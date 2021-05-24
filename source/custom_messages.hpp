#pragma once

#include <3ds.h>
#include <string>
#include <utility>
#include <vector>

#include "text.hpp"

#define QM_WHITE  0x00
#define QM_RED    0x41
#define QM_GREEN  0x42
#define QM_BLUE   0x43
#define QM_LBLUE  0x44
#define QM_PINK   0x45
#define QM_YELLOW 0x46
#define QM_BLACK  0x47

namespace CustomMessages {
    void CreateMessage(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition,
                       std::string englishText, std::string frenchText, std::string spanishText);
    void CreateMessageFromTextObject(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition, const Text& text);

    u32 NumMessages();

    std::pair<const char*, u32> RawMessageEntryData();
    std::pair<const char*, u32> RawMessageData();

    void CreateAlwaysIncludedMessages();
    Text AddColorsAndFormat(Text text, const std::vector<u8>& colors = {});
}
