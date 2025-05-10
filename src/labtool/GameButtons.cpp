#include "GameButtons.hpp"

namespace
{
//-----------------------------------------------------------------------------
[[nodiscard]] int bitwiseOrIfPressed(int bits, bool isButtonPressed, int value)
{
	if (isButtonPressed)
	{
		bits |= value;
	}

	return bits;
}
} // namespace

namespace labtool
{
//-----------------------------------------------------------------------------
int GameButtons::buildButtonsBitmask() const
{
	int bits = 0;

	bits = ::bitwiseOrIfPressed(bits, up, 0x1);
	bits = ::bitwiseOrIfPressed(bits, down, 0x2);
	bits = ::bitwiseOrIfPressed(bits, left, 0x4);
	bits = ::bitwiseOrIfPressed(bits, right, 0x8);
	bits = ::bitwiseOrIfPressed(bits, a, 0x10);
	bits = ::bitwiseOrIfPressed(bits, b, 0x20);
	bits = ::bitwiseOrIfPressed(bits, c, 0x40);
	bits = ::bitwiseOrIfPressed(bits, d, 0x80);
	bits = ::bitwiseOrIfPressed(bits, start, 0x100);
	bits = ::bitwiseOrIfPressed(bits, ab, 0x30);
	bits = ::bitwiseOrIfPressed(bits, bc, 0x60);
	bits = ::bitwiseOrIfPressed(bits, abc, 0x70);
	bits = ::bitwiseOrIfPressed(bits, screen, 0x400);

	return bits;
}
} // namespace labtool
