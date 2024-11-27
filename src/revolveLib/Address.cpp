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

	return static_cast<Address>(reinterpret_cast<uint32_t>(hModule));
}

Address getDynamicAddress(Address relativeAddress)
{
	return getBaseAddress() + relativeAddress;
}

Address operator+(Address lhs, Address rhs)
{
	return static_cast<Address>(static_cast<uint32_t>(lhs) + static_cast<std::uint32_t>(rhs));
}
} // namespace revolve
