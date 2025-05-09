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
} // namespace labtool
