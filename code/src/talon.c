#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

u16 EnTa_GetCastleTextbox(void) {
        
        if(gSaveContext.eventChkInf[0x1] & 0x0004)
                return 0x702C;
        else
                return 0x9100;
    
}
