#pragma once

namespace revolve
{
enum class Action : short
{
	Idle = 0,
	Walk = 1,
	Backwalk = 2,
	JumpNeutral = 3,
	JumpForward = 4,
	JumpBack = 5,

	StandToCrouch = 7, // Also CrouchToStand
	Crouch = 8
	// Anything else not listed is (most probably) character specific
};
}
