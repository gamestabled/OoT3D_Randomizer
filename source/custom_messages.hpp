#pragma once

#include <3ds.h>
#include <string>
#include <utility>
#include <vector>

#include "text.hpp"

#define QM_WHITE 0x00
#define QM_RED 0x41
#define QM_GREEN 0x42
#define QM_BLUE 0x43
#define QM_LBLUE 0x44
#define QM_PINK 0x45
#define QM_YELLOW 0x46
#define QM_BLACK 0x47

namespace CustomMessages {
void CreateMessage(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition, std::string englishText,
                   std::string frenchText, std::string spanishText, std::string italianText, std::string germanText);
void CreateMessageFromTextObject(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition, const Text& text);

u32 NumMessages();

std::pair<const char*, u32> RawMessageEntryData();
std::pair<const char*, u32> RawMessageData();

void CreateAlwaysIncludedMessages();
std::vector<Text> CreateBaseCompassTexts();
Text AddColorsAndFormat(Text text, const std::vector<u8>& colors = {});
void ClearMessages();

std::string MESSAGE_END();
std::string WAIT_FOR_INPUT();
std::string HORIZONTAL_SPACE(u8 x);
std::string GO_TO(u16 x); // "Go To Statement Considered Harmful"
std::string INSTANT_TEXT_ON();
std::string INSTANT_TEXT_OFF();
std::string SHOP_MESSAGE_BOX();
std::string EVENT_TRIGGER();
std::string DELAY_FRAMES(u8 x);
std::string CLOSE_AFTER(u8 x);
std::string PLAYER_NAME();
std::string PLAY_OCARINA();
std::string PLAY_SFX(u16 x);
std::string ITEM_OBTAINED(u8 x);
std::string SET_SPEED(u8 x);
std::string SKULLTULAS_DESTROYED();
std::string CURRENT_TIME();
std::string UNSKIPPABLE();
std::string TWO_WAY_CHOICE();
std::string NEWLINE();
std::string COLOR(u8 x);
std::string CENTER_TEXT();
std::string IF_NOT_MQ();
std::string MQ_ELSE();
std::string MQ_END();
std::string TRIFORCE_PIECE_COUNT();
} // namespace CustomMessages
