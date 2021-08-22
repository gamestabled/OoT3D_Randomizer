#include "z3D/z3D.h"
#include "settings.h"

u32 EnSyatekiMan_UseRemindText(void) {
	return gSaveContext.linkAge == 0 && (gSaveContext.upgrades & 0x7) == 0;
}
