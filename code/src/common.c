#include "common.h"
#include "settings.h"

// From section 5 of https://www.cs.ubc.ca/~rbridson/docs/schechter-sca08-turbulence.pdf
u32 Hash(u32 state) {
    // Added salt based on the seed hash so traps in the same location in different seeds can have different effects
    u32 salt = 0;
    for (int i = 0; i < 5; i++) {
        salt |= gSettingsContext.hashIndexes[i] << (i * 6);
    }
    state ^= salt;

    state ^= 0xDC3A653D;
    state *= 0xE1C88647;
    state ^= state >> 16;
    state *= 0xE1C88647;
    state ^= state >> 16;
    state *= 0xE1C88647;

    return state;
}

u8 And(u32 seed, u8 start, u8 end) {
    u8 value = 1;

    for (u8 i = start; i < end && value; i++) {
        value &= seed >> i;
    }

    return value;
}

u8 Bias(u32 seed) {
    u8 value = (seed & 0x00000007);
    value |= And(seed, 3, 5) << 3;
    value |= And(seed, 5, 7) << 4;
    value |= And(seed, 7, 11) << 5;
    value |= And(seed, 11, 16) << 6;
    return value;
}

u8 IsInGame(void) {
    s32 entr = gSaveContext.entranceIndex;
    s32 mode = gSaveContext.gameMode;
    return mode == 0 ||
        (mode == 1 && entr != 0x0629 && entr != 0x0147 && entr != 0x00A0 && entr != 0x008D);
}

void DebugPrintNumber(const char* message, int num) {
    char buf[128];
    int length = snprintf(buf, 128, message, num);
    svcOutputDebugString(buf, length);
}
