#include "FrameStep.hpp"

namespace labtool
{

void FrameStep::pauseNextFrame()
{
	if (m_mustPauseNextFrame)
	{
		isPaused = true;
		m_mustPauseNextFrame = !m_mustPauseNextFrame;
	}
}

void FrameStep::pause()
{
	isPaused = !isPaused;
}

void FrameStep::frameStep()
{
	isPaused = !isPaused;
	m_mustPauseNextFrame = true;
}
} // namespace labtool
