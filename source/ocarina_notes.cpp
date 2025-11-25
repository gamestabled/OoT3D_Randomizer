#include "ocarina_notes.hpp"
#include "settings.hpp"
#include "random.hpp"
#include <string.h>

namespace OcarinaNotes {

const std::array<std::string, OCARINA_BUTTON_MAX> ButtonNames = {
    "L", "R", "Y", "X", "A",
};
const std::array<std::string, OCARINA_SONG_MAX> SongNames = {
    "Minuet of Forest",   "Bolero of Fire",   "Serenade of Water", "Requiem of Spirit",
    "Nocturne of Shadow", "Prelude of Light", "Saria's Song",      "Epona's Song",
    "Zelda's Lullaby",    "Sun's Song",       "Song of Time",      "Song of Storms",
};

// clang-format off
static constexpr u8 sVanillaRequiredButtons[OCARINA_SONG_MAX] = {
    [OCARINA_SONG_MINUET]   = 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_A | 1 << OCARINA_BUTTON_X | 1 << OCARINA_BUTTON_Y,
    [OCARINA_SONG_BOLERO]   = 1 << OCARINA_BUTTON_R | 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_Y,
    [OCARINA_SONG_SERENADE] = 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_R | 1 << OCARINA_BUTTON_Y | 1 << OCARINA_BUTTON_X,
    [OCARINA_SONG_REQUIEM]  = 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_R | 1 << OCARINA_BUTTON_Y,
    [OCARINA_SONG_NOCTURNE] = 1 << OCARINA_BUTTON_X | 1 << OCARINA_BUTTON_Y | 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_R,
    [OCARINA_SONG_PRELUDE]  = 1 << OCARINA_BUTTON_A | 1 << OCARINA_BUTTON_Y | 1 << OCARINA_BUTTON_X,
    [OCARINA_SONG_SARIAS]   = 1 << OCARINA_BUTTON_R | 1 << OCARINA_BUTTON_Y | 1 << OCARINA_BUTTON_X,
    [OCARINA_SONG_EPONAS]   = 1 << OCARINA_BUTTON_A | 1 << OCARINA_BUTTON_X | 1 << OCARINA_BUTTON_Y,
    [OCARINA_SONG_LULLABY]  = 1 << OCARINA_BUTTON_X | 1 << OCARINA_BUTTON_A | 1 << OCARINA_BUTTON_Y,
    [OCARINA_SONG_SUNS]     = 1 << OCARINA_BUTTON_Y | 1 << OCARINA_BUTTON_R | 1 << OCARINA_BUTTON_A,
    [OCARINA_SONG_TIME]     = 1 << OCARINA_BUTTON_Y | 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_R,
    [OCARINA_SONG_STORMS]   = 1 << OCARINA_BUTTON_L | 1 << OCARINA_BUTTON_R | 1 << OCARINA_BUTTON_A,
};
// clang-format on

OcarinaSongButtonSequence SongData[OCARINA_SONG_MAX];
u8 SongRequiredButtons[OCARINA_SONG_MAX];
u8 FrogSongNotes[FROG_SONG_LENGTH];

static void RandomizeNoteSequence(u8 noteSequence[], u8 songLength) {
    for (u32 noteIndex = 0; noteIndex < songLength; noteIndex++) {
        noteSequence[noteIndex] = Random(OCARINA_BUTTON_L, OCARINA_BUTTON_MAX);
    }
}

static bool IsValidSong(OcarinaSongButtonSequence song) {
    // Check if this song contains or is contained by another song.
    for (OcarinaSongButtonSequence otherSong : SongData) {
        if (otherSong.length == 0)
            break;

        std::string songStr(reinterpret_cast<char*>(song.buttons), song.length);
        std::string otherSongStr(reinterpret_cast<char*>(otherSong.buttons), otherSong.length);

        if (songStr.find(otherSongStr) != std::string::npos || otherSongStr.find(songStr) != std::string::npos) {
            return false;
        }
    }
    return true;
}

void GenerateSongList(void) {
    // Reset structs
    memset(&SongData, 0, sizeof(SongData));
    memcpy(&SongRequiredButtons, &sVanillaRequiredButtons, sizeof(SongRequiredButtons));

    if (!Settings::RandomSongNotes) {
        return;
    }
    // Generate random songs
    for (u8 songId = OCARINA_SONG_MINUET; songId < OCARINA_SONG_MAX; songId++) {
        for (u32 attempts = 0; attempts < 1000; attempts++) {
            OcarinaSongButtonSequence randomSong = { 0 };
            if (songId <= OCARINA_SONG_PRELUDE) {
                // warp songs: random length between 5 and 8
                randomSong.length = Random(5, 9);
                RandomizeNoteSequence(randomSong.buttons, randomSong.length);
            } else {
                // regular songs: 3 notes repeated twice
                RandomizeNoteSequence(randomSong.buttons, 3);
                randomSong.length     = 6;
                randomSong.buttons[3] = randomSong.buttons[0];
                randomSong.buttons[4] = randomSong.buttons[1];
                randomSong.buttons[5] = randomSong.buttons[2];
            }

            if (IsValidSong(randomSong)) {
                SongData[songId] = randomSong;
                for (u32 i = 0; i < randomSong.length; i++) {
                    SongRequiredButtons[songId] |= (1 << randomSong.buttons[i]);
                }
                break;
            }
        }
    }

    RandomizeNoteSequence(FrogSongNotes, FROG_SONG_LENGTH);
}

} // namespace OcarinaNotes
