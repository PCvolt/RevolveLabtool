#pragma once

namespace labtool
{
/**
 * GameButtons contains all the buttons that the game understands.
 * It does not correspond to the buttons present on the controller.
 * This struct is the final step to build a bitmask variable that can be fed to the game.
 */
struct GameButtons
{
	/**
	 * Creates a variable that can be fed to the game, representing the buttons pressed.
	 */
	[[nodiscard]] int buildButtonsBitmask() const;

	// False if currently not pressed, true if currently pressed.
	bool up = false;	 // 0x1
	bool down = false;	 // 0x2
	bool left = false;	 // 0x4
	bool right = false;	 // 0x8
	bool a = false;		 // 0x10
	bool b = false;		 // 0x20
	bool c = false;		 // 0x40
	bool d = false;		 // 0x80
	bool start = false;	 // 0x100
	bool ab = false;	 // 0x30, same as a + b pressed at the same time
	bool bc = false;	 // 0x60, same as b + c pressed at the same time
	bool abc = false;	 // 0x70, same as a + b + c pressed at the same time
	bool screen = false; // 0x400
};
} // namespace labtool
