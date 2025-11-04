#include "ocarina_notes.h"
#include "savefile.h"
#include "settings.h"

// Values to be written to OcarinaNote.pitch for each button.
const u8 notePitches[5] = {
    [OCARINA_BUTTON_L] = 0x2, [OCARINA_BUTTON_R] = 0x5, [OCARINA_BUTTON_Y] = 0x9,
    [OCARINA_BUTTON_X] = 0xB, [OCARINA_BUTTON_A] = 0xE,
};

// Used to convert an OcarinaSongId to an index for the song list visible while playing the ocarina.
const u8 menuSongIds[12] = {
    [OCARINA_SONG_MINUET] = 2,   [OCARINA_SONG_BOLERO] = 6,   [OCARINA_SONG_SERENADE] = 10, [OCARINA_SONG_REQUIEM] = 3,
    [OCARINA_SONG_NOCTURNE] = 7, [OCARINA_SONG_PRELUDE] = 11, [OCARINA_SONG_SARIAS] = 8,    [OCARINA_SONG_EPONAS] = 4,
    [OCARINA_SONG_LULLABY] = 0,  [OCARINA_SONG_SUNS] = 1,     [OCARINA_SONG_TIME] = 5,      [OCARINA_SONG_STORMS] = 9,
};

// Used to store the button sequence for each song with u32 values instead of u8,
// in order to override gOcarinaMenuSongNoteSequences
u32 rMenuSongsOverrides[12][8] = { 0 };

void OcarinaNotes_Init(void) {
    if (gSettingsContext.randomSongNotes == OFF) {
        return;
    }

    for (u32 songId = 0; songId < 12; songId++) {

        OcarinaSongButtonSequence songBtns = gOcarinaSongButtons[songId];

        // set playback data
        OcarinaNote* songNotes = sOcarinaSongNotes[songId];
        u32 noteIndex          = 0;
        for (u32 btnIndex = 0; btnIndex < songBtns.length; btnIndex++) {
            // set menu song override data
            rMenuSongsOverrides[songId][btnIndex] = songBtns.buttons[btnIndex];

            // add very short pause if this note is the same as the previous one
            if (btnIndex > 0 && songBtns.buttons[btnIndex] == songBtns.buttons[btnIndex - 1]) {
                songNotes[noteIndex].pitch  = 0xFF;
                songNotes[noteIndex].length = 0x1;
                noteIndex++;
            }

            songNotes[noteIndex].pitch  = notePitches[songBtns.buttons[btnIndex]];
            songNotes[noteIndex].length = 0x24; // fixed note length

            noteIndex++;
        }

        // Set final note to mark end of sequence
        songNotes[noteIndex].pitch  = 0xFF;
        songNotes[noteIndex].length = 0;

        // override menu data
        gOcarinaMenuSongLengths[menuSongIds[songId]]       = songBtns.length;
        gOcarinaMenuSongNoteSequences[menuSongIds[songId]] = rMenuSongsOverrides[songId];
    }
}

s32 OcarinaNotes_IsButtonOwned(OcarinaNoteButton button) {
    return (gSettingsContext.shuffleOcarinaButtons == OFF) ||
           (gExtSaveData.extInf[EXTINF_OCARINA_BUTTONS] & (1 << button));
}

void OcarinaNotes_RegisterButtonOwned(OcarinaNoteButton button) {
    gExtSaveData.extInf[EXTINF_OCARINA_BUTTONS] |= (1 << button);
}

void OcarinaNotes_MoveButtons(void* spriteStruct, Vec2f* posOffset, u32 unk, u32 spriteIndex) {
    if (spriteStruct != OcarinaUIStruct) {
        return;
    }

    u8 shouldDraw = TRUE;

    switch (spriteIndex) {
        case OCS_L_BG_L:
        case OCS_L_BG_M:
        case OCS_L_BG_R:
        case OCS_L_BUTTON:
        case OCS_L_LETTER:
        case OCS_L_SHADOW_L:
        case OCS_L_SHADOW_M:
        case OCS_L_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_L);
            break;
        case OCS_R_BG_L:
        case OCS_R_BG_M:
        case OCS_R_BG_R:
        case OCS_R_BUTTON:
        case OCS_R_LETTER:
        case OCS_R_SHADOW_L:
        case OCS_R_SHADOW_M:
        case OCS_R_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_R);
            break;
        case OCS_X_BG_L:
        case OCS_X_BG_R:
        case OCS_X_BUTTON:
        case OCS_X_LETTER:
        case OCS_X_SHADOW_L:
        case OCS_X_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_X);
            break;
        case OCS_Y_BG_L:
        case OCS_Y_BG_R:
        case OCS_Y_BUTTON:
        case OCS_Y_LETTER:
        case OCS_Y_SHADOW_L:
        case OCS_Y_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_Y);
            break;
        case OCS_A_BG_L:
        case OCS_A_BG_R:
        case OCS_A_BUTTON:
        case OCS_A_LETTER:
        case OCS_A_SHADOW_L:
        case OCS_A_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_A);
            break;
    }

    if (shouldDraw == FALSE) {
        // yeet sprite off-screen
        posOffset->x += 500.0f;
        posOffset->y += 500.0f;
    }
}

u32 OcarinaNotes_HandleInputs(u32 ocarinaInputs) {
    static const u32 btnShifts[5] = { 7, 9, 11, 10, 8 }; // not the same offsets as the btn_t struct
    u32 ownedBtnsMask             = 0;
    for (OcarinaNoteButton btn = 0; btn < 5; btn++) {
        ownedBtnsMask |= (OcarinaNotes_IsButtonOwned(btn) << btnShifts[btn]);
    }
    ocarinaInputs &= ownedBtnsMask;
    return ocarinaInputs;
}
