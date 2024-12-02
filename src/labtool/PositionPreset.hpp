#pragma once

namespace labtool
{

struct PressedButtons
{
	char up;
	char down;
	char left;
	char right;
	char a;
	char b;
	char c;
	char d;
};

enum class Direction
{
	Neutral,
	Forward,
	DownForward,
	Down,
	DownBack,
	Back,
	UpBack,
	UpForward,
	Up
};

enum class PositionPreset
{
	Roundstart,
	InvertedRoundstart,
	CorneredRight,
	CorneringRight,
	CorneredLeft,
	CorneringLeft
};

PressedButtons readPressedButtons(char pressedButtonsBits);
Direction pressedButtonsToDirection(PressedButtons pressedButtons);
void resetCharacters(char pressedButtonsBits);
void resetCharacters(Direction direction);
void resetCharacters(PositionPreset preset);
} // namespace labtool
