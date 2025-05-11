#include "ResetState.hpp"

#include "../revolveLib/RevolveLib.hpp"

namespace labtool
{

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

// TODO: To be replaced with GameButtons.
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

//----------------------------------------------------------------------------------------------------------------------
PressedButtons ResetState::mReadPressedButtons(char pressedButtonsBits)
{
	PressedButtons pressedButtons;
	pressedButtons.up = pressedButtonsBits >> 0 & 1;
	pressedButtons.down = pressedButtonsBits >> 1 & 1;
	pressedButtons.left = pressedButtonsBits >> 2 & 1;
	pressedButtons.right = pressedButtonsBits >> 3 & 1;
	pressedButtons.a = pressedButtonsBits >> 4 & 1;
	pressedButtons.b = pressedButtonsBits >> 5 & 1;
	pressedButtons.c = pressedButtonsBits >> 6 & 1;
	pressedButtons.d = pressedButtonsBits >> 7 & 1;

	return pressedButtons;
}

//----------------------------------------------------------------------------------------------------------------------
Direction ResetState::mPressedButtonsToDirection(PressedButtons pressedButtons)
{
	// For now, no handling of facing direction

	if (pressedButtons.down && pressedButtons.left)
	{
		return Direction::DownBack;
	}
	else if (pressedButtons.down && pressedButtons.right)
	{
		return Direction::DownForward;
	}
	else if (pressedButtons.up && pressedButtons.left)
	{
		return Direction::UpBack;
	}
	else if (pressedButtons.up && pressedButtons.right)
	{
		return Direction::UpForward;
	}
	else if (pressedButtons.down)
	{
		return Direction::Down;
	}
	else if (pressedButtons.left)
	{
		return Direction::Back;
	}
	else if (pressedButtons.right)
	{
		return Direction::Forward;
	}
	else if (pressedButtons.up)
	{
		return Direction::Up;
	}

	return Direction::Neutral;
}

//----------------------------------------------------------------------------------------------------------------------
void ResetState::reset(char pressedButtonsBits)
{
	const auto pressedButtons = mReadPressedButtons(pressedButtonsBits);
	const auto direction = mPressedButtonsToDirection(pressedButtons);
	mResetCharacters(direction);
}

//----------------------------------------------------------------------------------------------------------------------
void ResetState::mResetCharacters(Direction direction)
{
	static auto currentPreset = PositionPreset::Roundstart;

	switch (direction)
	{
	case Direction::DownBack:
		currentPreset = PositionPreset::CorneringRight;
		break;
	case Direction::DownForward:
		currentPreset = PositionPreset::CorneredLeft;
		break;
	case Direction::Down:
		currentPreset = PositionPreset::Roundstart;
		break;
	case Direction::Up:
		currentPreset = PositionPreset::InvertedRoundstart;
		break;
	case Direction::Back:
		currentPreset = PositionPreset::CorneredRight;
		break;
	case Direction::Forward:
		currentPreset = PositionPreset::CorneringLeft;
		break;
	case Direction::Neutral:
		break;
	}

	mResetCharacters(currentPreset);

	return;
}

//----------------------------------------------------------------------------------------------------------------------
void ResetState::mResetCharacters(PositionPreset preset)
{
	switch (preset)
	{
	case PositionPreset::Roundstart:
		revolve::character1.currentPosition = { -10000, 0 };
		revolve::character2.currentPosition = { 10000, 0 };
		break;
	case PositionPreset::InvertedRoundstart:
		revolve::character1.currentPosition = { 10000, 0 };
		revolve::character2.currentPosition = { -10000, 0 };
		break;
	case PositionPreset::CorneredRight:
		revolve::character1.currentPosition = { -58000, 0 };
		revolve::character2.currentPosition = { -53000, 0 };
		break;
	case PositionPreset::CorneringRight:
		revolve::character1.currentPosition = { -53000, 0 };
		revolve::character2.currentPosition = { -58000, 0 };
		break;
	case PositionPreset::CorneredLeft:
		revolve::character1.currentPosition = { 58000, 0 };
		revolve::character2.currentPosition = { 53000, 0 };
		break;
	case PositionPreset::CorneringLeft:
		revolve::character1.currentPosition = { 53000, 0 };
		revolve::character2.currentPosition = { 58000, 0 };
		break;
	}

	return;
}
} // namespace labtool
