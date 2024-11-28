#include "Hooks.hpp"

DWORD hookFunctionCall(DWORD instructionAddress, DWORD target)
{
	const int instructionSize = 5;

	// Change the protection level to Read/Write for 5 bytes at the given address
	DWORD oldProtection;
	if (!VirtualProtect((void *)instructionAddress, instructionSize, PAGE_READWRITE, &oldProtection))
	{
		return 0;
	}

	// We get the CALL instruction address (+ CALL instruction size) and add the offset to get the original target
	// address.
	DWORD oldTargetAddress = (instructionAddress + instructionSize) + (*(DWORD *)(instructionAddress + 1));

	// We compute the difference between the new target we want to jump to, and the CALL instruction itself (+ CALL
	// instruction size), to get the new relative offset. The CALL will now jump to the new target.
	*((DWORD *)(instructionAddress + 1)) = target - (instructionAddress + instructionSize);

	// Reset the protection level to what it originally was
	if (!VirtualProtect((void *)instructionAddress, instructionSize, oldProtection, &oldProtection))
	{
		return 0;
	}

	return oldTargetAddress;
}
