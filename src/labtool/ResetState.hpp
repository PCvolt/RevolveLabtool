#pragma once

namespace labtool
{

enum class Direction;  // May be moved for more generalistic uses
struct PressedButtons; // May be moved for more generalistic uses
enum class PositionPreset;

class ResetState
{
  public:
	static void reset(char pressedButtonsBits);

  private:
	static PressedButtons mReadPressedButtons(char pressedButtonsBits); // May be moved for more generalistic uses
	static Direction mPressedButtonsToDirection(PressedButtons pressedButtons);
	static void mResetCharacters(Direction direction);
	static void mResetCharacters(PositionPreset preset);
};
} // namespace labtool
