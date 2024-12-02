#pragma once

namespace labtool
{
class FrameStep
{
  public:
	static void pauseNextFrame();
	static void pause();
	static void frameStep();
	inline static bool isPaused = false;

  private:
	inline static bool m_mustPauseNextFrame = false;
};
} // namespace labtool
