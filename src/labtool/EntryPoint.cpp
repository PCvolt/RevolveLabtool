#include "EntryPoint.hpp"
#include "Hooks.hpp"

#include "../revolveLib/RevolveLib.hpp"

#include <iostream>

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
} // namespace

void setDebugMode(bool isDebug)
{
	int & debugMode = *reinterpret_cast<int *>(revolve::getDynamicAddress(revolve::Address::DebugMode));
	debugMode = isDebug;
}

void newGameUpdate(void ** esi)
{
	std::cout << "aaa" << std::endl;

	auto oldGameUpdate = (void (*)(void **))(*esi); // Ideally only set once at startup
	oldGameUpdate(esi);
}

DWORD WINAPI HookThread(HMODULE hModule)
{
	::compileTimeStructChecks();
	::openConsole();

	setDebugMode(true);
	patchToCallShim((DWORD)revolve::getDynamicAddress(revolve::Address::GameUpdateShim), (DWORD)oldGameUpdateShim);

	return 0;
}
