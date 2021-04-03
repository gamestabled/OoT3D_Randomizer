#pragma once

#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "../code/src/message.h"

using namespace std::literals::string_literals;

namespace CustomMessages {
    void CreateMessage(u32 textId, u32 unk_04, u32 unk_08, u32 unk_0C, 
        std::string englishText, std::string frenchText, std::string spanishText);

    u32 NumMessages(void);

    std::pair<const char*, u32> RawMessageEntryData(void);
    std::pair<const char*, u32> RawMessageData(void);

    void CreateAlwaysIncludedMessages(void);

    const std::string MESSAGE_END();
    const std::string WAIT_FOR_INPUT();
    const std::string HORIZONTAL_SPACE(u8 x);
    const std::string INSTANT_TEXT_ON();
    const std::string INSTANT_TEXT_OFF();
    const std::string SHOP_MESSAGE_BOX();
    const std::string EVENT_TRIGGER();
    const std::string DELAY_FRAMES(u8 x);
    const std::string CLOSE_AFTER(u8 x);
    const std::string PLAYER_NAME();
    const std::string PLAY_OCARINA();
    const std::string ITEM_OBTAINED(u8 x);
    const std::string SET_SPEED(u8 x);
    const std::string SKULLTULAS_DESTROYED();
    const std::string CURRENT_TIME();
    const std::string UNSKIPPABLE();
    const std::string TWO_WAY_CHOICE();
    const std::string NEWLINE();
    const std::string COLOR(u8 x);
    const std::string CENTER_TEXT();

    static constexpr u8 QM_WHITE  = 0x00;
    static constexpr u8 QM_RED    = 0x41;
    static constexpr u8 QM_GREEN  = 0x42;
    static constexpr u8 QM_BLUE   = 0x43;
    static constexpr u8 QM_LBLUE  = 0x44;
    static constexpr u8 QM_PINK   = 0x45;
    static constexpr u8 QM_YELLOW = 0x46;
    static constexpr u8 QM_BLACK  = 0x47;

    class MessageEntryComp {
    public:
        inline bool operator()(const MessageEntry& lhs, const MessageEntry& rhs) const {
            return lhs.id < rhs.id;
        }
    };
}
