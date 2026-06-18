#ifndef _OCARINA_NOTES_H_
#define _OCARINA_NOTES_H_

#include "s_ocarina_notes.h"

#include "z3D/z3D.h"

// These values are one less than in OoT decomp
typedef enum OcarinaInstrumentId {
    OCARINA_INSTRUMENT_DEFAULT,
    OCARINA_INSTRUMENT_MALON,
    OCARINA_INSTRUMENT_WHISTLE,     // Impa
    OCARINA_INSTRUMENT_HARP,        // Sheik
    OCARINA_INSTRUMENT_GRIND_ORGAN, // Windmill Man
    OCARINA_INSTRUMENT_FLUTE,       // Skull Kid
    OCARINA_INSTRUMENT_MAX,
} OcarinaInstrumentId;

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

typedef struct {
    /* 0x0 */ u8 pitch;   // number of semitones above middle C
    /* 0x2 */ u16 length; // number of frames the note is sustained
    /* 0x4 */ u8 volume;
    /* 0x5 */ u8 vibrato;
    /* 0x6 */ s8 bend; // frequency multiplicative offset from the pitch
    /* 0x7 */ u8 bFlat4Flag;
} OcarinaNote; // size = 0x8

extern void* OcarinaUIStruct;

// sequence of notes to check when a song has been played
extern OcarinaSongButtonSequence gOcarinaSongButtons[];
// sequence of note data used for the playbacks (2D array of 20 notes for each song)
extern OcarinaNote gOcarinaSongNotes[][20];
// sequence of notes to display on the ocarina song list menu (array of pointers to arrays)
extern u32* gOcarinaMenuSongNoteSequences[];
extern u32 gOcarinaMenuSongLengths[];

void OcarinaNotes_Init(void);
s32 OcarinaNotes_IsButtonOwned(OcarinaNoteButton button);
void OcarinaNotes_RegisterButtonOwned(OcarinaNoteButton button);

#endif //_OCARINA_NOTES_H_
