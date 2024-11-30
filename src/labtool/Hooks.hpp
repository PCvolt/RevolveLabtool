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
 * @param target The target address we want to jump to.
 * @return the original target address.
 */
DWORD hookFunctionCall(DWORD instructionAddress, DWORD target);

/**
 * Replaces 5 bytes at the designated address by a CALL, when it is not possible to hook to a pre-existing CALL.
 *
 * @param instructionAddress The address at which to replace the instructions.
 * @param target The target address we want to jump to: the shim function.
 * @return 1 on success.
 */
DWORD patchToCallShim(DWORD instructionAddress, DWORD target);

/**
 * Patches the original game update instructions with a CALL to newGameUpdate().
 * The shim is responsible for handling registers and memory.
 */
void oldGameUpdateShim();
void newGameUpdate(void ** esi_param);
