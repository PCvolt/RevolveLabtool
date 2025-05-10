#pragma once

namespace labtool
{
/**
 * Contains all the buttons pressed during the current frame.
 * 0 = Not pressed
 * 1 = Pressed
 */
struct ButtonsPressed
{
	/**
	 * Creates a variable that can be fed to the game, representing the buttons pressed.
	 */
	[[nodiscard]] int buildButtonsBitsVariable();

	bool up;	 // 0x1
	bool down;	 // 0x2
	bool left;	 // 0x4
	bool right;	 // 0x8
	bool a;		 // 0x10
	bool b;		 // 0x20
	bool c;		 // 0x40
	bool d;		 // 0x80
	bool start;	 // 0x100
	bool ab;	 // 0x30, same as a + b pressed at the same time
	bool bc;	 // 0x60, same as b + c pressed at the same time
	bool abc;	 // 0x70, same as a + b + c pressed at the same time
	bool screen; // 0x400
};
} // namespace labtool
