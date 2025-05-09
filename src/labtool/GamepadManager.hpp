#pragma once

// windows.h include is required to be above Xinput to recognize which architecture is used.
#include <windows.h>

#include <Xinput.h>
#pragma comment(lib, "Xinput9_1_0.lib")

#include <map>

namespace labtool
{
/**
 * Manages all the gamepads and hotplug using XInput 9.
 */
class GamepadManager
{
  public:
	GamepadManager();

	void readGamepads();

  private:
	void mReadGamepad(int gamepadIndex);

	using MapActiveStates = std::map<int, std::pair<bool, XINPUT_STATE>>;
	MapActiveStates m_inputStates;
};
} // namespace labtool
