#include "z3D/z3D.h"

#define EDIT_CMB_BYTE(offset_, val_) (CMB_[offset_] = val_)

void CustomModel_EditHeartContainerToDoubleDefense(void* heartContainerCMB) {
    char* CMB_ = (char*)heartContainerCMB;

    EDIT_CMB_BYTE(0xDB, 0x01);
    EDIT_CMB_BYTE(0xE8, 0x01);
    EDIT_CMB_BYTE(0x17C, 0x19); EDIT_CMB_BYTE(0x17D, 0x19); EDIT_CMB_BYTE(0x17E, 0x19); 
    EDIT_CMB_BYTE(0x180, 0x00); EDIT_CMB_BYTE(0x181, 0x00); EDIT_CMB_BYTE(0x182, 0x00); EDIT_CMB_BYTE(0x183, 0xB2);
    EDIT_CMB_BYTE(0x1FC, 0x01);
    EDIT_CMB_BYTE(0x20D, 0x00);
    EDIT_CMB_BYTE(0x210, 0x01);
    EDIT_CMB_BYTE(0x235, 0x01);
    EDIT_CMB_BYTE(0x244, 0x02);
    EDIT_CMB_BYTE(0x2DC, 0xFF); EDIT_CMB_BYTE(0x2DD, 0xFF);
    EDIT_CMB_BYTE(0x358, 0x00);
}
