#include "EntryPoint.hpp"

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

DWORD WINAPI HookThread(HMODULE hModule)
{
	::compileTimeStructChecks();
	::openConsole();

	setDebugMode(true);

	return 0;
}
