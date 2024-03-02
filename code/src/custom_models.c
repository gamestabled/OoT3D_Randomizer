#include "z3D/z3D.h"
#include "string.h"
#include "custom_models.h"
#include "objects.h"
#include "settings.h"

#define EDIT_BYTE(offset_, val_) (BASE_[offset_] = val_)

u8 SmallKeyData[][7] = {
    { 0x00, 0x80, 0x00, 0x00, 0x00, 0xCC, 0x00 }, // Forest
    { 0x54, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00 }, // Fire
    { 0x00, 0x00, 0xDA, 0x00, 0x00, 0x00, 0xFF }, // Water
    { 0x25, 0x00, 0x40, 0x00, 0x64, 0x00, 0xAD }, // Shadow
    { 0x80, 0x00, 0x82, 0x00, 0xAD, 0x00, 0xB0 }, // BotW
    { 0x80, 0x55, 0x00, 0x00, 0xFF, 0xAA, 0x00 }, // Spirit
    { 0x44, 0x1E, 0x00, 0x00, 0x86, 0x3B, 0x00 }, // Fortress
    { 0xC4, 0x57, 0x00, 0x00, 0xFF, 0xD1, 0xAD }, // GTG
    { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // Ganon
};

void CustomModel_EditLinkToCustomTunic(void* linkCMB) {
    char* BASE_ = (char*)linkCMB;

    // Edit combinerIndices
    EDIT_BYTE(0x6C4, 0x04); // Update combinerCount
    EDIT_BYTE(0x6CC, 0x0B);
    EDIT_BYTE(0x6CD, 0x00); // Add new combiner index (Replacing one of the combiners used by unused deku stick)
    EDIT_BYTE(0x6CE, 0x11);
    EDIT_BYTE(0x6CF, 0x00);

    // TextureCombiner0
    EDIT_BYTE(0x3588, 0x04);
    EDIT_BYTE(0x3589, 0x01); // CombinerMode to "Add"
    EDIT_BYTE(0x3594, 0x76); // SourceColor0 to "ConstantColor"
    EDIT_BYTE(0x359C, 0x03); // Color1Operand to OneMinusAlpha

    // TextureCombiner1
    EDIT_BYTE(0x35B0, 0x00);
    EDIT_BYTE(0x35B1, 0x21); // CombinerMode to "Modulate"
    EDIT_BYTE(0x35BE, 0xC0);
    EDIT_BYTE(0x35BF, 0x84); // SourceColor1 to "Texture0"
    EDIT_BYTE(0x35C4, 0x00); // Color1Operand to Color
    EDIT_BYTE(0x36FC, 0x78); // SourceColor0 to "Previous" (aka return the output of "TextureCombiner0")
    EDIT_BYTE(0x36FE, 0x77);
    EDIT_BYTE(0x36FF, 0x85); // SourceColor1 to "PrimaryColor"

    // Edit Texture Entry
    EDIT_BYTE(0x44E1, 0x40); // Update texture data length to "16384" bytes
    EDIT_BYTE(0x44EC, 0x5B); // Set texture to ETC1a4
}

void CustomModel_EditChildLinkToCustomTunic(void* linkCMB) {
    char* BASE_ = (char*)linkCMB;

    // Edit combinerIndices
    EDIT_BYTE(0x6C4, 0x03); // Update combinerCount
    EDIT_BYTE(0x6CC, 0x0D);
    EDIT_BYTE(0x6CD, 0x00);

    // TextureCombiner0
    EDIT_BYTE(0x2974, 0x02);
    EDIT_BYTE(0x2975, 0x64); // CombinerMode to "AddMult"
    EDIT_BYTE(0x2978, 0x01); // ColorScale to "One"
    EDIT_BYTE(0x2980, 0x76); // SourceColor0 to "ConstantColor"
    EDIT_BYTE(0x2984, 0xC0);
    EDIT_BYTE(0x2985, 0x84); // SourceColor2 to "Texture0"
    EDIT_BYTE(0x2988, 0x03); // Color1Operand to OneMinusAlpha

    // TextureCombiner1
    EDIT_BYTE(0x299C, 0x00);
    EDIT_BYTE(0x299D, 0x21); // CombinerMode to "Modulate"
    EDIT_BYTE(0x29A0, 0x04); // ColorScale to "Four"
    EDIT_BYTE(0x29AA, 0x77); // SourceColor1 to "PrimaryColor"
    EDIT_BYTE(0x29B0, 0x00); // Color1Operand to Color

    // Edit Texture Entry
    EDIT_BYTE(0x3441, 0x40); // Update texture data length to "16384" bytes
    EDIT_BYTE(0x344C, 0x5B); // Set texture to ETC1a4
}

static void CustomModel_EditHeartContainerToDoubleDefense(void* heartContainerCMB) {
    char* BASE_ = (char*)heartContainerCMB;

    EDIT_BYTE(0xDB, 0x01);
    EDIT_BYTE(0xE8, 0x01);
    EDIT_BYTE(0x17C, 0x19);
    EDIT_BYTE(0x17D, 0x19);
    EDIT_BYTE(0x17E, 0x19);
    EDIT_BYTE(0x180, 0x00);
    EDIT_BYTE(0x181, 0x00);
    EDIT_BYTE(0x182, 0x00);
    EDIT_BYTE(0x183, 0xB2);
    EDIT_BYTE(0x1FC, 0x01);
    EDIT_BYTE(0x20D, 0x00);
    EDIT_BYTE(0x210, 0x01);
    EDIT_BYTE(0x235, 0x01);
    EDIT_BYTE(0x244, 0x02);
    EDIT_BYTE(0x2DC, 0xFF);
    EDIT_BYTE(0x2DD, 0xFF);
    EDIT_BYTE(0x358, 0x00);
}

static void CustomModel_ApplyColorEditsToSmallKey(void* smallKeyCMB, s32 keyType) {
    char* BASE_ = (char*)smallKeyCMB;

    for (s32 i = 0; i < 7; i++) {
        EDIT_BYTE(0x12C + i, SmallKeyData[keyType][i]);
    }
}

void CustomModel_EditTitleScreenLogo(void* titleScreenZAR) {
    char* BASE_ = (char*)titleScreenZAR;

    // copy_nintendo.cmb:
    EDIT_BYTE(0x4F3, 0x40);
    EDIT_BYTE(0x5905, 0x00);
    EDIT_BYTE(0x5906, 0x01); // Change texture dataLength
    EDIT_BYTE(0x590A, 0x01); // IsETC1 = true
    EDIT_BYTE(0x590D, 0x02); // Width  = 512
    EDIT_BYTE(0x590E, 0x80); // Height = 128
    EDIT_BYTE(0x5910, 0x5B); // ETC1a4
    // Edit positionOffset of each shape
    EDIT_BYTE(0x597A, 0x80);
    EDIT_BYTE(0x597B, 0x3F);
    EDIT_BYTE(0x597C, 0x33);
    EDIT_BYTE(0x597D, 0x33);
    EDIT_BYTE(0x597E, 0x33);
    EDIT_BYTE(0x597F, 0x40);
    // Edit vertices/UVs
    EDIT_BYTE(0x5AFE, 0xA0);
    EDIT_BYTE(0x5B02, 0xA0);
    EDIT_BYTE(0x5B0A, 0xA0);
    EDIT_BYTE(0x5B0E, 0xA0);
    EDIT_BYTE(0x5B16, 0xA0);
    EDIT_BYTE(0x5B1A, 0xA0);
    EDIT_BYTE(0x5B22, 0xA0);
    EDIT_BYTE(0x5B26, 0xA0);

    // title_logo_us.cmb: Edit positionOffset of each shape
    EDIT_BYTE(0x36BF3, 0x40); // Blade
    EDIT_BYTE(0x36D33, 0x40); // Hilt
    EDIT_BYTE(0x36E73, 0x40); // Diamond
    EDIT_BYTE(0x36FB3, 0x40); // "3D"
    EDIT_BYTE(0x370F3, 0x40); // "A"
    EDIT_BYTE(0x37233, 0x40); // "A" shadow
    EDIT_BYTE(0x37373, 0x40); // "D"
    EDIT_BYTE(0x374B3, 0x40); // "D" shadow
    EDIT_BYTE(0x375F3, 0x40); // "E"
    EDIT_BYTE(0x37733, 0x40); // "E" shadow
    EDIT_BYTE(0x37873, 0x40); // "L"
    EDIT_BYTE(0x379B3, 0x40); // "L" shadow
    EDIT_BYTE(0x37AF3, 0x40); // "THE LEGEND OF"
    EDIT_BYTE(0x37C33, 0x40); // "Z"
    EDIT_BYTE(0x37D73, 0x40); // "Z" shadow
    EDIT_BYTE(0x37EB3, 0x40); // "OCARINA OF TIME"
    EDIT_BYTE(0x37FF3, 0x40); // Triforce
    EDIT_BYTE(0x38133, 0x40); // Shield body
    EDIT_BYTE(0x38273, 0x40); // Shield border
    EDIT_BYTE(0x383B3, 0x40); // Shield strap
    EDIT_BYTE(0x384F3, 0x40); // "TM" (zelda)
    EDIT_BYTE(0x38633, 0x40); // "TM" (ocarina of time, only present in the US logo)

    // title_logo_jpeu.cmb: Edit positionOffset of each shape
    EDIT_BYTE(0xF31B, 0x40);
    EDIT_BYTE(0xF45B, 0x40);
    EDIT_BYTE(0xF59B, 0x40);
    EDIT_BYTE(0xF6DB, 0x40);
    EDIT_BYTE(0xF81B, 0x40);
    EDIT_BYTE(0xF95B, 0x40);
    EDIT_BYTE(0xFA9B, 0x40);
    EDIT_BYTE(0xFBDB, 0x40);
    EDIT_BYTE(0xFD1B, 0x40);
    EDIT_BYTE(0xFE5B, 0x40);
    EDIT_BYTE(0xFF9B, 0x40);
    EDIT_BYTE(0x100DB, 0x40);
    EDIT_BYTE(0x1021B, 0x40);
    EDIT_BYTE(0x1035B, 0x40);
    EDIT_BYTE(0x1049B, 0x40);
    EDIT_BYTE(0x105DB, 0x40);
    EDIT_BYTE(0x1071B, 0x40);
    EDIT_BYTE(0x1085B, 0x40);
    EDIT_BYTE(0x1099B, 0x40);
    EDIT_BYTE(0x10ADB, 0x40);
    EDIT_BYTE(0x10C1B, 0x40);

    // g_title_fire.cmab
    EDIT_BYTE(0x5E570, 0x01); // Change keyframe count to 1 so we only have to change one keyframe
    EDIT_BYTE(0x5E580, 0x0A);
    EDIT_BYTE(0x5E581, 0xD7);
    EDIT_BYTE(0x5E582, 0x23);
    EDIT_BYTE(0x5E583, 0x3D); // Red to 0.04
    EDIT_BYTE(0x5E660, 0x01);
    EDIT_BYTE(0x5E670, 0x91);
    EDIT_BYTE(0x5E671, 0xED);
    EDIT_BYTE(0x5E672, 0x5C);
    EDIT_BYTE(0x5E673, 0x3F); // Green 0.863

    // g_title_fire_ura.cmab
    EDIT_BYTE(0x5EA80, 0x01);
    EDIT_BYTE(0x5EA90, 0x0A);
    EDIT_BYTE(0x5E581, 0xD7);
    EDIT_BYTE(0x5E582, 0x23);
    EDIT_BYTE(0x5E583, 0x3D);
    EDIT_BYTE(0x5EB70, 0x01);
    EDIT_BYTE(0x5EB80, 0x91);
    EDIT_BYTE(0x5EB81, 0xED);
    EDIT_BYTE(0x5EB82, 0x5C);
    EDIT_BYTE(0x5EB83, 0x3F);
}

// The same offsets work for both fairy ocarina and ocarina of time,
// so we will just reuse this function for both
static void CustomModel_SetOcarinaToRGBA565(void* ocarinaCMB) {
    char* BASE_ = (char*)ocarinaCMB;

    EDIT_BYTE(0x3F2, 0x01);
    EDIT_BYTE(0x3F8, 0x5A);
}

static void CustomModel_SetBossKeyToRGBA565(void* bossKeyCMB) {
    char* BASE_ = (char*)bossKeyCMB;

    EDIT_BYTE(0x43D, 0x10);
    EDIT_BYTE(0x442, 0x01);
    EDIT_BYTE(0x448, 0x5B);
    EDIT_BYTE(0x44A, 0x00);
    EDIT_BYTE(0x44B, 0x00);
}

static void CustomModel_EditTriforce(void* triforceCMB) {
    char* BASE_ = (char*)triforceCMB;

    // Set number of vertices from 0x120 to 0x60 so only one triangle will be drawn.
    EDIT_BYTE(0x3FC, 0x60);
    EDIT_BYTE(0x3FD, 0x00);
}

void CustomModel_Update(void) {
    // Make sure custom_assets is loaded
    if (ExtendedObject_GetIndex(&gGlobalContext->objectCtx, OBJECT_CUSTOM_GENERAL_ASSETS) < 0) {
        ExtendedObject_Spawn(&gGlobalContext->objectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    }
}

void CustomModels_EditItemCMB(void* ZARBuf, u16 objectId, s8 special) {
    void* cmb;

    switch (objectId) {
        case OBJECT_CUSTOM_DOUBLE_DEFENSE:
            cmb = ((char*)ZARBuf) + 0xA4;
            CustomModel_EditHeartContainerToDoubleDefense(cmb);
            break;
        case OBJECT_CUSTOM_CHILD_SONGS:
            cmb = ((char*)ZARBuf) + 0x2E60;
            CustomModel_SetOcarinaToRGBA565(cmb);
            break;
        case OBJECT_CUSTOM_ADULT_SONGS:
            cmb = ((char*)ZARBuf) + 0xE8;
            CustomModel_SetOcarinaToRGBA565(cmb);
            break;
        case OBJECT_CUSTOM_SMALL_KEY_FOREST:
        case OBJECT_CUSTOM_SMALL_KEY_FIRE:
        case OBJECT_CUSTOM_SMALL_KEY_WATER:
        case OBJECT_CUSTOM_SMALL_KEY_SHADOW:
        case OBJECT_CUSTOM_SMALL_KEY_BOTW:
        case OBJECT_CUSTOM_SMALL_KEY_SPIRIT:
        case OBJECT_CUSTOM_SMALL_KEY_FORTRESS:
        case OBJECT_CUSTOM_SMALL_KEY_GTG:
        case OBJECT_CUSTOM_SMALL_KEY_GANON:
            cmb = ((char*)ZARBuf) + 0x74;
            CustomModel_ApplyColorEditsToSmallKey(cmb, special);
            break;
        case OBJECT_CUSTOM_BOSS_KEYS:
            cmb = ((char*)ZARBuf) + 0x78;
            CustomModel_SetBossKeyToRGBA565(cmb);
            break;
        case OBJECT_CUSTOM_TRIFORCE_PIECE:
            cmb = ((char*)ZARBuf) + 0xF0;
            CustomModel_EditTriforce(cmb);
            break;
    }
}

void CustomModels_ApplyItemCMAB(SkeletonAnimationModel* model, u16 objectId, s8 special) {
    void* cmabMan;

    switch (objectId) {
        case OBJECT_CUSTOM_CHILD_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_CHILD_SONG);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode  = 0;
            model->unk_0C->curFrame  = special;
            break;
        case OBJECT_CUSTOM_ADULT_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_ADULT_SONG);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode  = 0;
            model->unk_0C->curFrame  = special;
            break;
        case OBJECT_CUSTOM_BOSS_KEYS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_BOSS_KEY);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode  = 0;
            model->unk_0C->curFrame  = special;
            break;
    }
}

void CustomModels_UpdateMatrix(nn_math_MTX34* modelMtx, u16 objectId) {
    f32 scale;
    Vec3f posOffset;

    switch (objectId) {
        case OBJECT_CUSTOM_TRIFORCE_PIECE:
            scale     = 0.05f;
            posOffset = (Vec3f){ 0.0f, -800.0f, 0.0f };
            break;
        default:
            return;
    }

    nn_math_MTX44 scaleMtx = { 0 };
    scaleMtx.data[0][0]    = scale;
    scaleMtx.data[1][1]    = scale;
    scaleMtx.data[2][2]    = scale;
    scaleMtx.data[3][3]    = 1.0f;

    Matrix_Multiply(modelMtx, modelMtx, &scaleMtx);
    Matrix_UpdatePosition(modelMtx, modelMtx, &posOffset);
}
