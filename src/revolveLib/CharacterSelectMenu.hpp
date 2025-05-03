#pragma once

namespace revolve
{
/*
struct u_Coordinates
{
	int x;
	int y;
	// int;
	// int;
}
*/
struct CharacterSelectMenu
{
	char pad_1[48];
	int stageIndex; // 0x30
	char pad_2[16];
	// u_Coordinates * p1CursorCoordinates; // 0x34
	// u_Coordinates * p2CursorCoordinates; // 0x38
	// u_Coordinates * p1ArtworkCoordinates; // 0x3C
	// u_Coordinates * p2ArtworkCoordinates; // 0x40
	// CursorIndex goes from 0 to 18
	int p1CursorIndex;	// 0x44
	int p2CursorIndex;	// 0x48
	int cursorMaxIndex; // 0x4C, seemingly useless
	bool p1LockedIn;	// 0x50
	bool p2LockedIn;	// 0x51
	char pad_3[26];
	int timeSpent; // 0x6C
};

} // namespace revolve
