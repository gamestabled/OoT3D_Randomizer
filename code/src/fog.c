#include "fog.h"
#include "settings.h"

#include "z3D/z3D.h"

#define z3D_Fog_State_addr 0x531EB4
#define z3D_Fog_State (*(u8*) z3D_Fog_State_addr)

//Override glitchy fog state when going through Market Entrance -> Hyrule Field
//exit during entrance randomizer
void Fog_OverrideState(void) {
    if (gSettingsContext.shuffleOverworldEntrances == ON) {
        z3D_Fog_State = 0;
    }
}
