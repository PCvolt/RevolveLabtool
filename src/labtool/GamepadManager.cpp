#include "GamepadManager.hpp"

#include <iostream>

namespace labtool
{
//-----------------------------------------------------------------------------
GamepadManager::GamepadManager() = default;

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
ButtonsPressed GamepadManager::remapButtons(int gamepadIndex)
{
	const auto stateActivity = m_inputStates[gamepadIndex].first;
	if (!stateActivity)
	{
		return ButtonsPressed();
	}

	const auto inputState = m_inputStates[gamepadIndex].second;
	const auto & buttons = inputState.Gamepad.wButtons;

	ButtonsPressed buttonsPressed;
	// XInput joysticks range is [-32768; 32767].
	// We apply an arbitrary deadzone to avoid drift from affecting controls.
	constexpr int deadzone = 15000;
	buttonsPressed.up = (buttons & XINPUT_GAMEPAD_DPAD_UP) || (inputState.Gamepad.sThumbLY > deadzone);
	buttonsPressed.down = (buttons & XINPUT_GAMEPAD_DPAD_DOWN) || (inputState.Gamepad.sThumbLY < -deadzone);
	buttonsPressed.left = (buttons & XINPUT_GAMEPAD_DPAD_LEFT) || (inputState.Gamepad.sThumbLX < -deadzone);
	buttonsPressed.right = (buttons & XINPUT_GAMEPAD_DPAD_RIGHT) || (inputState.Gamepad.sThumbLX > deadzone);
	buttonsPressed.a = buttons & XINPUT_GAMEPAD_A;
	buttonsPressed.b = buttons & XINPUT_GAMEPAD_B;
	buttonsPressed.c = buttons & XINPUT_GAMEPAD_X;
	buttonsPressed.d = buttons & XINPUT_GAMEPAD_Y;
	buttonsPressed.start = buttons & XINPUT_GAMEPAD_START;

	return buttonsPressed;
}
} // namespace labtool
