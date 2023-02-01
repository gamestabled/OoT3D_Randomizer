#include "z3D/z3D.h"
#include "settings.h"

// There is a bug that ties opening of kak gate to pulling the master sword for the first time
// This bug is fixed if kak gate is set to closed- If open the bug is allowed to exist so the gate
//  can be opened without also opening the mask shop.
u32 KakGate_CheckToFixBug(void) {
    if (gSettingsContext.openKakariko == OPENKAKARIKO_OPEN) {
        return 0;
    } else {
        return 1;
    }
}
