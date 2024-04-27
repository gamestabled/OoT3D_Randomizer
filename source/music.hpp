#pragma once

#include <array>
#include <vector>

#include <3ds.h>

namespace Music {

// Index Variant
// Shuffles and replaces sequence indexes with a patch
// Does not support custom music, but does not require the original archive to be provided

const u32 BGM_BASE  = 0x1000585;
const int SEQ_COUNT = 85;

enum SeqType {
    SEQ_NOSHUFFLE  = 0,
    SEQ_BGM_WORLD  = 1 << 0,
    SEQ_BGM_EVENT  = 1 << 1,
    SEQ_BGM_BATTLE = 1 << 2,
    SEQ_OCARINA    = 1 << 3,
    SEQ_FANFARE    = 1 << 4,
    // A soundtrack in this category has the issue where if another soundtrack that isn't
    // in this category overrides it, it will keep playing when it should be stopped.
    // For example when beating a mini-boss or finishing the zora diving game.
    SEQ_BGM_ERROR = 1 << 5,
};

extern const std::array<SeqType, SEQ_COUNT> seqTypesMusic;
extern std::array<u32, SEQ_COUNT> seqOverridesMusic;

void InitMusicRandomizer();
void ShuffleSequences(int type);

// Archive Variant
// Shuffles and replaces files in the original sound archive
// Requires the original archive to be provided, but avoids certain bugs and supports custom music

typedef enum {
    SARSHUFFLE_SUCCESS,
    SARSHUFFLE_NO_DIRS,
    SARSHUFFLE_SDMC_ARCHIVE_FAIL,
    SARSHUFFLE_BCSAR_NOT_FOUND,
} ArchiveShuffleResult;

extern bool archiveFound;
extern bool musicDirsCreated;
void CreateMusicDirectories(FS_Archive sdmcArchive);
void DeleteOldArchive();
int ShuffleMusic_Archive();

} // namespace Music
