#include "z3D/z3D.h"
#include "settings.h"

u16 MagicWind_CheckSet(void) {
    if (gSaveContext.fw.set) {
        gSaveContext.respawn[2].pos.x = (f32)gSaveContext.fw.pos.x;
        gSaveContext.respawn[2].pos.y = (f32)gSaveContext.fw.pos.y;
        gSaveContext.respawn[2].pos.z = (f32)gSaveContext.fw.pos.z;
        return 1;
    }
    return 0;
}
