#include "z3D/z3D.h"
#include "string.h"
#include "custom_models.h"

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

void CustomModel_EditFairyOcarinaToZeldasLullaby(void* fairyOcarinaCMB) {
    static u8 zeldasLullabyTex[] = {
        #include "zeldas_lullaby_texture.inc.c"
    };

    void* fairyOcarinaTex0 = (((char*)fairyOcarinaCMB) + 0x1700);

    memcpy(fairyOcarinaTex0, zeldasLullabyTex, 0x2000);
}

void CustomModel_EditFairyOcarinaToSariasSong(void* fairyOcarinaCMB) {
    static u8 sariasSongTex[] = {
        #include "sarias_song_texture.inc.c"
    };

    void* fairyOcarinaTex0 = (((char*)fairyOcarinaCMB) + 0x1700);

    memcpy(fairyOcarinaTex0, sariasSongTex, 0x2000);
}

void CustomModel_EditFairyOcarinaToSunsSong(void* fairyOcarinaCMB) {
    static u8 sunsSongTex[] = {
        #include "suns_song_texture.inc.c"
    };

    void* fairyOcarinaTex0 = (((char*)fairyOcarinaCMB) + 0x1700);

    memcpy(fairyOcarinaTex0, sunsSongTex, 0x2000);
}

void CustomModel_EditFairyOcarinaToEponasSong(void* fairyOcarinaCMB) {
    static u8 eponasSongTex[] = {
        #include "eponas_song_texture.inc.c"
    };

    void* fairyOcarinaTex0 = (((char*)fairyOcarinaCMB) + 0x1700);

    memcpy(fairyOcarinaTex0, eponasSongTex, 0x2000);
}

void CustomModel_EditFairyOcarinaToSongOfStorms(void* fairyOcarinaCMB) {
    static u8 songOfStormsTex[] = {
        #include "song_of_storms_texture.inc.c"
    };

    void* fairyOcarinaTex0 = (((char*)fairyOcarinaCMB) + 0x1700);

    memcpy(fairyOcarinaTex0, songOfStormsTex, 0x2000);
}

void CustomModel_EditFairyOcarinaToSongOfTime(void* fairyOcarinaCMB) {
    static u8 songOfTimeTex[] = {
        #include "song_of_time_texture.inc.c"
    };

    void* fairyOcarinaTex0 = (((char*)fairyOcarinaCMB) + 0x1700);

    memcpy(fairyOcarinaTex0, songOfTimeTex, 0x2000);
}

void CustomModel_EditOcarinaOfTimeToMinuetOfForest(void* ocarinaOfTimeCMB) {
    static u8 minuetOfForestTex[] = {
        #include "minuet_of_forest_texture.inc.c"
    };

    void* ocarinaOfTimeTex0 = (((char*)ocarinaOfTimeCMB) + 0x1700);

    memcpy(ocarinaOfTimeTex0, minuetOfForestTex, 0x2000);
}

void CustomModel_EditOcarinaOfTimeToBoleroOfFire(void* ocarinaOfTimeCMB) {
    static u8 boleroOfFireTex[] = {
        #include "bolero_of_fire_texture.inc.c"
    };

    void* ocarinaOfTimeTex0 = (((char*)ocarinaOfTimeCMB) + 0x1700);

    memcpy(ocarinaOfTimeTex0, boleroOfFireTex, 0x2000);
}

void CustomModel_EditOcarinaOfTimeToSerenadeOfWater(void* ocarinaOfTimeCMB) {
    static u8 serenadeOfWaterTex[] = {
        #include "serenade_of_water_texture.inc.c"
    };

    void* ocarinaOfTimeTex0 = (((char*)ocarinaOfTimeCMB) + 0x1700);

    memcpy(ocarinaOfTimeTex0, serenadeOfWaterTex, 0x2000);
}

