#include "EntryPoint.hpp"
#include "Hooks.hpp"
#include "PositionPreset.hpp"

#include "../revolveLib/RevolveLib.hpp"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

auto oldUnknownFunctionInGameLoop = (unsigned int(__cdecl *)(void)) nullptr;

bool isPaused = false;

namespace
{

void compileTimeStructChecks()
{
	static_assert(sizeof(revolve::CharacterResources) == 0xC0, "Struct size mismatch: CharacterResources");
	static_assert(offsetof(revolve::Character, absoluteDirections) == 0xA0,
				  "Wrong offset: Character::absoluteDirections");
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
	if (isPaused)
	{
		return;
	}

	auto oldGameUpdate = (void (*)(void **))(*esi); // Ideally only set once at startup
	oldGameUpdate(esi);
}

void frameStep()
{
	static bool mustPauseNextFrame = false;

	if (mustPauseNextFrame)
	{
		isPaused = true;
		mustPauseNextFrame = !mustPauseNextFrame;
	}

	if (::isKeyJustPressed(0x39)) // key 9
	{
		isPaused = !isPaused;
	}
	else if (::isKeyJustPressed(0x30)) // key 0
	{
		isPaused = !isPaused;
		mustPauseNextFrame = true;
	}
}

void positionReset()
{
	if (::isKeyJustPressed(0x08)) // key Backspace
	{
		labtool::resetCharacters(revolve::character1.absoluteDirections);
	}
}

unsigned int functionInGameLoop()
{
	//::displayFps();
	if (static_cast<int>(revolve::PauseMenuMode::TrainingMode) == revolve::pauseMenu.setModeInCharacterSelect)
	{
		frameStep();
		positionReset();
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
