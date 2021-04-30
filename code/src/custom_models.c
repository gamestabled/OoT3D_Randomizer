#include "z3D/z3D.h"
#include "string.h"
#include "custom_models.h"
#include "objects.h"

#define EDIT_BYTE(offset_, val_) (BASE_[offset_] = val_)

void CustomModel_EditHeartContainerToDoubleDefense(void* heartContainerCMB) {
    char* BASE_ = (char*)heartContainerCMB;

    EDIT_BYTE(0xDB, 0x01);
    EDIT_BYTE(0xE8, 0x01);
    EDIT_BYTE(0x17C, 0x19); EDIT_BYTE(0x17D, 0x19); EDIT_BYTE(0x17E, 0x19); 
    EDIT_BYTE(0x180, 0x00); EDIT_BYTE(0x181, 0x00); EDIT_BYTE(0x182, 0x00); EDIT_BYTE(0x183, 0xB2);
    EDIT_BYTE(0x1FC, 0x01);
    EDIT_BYTE(0x20D, 0x00);
    EDIT_BYTE(0x210, 0x01);
    EDIT_BYTE(0x235, 0x01);
    EDIT_BYTE(0x244, 0x02);
    EDIT_BYTE(0x2DC, 0xFF); EDIT_BYTE(0x2DD, 0xFF);
    EDIT_BYTE(0x358, 0x00);
}

void CustomModel_EditTitleScreenLogo(void* titleScreenZAR) {
    char* BASE_ = (char*)titleScreenZAR;

    // copy_nintendo.cmb:
    EDIT_BYTE(0x4F3, 0x40);
    EDIT_BYTE(0x5905, 0x00); EDIT_BYTE(0x5906, 0x01);//Change texture dataLength
    EDIT_BYTE(0x590A, 0x01);// IsETC1 = true
    EDIT_BYTE(0x590D, 0x02);// Width  = 512
    EDIT_BYTE(0x590E, 0x80);// Height = 128
    EDIT_BYTE(0x5910, 0x5B);// ETC1a4
    //Edit positionOffset of each shape
    EDIT_BYTE(0x597A, 0x80); EDIT_BYTE(0x597B, 0x3F);
    EDIT_BYTE(0x597C, 0x33); EDIT_BYTE(0x597D, 0x33); EDIT_BYTE(0x597E, 0x33); EDIT_BYTE(0x597F, 0x40);
    //Edit vertices/UVs
    EDIT_BYTE(0x5AFE, 0xA0); EDIT_BYTE(0x5B02, 0xA0); EDIT_BYTE(0x5B0A, 0xA0); EDIT_BYTE(0x5B0E, 0xA0);
    EDIT_BYTE(0x5B16, 0xA0); EDIT_BYTE(0x5B1A, 0xA0); EDIT_BYTE(0x5B22, 0xA0); EDIT_BYTE(0x5B26, 0xA0);

    // title_logo_us.cmb: Edit positionOffset of each shape
    EDIT_BYTE(0x36BF3, 0x40); EDIT_BYTE(0x36D33, 0x40); EDIT_BYTE(0x36E73, 0x40); EDIT_BYTE(0x36FB3, 0x40);
    EDIT_BYTE(0x370F3, 0x40); EDIT_BYTE(0x37233, 0x40); EDIT_BYTE(0x37373, 0x40); EDIT_BYTE(0x374B3, 0x40);
    EDIT_BYTE(0x375F3, 0x40); EDIT_BYTE(0x37733, 0x40); EDIT_BYTE(0x37873, 0x40); EDIT_BYTE(0x379B3, 0x40);
    EDIT_BYTE(0x37AF3, 0x40); EDIT_BYTE(0x37C33, 0x40); EDIT_BYTE(0x37D73, 0x40); EDIT_BYTE(0x37EB3, 0x40);
    EDIT_BYTE(0x37FF3, 0x40); EDIT_BYTE(0x38133, 0x40); EDIT_BYTE(0x38273, 0x40); EDIT_BYTE(0x383B3, 0x40);
    EDIT_BYTE(0x384F3, 0x40); EDIT_BYTE(0x38633, 0x40);

    // g_title_fire.cmab 
    EDIT_BYTE(0x5E570, 0x01);// Change keyframe count to 1 so we only have to change one keyframe
    EDIT_BYTE(0x5E580, 0x0A); EDIT_BYTE(0x5E581, 0xD7); EDIT_BYTE(0x5E582, 0x23); EDIT_BYTE(0x5E583, 0x3D);// Red to 0.04
    EDIT_BYTE(0x5E660, 0x01);
    EDIT_BYTE(0x5E670, 0x91); EDIT_BYTE(0x5E671, 0xED); EDIT_BYTE(0x5E672, 0x5C); EDIT_BYTE(0x5E673, 0x3F);// Green 0.863

    // g_title_fire_ura.cmab
    EDIT_BYTE(0x5EA80, 0x01);
    EDIT_BYTE(0x5EA90, 0x0A); EDIT_BYTE(0x5E581, 0xD7); EDIT_BYTE(0x5E582, 0x23); EDIT_BYTE(0x5E583, 0x3D);
    EDIT_BYTE(0x5EB70, 0x01);
    EDIT_BYTE(0x5EB80, 0x91); EDIT_BYTE(0x5EB81, 0xED); EDIT_BYTE(0x5EB82, 0x5C); EDIT_BYTE(0x5EB83, 0x3F);
}

// The same offsets work for both fairy ocarina and ocarina of time,
// so we will just reuse this function for both
void CustomModel_SetOcarinaToRGBA565(void* ocarinaCMB) {
    char* BASE_ = (char*)ocarinaCMB;

    EDIT_BYTE(0x3F2, 0x01); EDIT_BYTE(0x3F8, 0x5A);
}

void CustomModel_Update(void) {
    // Make sure custom_assets is loaded
    if (ExtendedObject_GetIndex(&gGlobalContext->objectCtx, OBJECT_CUSTOM_GENERAL_ASSETS) < 0) {
        ExtendedObject_Spawn(&gGlobalContext->objectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    }
}