void CustomModel_EditOcarinaOfTimeToRequiemOfSpirit(void* ocarinaOfTimeCMB) {
    static u8 requiemOfSpiritTex[] = {
        #include "requiem_of_spirit_texture.inc.c"
    };

    void* ocarinaOfTimeTex0 = (((char*)ocarinaOfTimeCMB) + 0x1700);

    memcpy(ocarinaOfTimeTex0, requiemOfSpiritTex, 0x2000);
}

void CustomModel_EditOcarinaOfTimeToNocturneOfShadow(void* ocarinaOfTimeCMB) {
    static u8 nocturneOfShadowTex[] = {
        #include "nocturne_of_shadow_texture.inc.c"
    };

    void* ocarinaOfTimeTex0 = (((char*)ocarinaOfTimeCMB) + 0x1700);

    memcpy(ocarinaOfTimeTex0, nocturneOfShadowTex, 0x2000);
}

void CustomModel_EditOcarinaOfTimeToPreludeOfLight(void* ocarinaOfTimeCMB) {
    static u8 preludeOfLightTex[] = {
        #include "prelude_of_light_texture.inc.c"
    };

    void* ocarinaOfTimeTex0 = (((char*)ocarinaOfTimeCMB) + 0x1700);

    memcpy(ocarinaOfTimeTex0, preludeOfLightTex, 0x2000);
}

#include "title_screen_assets.c"

