#pragma once

#include <3ds.h>
#include <string>

namespace CustomMessages {
    void CreateMessage(u32 textId, u32 unk_04, u32 unk_08, u32 unk_0C,
                       std::string englishText, std::string frenchText, std::string spanishText);

    u32 NumMessages();

    std::pair<const char*, u32> RawMessageEntryData();
    std::pair<const char*, u32> RawMessageData();

    void CreateAlwaysIncludedMessages();

    std::string MESSAGE_END();
    std::string WAIT_FOR_INPUT();
    std::string HORIZONTAL_SPACE(u8 x);
    std::string INSTANT_TEXT_ON();
    std::string INSTANT_TEXT_OFF();
    std::string SHOP_MESSAGE_BOX();
    std::string EVENT_TRIGGER();
    std::string DELAY_FRAMES(u8 x);
    std::string CLOSE_AFTER(u8 x);
    std::string PLAYER_NAME();
    std::string PLAY_OCARINA();
    std::string ITEM_OBTAINED(u8 x);
    std::string SET_SPEED(u8 x);
    std::string SKULLTULAS_DESTROYED();
    std::string CURRENT_TIME();
    std::string UNSKIPPABLE();
    std::string TWO_WAY_CHOICE();
    std::string NEWLINE();
    std::string COLOR(u8 x);
    std::string CENTER_TEXT();
}
