#pragma once

#include <Windows.h>

/**
 * Hooks the function call by replacing the original relative offset with a new relative offset.
 * The relative offset is the difference between the target address to jump to, and the CALL instruction itself.
 *
 * A CALL instruction takes 5 bytes in this form: E8 xx xx xx xx.
 * E8 is the CALL instruction.
 * xx xx xx xx is the relative offset.
 *
 * @param instructionAddress The address of the CALL instruction.
 * @param target The address we want to jump to.
 * @return the original target address.
 */
DWORD hookFunctionCall(DWORD instructionAddress, DWORD target);
