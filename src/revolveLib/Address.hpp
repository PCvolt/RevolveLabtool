#pragma once

#include <stdint.h>

namespace revolve
{
enum class Address : uint32_t
{
	Character1 = 0x122F1F8,
	Character2 = 0x12322D0,
	CharacterResources1 = 0x633C28,
	CharacterResources2 = 0x633CE8,

	// Contain value from enum class CharacterIndex
	CharacterSelectCursor1 = 0x635498,
	CharacterSelectCursor2 = 0x63549C,

	PauseMenu = 0x14B856C,
	PauseMenuUniqueGauge = 0x742798,
	MainMenuCursor = 0x122E1DC, // static: 0x170E1DC
	PauseMenuCursor = 0x12451b8,
	DebugMode = 0x742128, // static: 0xC22128 // 0 = Release, 1 = Debug
};

/*
 * Required as the base address may change when rebooted.
 */
Address getBaseAddress();
Address getDynamicAddress(Address relativeAddress);
Address operator+(Address lhs, Address rhs);
} // namespace revolve
