#pragma once

namespace revolve
{
enum class Address : unsigned int
{
	Character1 = 0x122F1F8,
	Character2 = 0x12322D0,
	CharacterResources1 = 0x633C28,
	CharacterResources2 = 0x633CE8,
	CharacterIndex1 = 0x635498,
};

/*
 * Required as the base address may change when rebooted.
 */
Address getBaseAddress();
Address operator+(Address lhs, Address rhs);
} // namespace revolve
