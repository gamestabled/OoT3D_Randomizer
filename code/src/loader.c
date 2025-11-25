/*
 * This file is a modified version of a file originally written by RicBent
 * for the program Magikoopa.
 */

#include "newcodeinfo.h"

#include "3ds/types.h"
#include "3ds/svc.h"

Result svcOpenProcess(Handle* process, u32 processId);
Result svcGetProcessId(u32* out, Handle handle);
Result svcControlProcessMemory(Handle process, u32 addr0, u32 addr1, u32 size, u32 type, u32 perm);

void loader_main(void) __attribute__((section(".loader")));
Handle getCurrentProcessHandle(void) __attribute__((section(".loader")));

void loader_main(void) {
    Result res;

    u32 address      = NEWCODE_OFFSET;
    u32 neededMemory = (NEWCODE_SIZE + 0xFFF) & ~0xFFF; // rounding up

    res = svcControlProcessMemory(getCurrentProcessHandle(), address, address, neededMemory, MEMOP_PROT,
                                  MEMPERM_READ | MEMPERM_WRITE | MEMPERM_EXECUTE);

    if (res < 0)
        svcBreak(1);

    // Hacky solution to be able to edit the following structs, which are normally in RO data:
    // gGearUsabilityTable, gOcarinaMenuSongNoteSequences, gOcarinaMenuSongLengths
    res = svcControlProcessMemory(getCurrentProcessHandle(), 0x4D4000, 0x4D4000, 0x2000, MEMOP_PROT,
                                  MEMPERM_READ | MEMPERM_WRITE);

    if (res < 0)
        svcBreak(1);
}

Handle getCurrentProcessHandle(void) {
    Handle handle  = 0;
    u32 currentPid = 0;
    Result res;

    svcGetProcessId(&currentPid, 0xffff8001);
    res = svcOpenProcess(&handle, currentPid);

    if (res != 0)
        return 0;

    return handle;
}
