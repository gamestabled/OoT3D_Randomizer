#pragma once

#include "s_sfx.h"

#include <3ds.h>
#include <array>
#include <vector>

namespace SFX {
extern const std::array<SeqType, SFX_COUNT> seqTypesSFX;

const SFXData& GetSFXData();

void InitSFXRandomizer();
void ShuffleSequences(bool shuffleCategorically);
} // namespace SFX
