#include <string>
#include <array>
#include "../code/src/ocarina_notes.h"

#define FROG_SONG_LENGTH 14

namespace OcarinaNotes {

extern const std::array<std::string, OCARINA_BUTTON_MAX> ButtonNames;
extern const std::array<std::string, OCARINA_SONG_MAX> SongNames;

extern OcarinaSongButtonSequence SongData[OCARINA_SONG_MAX];
extern u8 SongRequiredButtons[OCARINA_SONG_MAX];
extern u8 FrogSongNotes[FROG_SONG_LENGTH];

void GenerateSongList(void);

} // namespace OcarinaNotes
