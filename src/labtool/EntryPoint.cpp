#include "EntryPoint.hpp"

#include <iostream>

namespace
{
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
	::openConsole();

	return 0;
}