void CustomModel_EditTitleScreenLogo(void* titleScreenZAR) {
    char* BASE_ = (char*)titleScreenZAR;

    char* readCursor;
    char* writeCursor;
    readCursor = (BASE_ + 0x3F12C);
    writeCursor = (BASE_ + 0x8610C);
    memcpy(writeCursor, readCursor, 0x1FBA0); // copy 3F12C-5ECCC
    readCursor = (BASE_ + 0xF12C);
    writeCursor = (BASE_ + 0x5610C);
    memcpy(writeCursor, readCursor, 0x30000); // copy  F12C-3F12C

    readCursor = (BASE_ + 0xF108);
    writeCursor = (BASE_ + 0x560F8);
    memcpy(writeCursor, readCursor, 0x14); // copy F108-F11C
    readCursor = (BASE_ + 0xDB6C);
    writeCursor = (BASE_ + 0x54B6C);
    memcpy(writeCursor, readCursor, 0x158C);

    // copy in the extended texture
    writeCursor = (((char*)titleScreenZAR) + 0x06EC);
    memcpy(writeCursor, titleScreenEditedTex0, 0x54480);

    // all the other edits
    EDIT_BYTE(0x0004, 0xAC); EDIT_BYTE(0x0005, 0x5C); EDIT_BYTE(0x0006, 0x0A);

    EDIT_BYTE(0x00A1, 0x45); EDIT_BYTE(0x00A2, 0x01); EDIT_BYTE(0x00A3, 0x00);
    EDIT_BYTE(0x00A4, 0xE8); EDIT_BYTE(0x00A5, 0x00); EDIT_BYTE(0x00A6, 0x00); EDIT_BYTE(0x00A7, 0x00);
    EDIT_BYTE(0x00A8, 0x80); EDIT_BYTE(0x00A9, 0x04); EDIT_BYTE(0x00AA, 0x04); EDIT_BYTE(0x00AB, 0x00);
    EDIT_BYTE(0x00AC, 0xFC); EDIT_BYTE(0x00AD, 0x00); EDIT_BYTE(0x00AE, 0x00); EDIT_BYTE(0x00AF, 0x00);
    EDIT_BYTE(0x00B0, 0xE0); EDIT_BYTE(0x00B1, 0x76);

    EDIT_BYTE(0x01CD, 0x46); EDIT_BYTE(0x01CE, 0x01); EDIT_BYTE(0x01CF, 0x00);
    EDIT_BYTE(0x01D0, 0x6C); EDIT_BYTE(0x01D1, 0x4B); EDIT_BYTE(0x01D2, 0x05); EDIT_BYTE(0x01D3, 0x00);
    EDIT_BYTE(0x01D4, 0x4C); EDIT_BYTE(0x01D5, 0xC2); EDIT_BYTE(0x01D6, 0x07); EDIT_BYTE(0x01D7, 0x00);
    EDIT_BYTE(0x01D8, 0xCC); EDIT_BYTE(0x01D9, 0x3C); EDIT_BYTE(0x01DA, 0x0A); EDIT_BYTE(0x01DB, 0x00);
    EDIT_BYTE(0x01DC, 0xF8); EDIT_BYTE(0x01DD, 0x44); EDIT_BYTE(0x01DE, 0x0A); EDIT_BYTE(0x01DF, 0x00);
    EDIT_BYTE(0x01E0, 0x78); EDIT_BYTE(0x01E1, 0x4B); EDIT_BYTE(0x01E2, 0x0A); EDIT_BYTE(0x01E3, 0x00);
    EDIT_BYTE(0x01E4, 0x8C); EDIT_BYTE(0x01E5, 0x52); EDIT_BYTE(0x01E6, 0x0A); EDIT_BYTE(0x01E7, 0x00);
    EDIT_BYTE(0x01E8, 0x9C); EDIT_BYTE(0x01E9, 0x57); EDIT_BYTE(0x01EA, 0x0A);

    EDIT_BYTE(0x0455, 0x00); EDIT_BYTE(0x0456, 0x01); EDIT_BYTE(0x0457, 0x00);
    EDIT_BYTE(0x0458, 0x01); EDIT_BYTE(0x0459, 0x00); EDIT_BYTE(0x045A, 0x00); EDIT_BYTE(0x045B, 0x00);
    EDIT_BYTE(0x045C, 0x80); EDIT_BYTE(0x045D, 0x00); EDIT_BYTE(0x045E, 0x80); EDIT_BYTE(0x045F, 0x00);
    EDIT_BYTE(0x0460, 0x52); EDIT_BYTE(0x0461, 0x67); EDIT_BYTE(0x0462, 0x01); EDIT_BYTE(0x0463, 0x14);
    EDIT_BYTE(0x0464, 0x00); EDIT_BYTE(0x0465, 0x00); EDIT_BYTE(0x0466, 0x00); EDIT_BYTE(0x0467, 0x00);
    EDIT_BYTE(0x0468, 0x00); EDIT_BYTE(0x0469, 0x40); EDIT_BYTE(0x046A, 0x00); EDIT_BYTE(0x046B, 0x00);
    EDIT_BYTE(0x046C, 0x01); EDIT_BYTE(0x046D, 0x00); EDIT_BYTE(0x046E, 0x00); EDIT_BYTE(0x046F, 0x00);
    EDIT_BYTE(0x0470, 0x40); EDIT_BYTE(0x0471, 0x00); EDIT_BYTE(0x0472, 0x40); EDIT_BYTE(0x0473, 0x00);
    EDIT_BYTE(0x0474, 0x52); EDIT_BYTE(0x0475, 0x67); EDIT_BYTE(0x0476, 0x01); EDIT_BYTE(0x0477, 0x14);
    EDIT_BYTE(0x0478, 0x00); EDIT_BYTE(0x0479, 0x00); EDIT_BYTE(0x047A, 0x01); EDIT_BYTE(0x047B, 0x00);
    EDIT_BYTE(0x047C, 0x01); EDIT_BYTE(0x047D, 0x00); EDIT_BYTE(0x047E, 0x00); EDIT_BYTE(0x047F, 0x00);
    EDIT_BYTE(0x0480, 0x40); EDIT_BYTE(0x0481, 0x00); EDIT_BYTE(0x0482, 0x40); EDIT_BYTE(0x0483, 0x00);
    EDIT_BYTE(0x0484, 0x52);

    EDIT_BYTE(0x004F3, 0x40); EDIT_BYTE(0x562FB, 0x40); EDIT_BYTE(0x5643B, 0x40); EDIT_BYTE(0x5657B, 0x40);
    EDIT_BYTE(0x566BB, 0x40); EDIT_BYTE(0x567FB, 0x40); EDIT_BYTE(0x5693B, 0x40); EDIT_BYTE(0x56A7B, 0x40);
    EDIT_BYTE(0x56BBB, 0x40); EDIT_BYTE(0x56CFB, 0x40); EDIT_BYTE(0x56E3B, 0x40); EDIT_BYTE(0x56F7B, 0x40);
    EDIT_BYTE(0x570BB, 0x40); EDIT_BYTE(0x571FB, 0x40); EDIT_BYTE(0x5733B, 0x40); EDIT_BYTE(0x5747B, 0x40);
    EDIT_BYTE(0x575BB, 0x40); EDIT_BYTE(0x576FB, 0x40); EDIT_BYTE(0x5783B, 0x40); EDIT_BYTE(0x5797B, 0x40);
    EDIT_BYTE(0x57ABB, 0x40); EDIT_BYTE(0x57BFB, 0x40); EDIT_BYTE(0x7DBD3, 0x40); EDIT_BYTE(0x7DD13, 0x40);
    EDIT_BYTE(0x7DE53, 0x40); EDIT_BYTE(0x7DF93, 0x40); EDIT_BYTE(0x7E0D3, 0x40); EDIT_BYTE(0x7E213, 0x40);
    EDIT_BYTE(0x7E353, 0x40); EDIT_BYTE(0x7E493, 0x40); EDIT_BYTE(0x7E5D3, 0x40); EDIT_BYTE(0x7E713, 0x40);
    EDIT_BYTE(0x7E853, 0x40); EDIT_BYTE(0x7E993, 0x40); EDIT_BYTE(0x7EAD3, 0x40); EDIT_BYTE(0x7EC13, 0x40);
    EDIT_BYTE(0x7ED53, 0x40); EDIT_BYTE(0x7EE93, 0x40); EDIT_BYTE(0x7EFD3, 0x40); EDIT_BYTE(0x7F113, 0x40);
    EDIT_BYTE(0x7F253, 0x40); EDIT_BYTE(0x7F393, 0x40); EDIT_BYTE(0x7F4D3, 0x40); EDIT_BYTE(0x7F613, 0x40);

    writeCursor = (((char*)titleScreenZAR) + 0x60E7E);
    memcpy(writeCursor, titleScreenEditedTex1, 0xF60);
    writeCursor = (((char*)titleScreenZAR) + 0x888FE);
    memcpy(writeCursor, titleScreenEditedTex1, 0xF60);

    writeCursor = (((char*)titleScreenZAR) + 0x633B9);
    memcpy(writeCursor, titleScreenEditedTex2, 0x209);
    writeCursor = (((char*)titleScreenZAR) + 0x8AE39);
    memcpy(writeCursor, titleScreenEditedTex2, 0x209);

    writeCursor = (((char*)titleScreenZAR) + 0x63B75);
    memcpy(writeCursor, titleScreenEditedTex3, 0x2B5);
    writeCursor = (((char*)titleScreenZAR) + 0x8B5F5);
    memcpy(writeCursor, titleScreenEditedTex3, 0x2B5);

    writeCursor = (((char*)titleScreenZAR) + 0x643B8);
    memcpy(writeCursor, titleScreenEditedTex4, 0x266);
    writeCursor = (((char*)titleScreenZAR) + 0x8BE38);
    memcpy(writeCursor, titleScreenEditedTex4, 0x266);

    writeCursor = (((char*)titleScreenZAR) + 0x64B6E);
    memcpy(writeCursor, titleScreenEditedTex5, 0x208);
    writeCursor = (((char*)titleScreenZAR) + 0x8C5EE);
    memcpy(writeCursor, titleScreenEditedTex5, 0x208);
}
