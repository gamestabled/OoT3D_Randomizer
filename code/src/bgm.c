#include "z3D/z3D.h"
#include "bgm.h"

static u32 rBGMOverrides[128] = {0};

u32 SetBGM(u32 original)
{
    s32 i = original - BGM_BASE;
    u32 bgm;

    // Check for invalid index
    if(i < 0 || i > BGM_COUNT)
        return original;

    bgm = rBGMOverrides[i];
    // Check for invalid song
    if(bgm < BGM_BASE || bgm > BGM_BASE + BGM_COUNT)
        return original;

    return rBGMOverrides[i];
}
