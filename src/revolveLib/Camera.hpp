#pragma once

namespace revolve
{
struct Camera
{
	int isZoomEnabled;
	char pad_1[4];		// 900 by default
	int pad_2[4];		// 1280 by default
	int viewportHeight; // 480 by default
	int viewportWidth;	// 800 by default
	int isFollowingPlayers;
	int y;							// 800 when zoomed at max
	int xNegative;					// -640 to -160 from left to right
	int x;							// 160 to 640 from left to right
	int anyPlayersHighestYPosition; // Starts at 200, increases when any player jumps
};

extern Camera & camera;
} // namespace revolve
