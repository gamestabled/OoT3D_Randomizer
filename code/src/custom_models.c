#include "z3D/z3D.h"
#include "string.h"
#include "custom_models.h"

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
