#include "EntryPoint.hpp"

#include "../revolveLib/RevolveLib.hpp"

#include <iostream>

namespace
{
void compileTimeStructChecks()
{
	static_assert(sizeof(revolve::Character) == 0xC0, "Struct size mismatch: Character");
}

void openConsole()
{
	AllocConsole();

	FILE * f = new FILE;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "Hooked to BBBR" << std::endl;
}
} // namespace

DWORD WINAPI HookThread(HMODULE hModule)
{
	::compileTimeStructChecks();
	::openConsole();

	std::cout << revolve::character2.currentHealth << std::endl;

	return 0;
}
