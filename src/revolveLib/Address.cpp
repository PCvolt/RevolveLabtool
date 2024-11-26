#include "Address.hpp"

#include <Windows.h>
#include <stdexcept>

namespace revolve
{
Address getBaseAddress()
{
	HMODULE hModule = GetModuleHandle(nullptr);

	if (!hModule)
	{
		throw std::runtime_error("Could not get base address");
	}

	return static_cast<Address>(reinterpret_cast<uintptr_t>(hModule));
}

Address getDynamicAddress(Address relativeAddress)
{
	return getBaseAddress() + relativeAddress;
}

Address operator+(Address lhs, Address rhs)
{
	return static_cast<Address>(static_cast<unsigned int>(lhs) + static_cast<unsigned int>(rhs));
}
} // namespace revolve
