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

	MainMenuCursor = 0x122E1DC, // static: 0x170E1DC
	DebugMode = 0x742128, // static: 0xC22128 // 0 = Release, 1 = Debug
};

/*
 * Required as the base address may change when rebooted.
 */
Address getBaseAddress();
Address getDynamicAddress(Address relativeAddress);
Address operator+(Address lhs, Address rhs);
} // namespace revolve
