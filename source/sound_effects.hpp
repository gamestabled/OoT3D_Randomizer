#pragma once

#include <array>
#include <vector>

#include <3ds.h>

namespace SFX {
    const u32 SFX_BASE = 0x1000001;
    const int SEQ_COUNT = 1388;

    enum SeqType {
        SEQ_NOSHUFFLE = 0,
        SEQ_PLAYER    = 1 << 0,
        SEQ_ITEM      = 1 << 1,
        SEQ_EVENT     = 1 << 2,
        SEQ_ENEMY     = 1 << 3,
        SEQ_SYSTEM    = 1 << 4,
        SEQ_OCARINA   = 1 << 5,
        SEQ_VOICEOVER = 1 << 6,
    };

    extern const std::array<SeqType, SEQ_COUNT> seqTypesSFX;
    extern std::array<u32, SEQ_COUNT> seqOverridesSFX;

    void InitSFXRandomizer();
    void ShuffleSequences(int type);
} // namespace SFX
