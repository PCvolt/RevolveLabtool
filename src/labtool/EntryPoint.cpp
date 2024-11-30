#include "EntryPoint.hpp"
#include "Hooks.hpp"

#include "../revolveLib/RevolveLib.hpp"

#include <chrono>
#include <iostream>
#include <unordered_map>

auto oldUnknownFunctionInGameLoop = (unsigned int(__cdecl *)(void)) nullptr;

namespace
{
void compileTimeStructChecks()
{
	static_assert(sizeof(revolve::CharacterResources) == 0xC0, "Struct size mismatch: CharacterResources");
}

void openConsole()
{
	AllocConsole();

	FILE * f = new FILE;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "Hooked to BBBR" << std::endl;
}

bool isKeyJustPressed(int virtualKey)
{
	static std::unordered_map<int, bool> previousKeyState;
	bool currentKeyState = GetAsyncKeyState(virtualKey) & 0x8000;
	bool justPressed = currentKeyState && !previousKeyState[virtualKey];

	previousKeyState[virtualKey] = currentKeyState;

	return justPressed;
}

void displayFps()
{
	using namespace std::chrono;

	// Count how many calls were performed
	static int callNumbers = 0;
	++callNumbers;

	// Add time differences until it reaches 1 second
	static auto lastTime = high_resolution_clock::now();
	auto currentTime = high_resolution_clock::now();

	auto elapsed = duration_cast<milliseconds>(currentTime - lastTime).count();
	static auto elapsedTimeCumulated = 0;
	elapsedTimeCumulated += elapsed;

	// Display number of calls every second (FPS)
	if (elapsedTimeCumulated >= 1000)
	{
		std::cout << callNumbers << std::endl;

		callNumbers = 0;
		elapsedTimeCumulated = 0;
	}

	lastTime = currentTime;
}
} // namespace

void setDebugMode(bool isDebug)
{
	int & debugMode = *reinterpret_cast<int *>(revolve::getDynamicAddress(revolve::Address::DebugMode));
	debugMode = isDebug;
}

void newGameUpdate(void ** esi)
{
	auto oldGameUpdate = (void (*)(void **))(*esi); // Ideally only set once at startup
	oldGameUpdate(esi);
}

unsigned int functionInGameLoop()
{
	//::displayFps();
	if (::isKeyJustPressed(0x31)) // key 1
	{
		std::cout << "pressed!" << std::endl;
	}

	return oldUnknownFunctionInGameLoop();
}

DWORD WINAPI HookThread(HMODULE hModule)
{
	::compileTimeStructChecks();
	::openConsole();

	setDebugMode(true);
	patchToCallShim((DWORD)revolve::getDynamicAddress(revolve::Address::GameUpdateShim), (DWORD)oldGameUpdateShim);

	// Not very elegant, enum class Address is not handy for casting
	auto addressUnknownFunction =
		revolve::getDynamicAddress(static_cast<revolve::Address>(static_cast<uint32_t>(0x2400E)));
	oldUnknownFunctionInGameLoop = (unsigned int(__cdecl *)(void))hookFunctionCall(
		(DWORD) static_cast<uint32_t>(addressUnknownFunction), (DWORD)functionInGameLoop);

	return 0;
}
