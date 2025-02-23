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
	Character1Palette = 0x742548, // 0 to 3
	Character2Palette = 0x74254C, // 0 to 3
	Camera = 0x634440,

	// Contain value from enum class CharacterIndex
	CharacterSelectCursor1 = 0x635498,
	CharacterSelectCursor2 = 0x63549C,

	ResetCharacter = 0x36630,

	MainMenu = 0x421A2,
	PauseMenu = 0x14B856C,
	PauseMenuUniqueGauge = 0x742798,
	MainMenuCursor = 0x122E1DC, // static: 0x170E1DC
	PauseMenuCursor = 0x12451b8,
	DebugMode = 0x742128, // static: 0xC22128 // 0 = Release, 1 = Debug
	CharacterSelectMenu = 0x122E1B0,

	// Calls
	GameUpdateShim = 0x24053,
	Call_Render = 0x2407A,

	// Functions
	BattleSceneUpdate = 0x4361B0, // void battleLoop(int param_1)
	ReadInputs = 0x1C860,
	UpdateCamera = 0x3140,
	UpdateCharacterSelect = 0x47700,
	UpdateVersusScreen = 0x48CD0,

	Render = 0x23AF0,
	RenderNetworkMenu = 0x40CD0,
	RenderStageBackground = 0x13240,
	RenderTrainingMenu = 0x13670,
	RenderText = 0x8DA30,
	RenderListNetworkLobbies = 0x40270,
};

/*
 * Required as the base address may change when rebooted.
 */
Address getBaseAddress();
Address getDynamicAddress(Address relativeAddress);
Address operator+(Address lhs, Address rhs);
} // namespace revolve
