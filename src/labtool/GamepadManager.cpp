#include "GamepadManager.hpp"

#include <iostream>

namespace labtool
{
//----------------------------------------------------------------------------------------------------------------------
GamepadManager::GamepadManager() = default;

//----------------------------------------------------------------------------------------------------------------------
void GamepadManager::readGamepads()
{
	// XInput only accepts 4 gamepads, and won't read higher indexes.
	// While not robust for higher gamepad counts, we will accept it as a workable amount.
	constexpr int maxGamepads = 4;
	for (int gamepadIndex = 0; gamepadIndex < maxGamepads; ++gamepadIndex)
	{
		mReadGamepad(gamepadIndex);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void GamepadManager::mReadGamepad(int gamepadIndex)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	DWORD result = XInputGetState(gamepadIndex, &state);

	auto & inputState = m_inputStates[gamepadIndex].second;
	auto & stateActivity = m_inputStates[gamepadIndex].first;

	auto isConnected = ERROR_SUCCESS == result;
	if (isConnected != stateActivity)
	{
		std::cout << "Controller #" << gamepadIndex << " " << (isConnected ? "connected" : "disconnected") << std::endl;
	}

	// The state is undefined if XInputGetState returns an error, therefore the check.
	if (isConnected)
	{
		inputState = state;
	}
	stateActivity = isConnected;
}

//----------------------------------------------------------------------------------------------------------------------
GameButtons GamepadManager::remapButtons(int gamepadIndex)
{
	const auto stateActivity = m_inputStates[gamepadIndex].first;
	if (!stateActivity)
	{
		return GameButtons();
	}

	const auto inputState = m_inputStates[gamepadIndex].second;
	const auto & buttons = inputState.Gamepad.wButtons;

	GameButtons gameButtons;
	// XInput joysticks range is [-32768; 32767].
	// We apply an arbitrary deadzone to avoid drift from affecting controls.
	constexpr int stickDeadzone = 15000;
	gameButtons.up = (buttons & XINPUT_GAMEPAD_DPAD_UP) || (inputState.Gamepad.sThumbLY > stickDeadzone);
	gameButtons.down = (buttons & XINPUT_GAMEPAD_DPAD_DOWN) || (inputState.Gamepad.sThumbLY < -stickDeadzone);
	gameButtons.left = (buttons & XINPUT_GAMEPAD_DPAD_LEFT) || (inputState.Gamepad.sThumbLX < -stickDeadzone);
	gameButtons.right = (buttons & XINPUT_GAMEPAD_DPAD_RIGHT) || (inputState.Gamepad.sThumbLX > stickDeadzone);
	gameButtons.a = buttons & XINPUT_GAMEPAD_A;
	gameButtons.b = buttons & XINPUT_GAMEPAD_B;
	gameButtons.c = buttons & XINPUT_GAMEPAD_X;
	gameButtons.d = buttons & XINPUT_GAMEPAD_Y;
	gameButtons.start = buttons & XINPUT_GAMEPAD_START;

	constexpr int triggerDeadzone = 50;
	gameButtons.a |= inputState.Gamepad.bLeftTrigger > triggerDeadzone;
	gameButtons.b |= inputState.Gamepad.bRightTrigger > triggerDeadzone;

	return gameButtons;
}
} // namespace labtool
