#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "../include/z3D/z3D.h"

typedef struct {
    // In the true file format, offset is the offset into the QM file.
    // In randomizer, offset will be a pointer to the text in the game's address space.
    // Since these pointers will be much larger as u32 than the original script's offsets,
    // We will be able to distinguish between original and custom text using their numerical value.
    const char* offset;
    u32 length;
} MessageLanguageInfo;

typedef enum {
    /* 0x00 */ JAPANESE_J,
    /* 0x01 */ ENGLISH_U,
    /* 0x02 */ ENGLISH_E,
    /* 0x03 */ GERMAN_E,
    /* 0x04 */ FRENCH_E,
    /* 0x05 */ FRENCH_U,
    /* 0x06 */ SPANISH_E,
    /* 0x07 */ SPANISH_U,
    /* 0x08 */ ITALIAN_E,
    /* 0x09 */ DUTCH_E,
} MessageLanguage;

typedef struct {
    u32 id;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    MessageLanguageInfo info[10];
} MessageEntry; // size = 0x60

typedef struct {
    char magic[4]; //"QM\0\0"
    u32 unk_04;
    u32 numEntries;
    u32 unk_0C;
} MessageFileHeader;

typedef enum TextControlCode {
    /* 0x00 */ TEXT_CTRL_MESSAGE_END,
    /* 0x01 */ TEXT_CTRL_WAIT_FOR_INPUT,
    /* 0x02 */ TEXT_CTRL_HORIZONTAL_SPACE,
    /* 0x03 */ TEXT_CTRL_GO_TO,
    /* 0x04 */ TEXT_CTRL_INSTANT_TEXT_ON,
    /* 0x05 */ TEXT_CTRL_INSTANT_TEXT_OFF,
    /* 0x06 */ TEXT_CTRL_SHOP_MESSAGE_BOX,
    /* 0x07 */ TEXT_CTRL_EVENT_TRIGGER,
    /* 0x08 */ TEXT_CTRL_DELAY_FRAMES,
    /* 0x09 */ TEXT_CTRL_0x9,
    /* 0x0A */ TEXT_CTRL_CLOSE_AFTER,
    /* 0x0B */ TEXT_CTRL_PLAYER_NAME,
    /* 0x0C */ TEXT_CTRL_PLAY_OCARINA,
    /* 0x0D */ TEXT_CTRL_0xD,
    /* 0x0E */ TEXT_CTRL_PLAY_SFX,
    /* 0x0F */ TEXT_CTRL_ITEM_OBTAINED,
    /* 0x10 */ TEXT_CTRL_SET_SPEED,
    /* 0x11 */ TEXT_CTRL_WRONG_SONG,
    /* 0x12 */ TEXT_CTRL_MARATHON_TIME,
    /* 0x13 */ TEXT_CTRL_HORSE_RACE_TIME,
    /* 0x14 */ TEXT_CTRL_GERUDO_ARCHERY_POINTS,
    /* 0x15 */ TEXT_CTRL_SKULLTULAS_DESTROYED,
    /* 0x16 */ TEXT_CTRL_FISH_INFO,
    /* 0x17 */ TEXT_CTRL_CURRENT_TIME,
    /* 0x18 */ TEXT_CTRL_HIGH_SCORES,
    /* 0x19 */ TEXT_CTRL_UNSKIPPABLE,
    /* 0x1A */ TEXT_CTRL_TWO_WAY_CHOICE,
    /* 0x1B */ TEXT_CTRL_THREE_WAY_CHOICE,
    /* 0x1C */ TEXT_CTRL_NEWLINE,
    /* 0x1D */ TEXT_CTRL_COLOR,
    /* 0x1E */ TEXT_CTRL_CENTER_TEXT,
    /* 0x1F */ TEXT_CTRL_0x1F,
    /* 0x20 */ TEXT_CTRL_0x20,
    /* 0x21 */ TEXT_CTRL_0x21,
    /* 0x22 */ TEXT_CTRL_0x22,
    /* 0x23 */ TEXT_CTRL_BOSS_CHALLENGE_RECORDS,
    /* 0x24 */ TEXT_CTRL_BUTTON_ICON,
    /* 0x25 */ TEXT_CTRL_CREDITS_UNK,
    /* 0x26 */ TEXT_CTRL_SINGULAR_FORM_START,
    /* 0x27 */ TEXT_CTRL_PLURAL_FORM_START,
    /* 0x28 */ TEXT_CTRL_PLURAL_FORM_END,
    /* 0x29 */ TEXT_CTRL_IF_NOT_MQ,
    /* 0x2A */ TEXT_CTRL_MQ_ELSE,
    /* 0x2B */ TEXT_CTRL_MQ_END,
    /* 0x2C */ TEXT_CTRL_0x2C,
    /* 0x2D */ TEXT_CTRL_0x2D,
    /* 0x2E */ TEXT_CTRL_0x2E,
    /* 0x2F */ TEXT_CTRL_0x2F,

    // The following values are custom control codes added by the randomizer

    /* 0x30 */ TEXT_CTRL_TRIFORCE_PIECE_COUNT,
} TextControlCode;

typedef struct UnkTextControlData {
    /* 0x00 */ char unk_00[0x5];
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk_06[0x2];
    /* 0x08 */ u16* stringToInsert;
    /* 0x0C */ u32 stringLength;
    // ... size unknown
} UnkTextControlData;

typedef void (*Message_UnkControlCodeHandler_proc)(void* textObj, UnkTextControlData** data);
#define Message_UnkControlCodeHandler ((Message_UnkControlCodeHandler_proc)0x306318)

typedef char* (*Message_CheckForControlCodes_proc)(void* data, char* nextChars);
#define Message_CheckForControlCodes ((Message_CheckForControlCodes_proc)0x4C08C0)

typedef void (*Message_SetInstantText_proc)(void* textObj);
#define Message_SetInstantText ((Message_SetInstantText_proc)0x40B608)

#endif //_MESSAGE_H_
