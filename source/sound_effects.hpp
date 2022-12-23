#pragma once

#include <3ds.h>

#include <array>
#include <vector>

#include "../code/src/sfx.h"

namespace SFX {
extern const std::array<SeqType, SFX_COUNT> seqTypesSFX;

const SFXData& GetSFXData();

void InitSFXRandomizer();
void ShuffleSequences(bool shuffleCategorically);
} // namespace SFX
