#ifndef _OCARINA_NOTES_H_
#define _OCARINA_NOTES_H_

#include "../include/z3D/z3D.h"

typedef enum OcarinaNoteButton {
    OCARINA_BUTTON_L,
    OCARINA_BUTTON_R,
    OCARINA_BUTTON_Y,
    OCARINA_BUTTON_X,
    OCARINA_BUTTON_A,
    OCARINA_BUTTON_MAX,
} OcarinaNoteButton;

enum OcarinaSprites {
    OCS_L_BG_L = 0x3F,
    OCS_L_BG_M,
    OCS_L_BG_R,
    OCS_L_BUTTON,
    OCS_L_LETTER,
    OCS_R_BG_L,
    OCS_R_BG_M,
    OCS_R_BG_R,
    OCS_R_BUTTON,
    OCS_R_LETTER,
    OCS_X_BG_L,
    OCS_X_BG_R,
    OCS_X_BUTTON,
    OCS_X_LETTER,
    OCS_Y_BG_L,
    OCS_Y_BG_R,
    OCS_Y_BUTTON,
    OCS_Y_LETTER,
    OCS_A_BG_L,
    OCS_A_BG_R,
    OCS_A_BUTTON,
    OCS_A_LETTER,
    OCS_BACK_SHADOW_L,
    OCS_BACK_SHADOW_M,
    OCS_BACK_SHADOW_R,
    OCS_SONGS_SHADOW_L,
    OCS_SONGS_SHADOW_M,
    OCS_SONGS_SHADOW_R,
    OCS_L_SHADOW_L,
    OCS_L_SHADOW_M,
    OCS_L_SHADOW_R,
    OCS_R_SHADOW_L,
    OCS_R_SHADOW_M,
    OCS_R_SHADOW_R,
    OCS_X_SHADOW_L,
    OCS_X_SHADOW_R,
    OCS_Y_SHADOW_L,
    OCS_Y_SHADOW_R,
    OCS_A_SHADOW_L,
    OCS_A_SHADOW_R,
    OCS_YELLOW_MARKER_1,
    OCS_YELLOW_MARKER_2,
    OCS_YELLOW_MARKER_3,
    OCS_YELLOW_MARKER_4,
    OCS_YELLOW_MARKER_5,
}; // max 0x6C

typedef enum {
    OCARINA_SONG_MINUET,
    OCARINA_SONG_BOLERO,
    OCARINA_SONG_SERENADE,
    OCARINA_SONG_REQUIEM,
    OCARINA_SONG_NOCTURNE,
    OCARINA_SONG_PRELUDE,
    OCARINA_SONG_SARIAS,
    OCARINA_SONG_EPONAS,
    OCARINA_SONG_LULLABY,
    OCARINA_SONG_SUNS,
    OCARINA_SONG_TIME,
    OCARINA_SONG_STORMS,
    OCARINA_SONG_MAX,
} OcarinaSongId;

typedef struct {
    /* 0x0 */ u8 length;
    /* 0x1 */ u8 buttons[8];
} OcarinaSongButtonSequence; // size = 0x9

typedef struct {
    /* 0x0 */ u8 pitch;   // number of semitones above middle C
    /* 0x2 */ u16 length; // number of frames the note is sustained
    /* 0x4 */ u8 volume;
    /* 0x5 */ u8 vibrato;
    /* 0x6 */ s8 bend; // frequency multiplicative offset from the pitch
    /* 0x7 */ u8 bFlat4Flag;
} OcarinaNote; // size = 0x8

#define OcarinaUIStruct (*((void**)GAME_ADDR(0x5093EC)))

// sequence of notes to check when a song has been played
#define gOcarinaSongButtons ((OcarinaSongButtonSequence*)GAME_ADDR(0x54C222))
// sequence of note data used for the playbacks (2D array of 20 notes for each song)
#define sOcarinaSongNotes ((OcarinaNote(*)[20])GAME_ADDR(0x54B5F2))
// sequence of notes to display on the ocarina song list menu (array of pointers to arrays)
#define gOcarinaMenuSongNoteSequences ((u32**)GAME_ADDR(0x4D541C))
#define gOcarinaMenuSongLengths ((u32*)GAME_ADDR(0x4D53C8))

void OcarinaNotes_Init(void);
s32 OcarinaNotes_IsButtonOwned(OcarinaNoteButton button);
void OcarinaNotes_RegisterButtonOwned(OcarinaNoteButton button);

#endif //_OCARINA_NOTES_H_
