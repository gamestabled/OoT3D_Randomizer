#include "z3D/z3D.h"
#include "message.h"
#include "savefile.h"
#include "settings.h"
#include "3ds/util/utf.h"
#include "lib/printf.h"
#include <stddef.h>
#include <string.h>

// These consts are filled in by the app
volatile const u32 numCustomMessageEntries;
volatile const MessageEntry* ptrCustomMessageEntries;

typedef const MessageEntry* (*Message_GetEntry_proc)(void* param_1, u32 textId);
#define Message_GetEntry_addr 0x2DF4C4
#define Message_GetEntry ((Message_GetEntry_proc)Message_GetEntry_addr)

typedef const char* (*Message_GetText_proc)(void* param_1, u32 offset);
#define Message_GetText_addr 0x2DF4B0
#define Message_GetText ((Message_GetText_proc)Message_GetText_addr)

const MessageEntry* Message_GetCustomEntry(void* param_1, u32 textId) {
    s32 start;
    s32 end;

    start = 0;
    end   = numCustomMessageEntries - 1;
    while ((end >= 0) && (start <= end)) {
        s32 cur = (start + end) / 2;
        s32 id  = ptrCustomMessageEntries[cur].id;
        if (textId < id) {
            end = cur - 1;
        } else if (textId > id) {
            start = cur + 1;
        } else {
            return (MessageEntry*)&ptrCustomMessageEntries[cur];
        }
    }
    return Message_GetEntry(param_1, textId);
}

// compares offset to 0x500000 to detect custom
const char* Message_GetCustomText(void* param_1, u32 offset) {
    return (offset > 0x500000) ? (char*)offset : Message_GetText(param_1, offset);
}

#define MESSAGE_MAX_CUSTOM_STRING_SIZE 10
u32 Message_HandleTextControlCode(TextControlCode ctrl, void* textObj, UnkTextControlData* data) {
    static u16 utf16Str[MESSAGE_MAX_CUSTOM_STRING_SIZE] = { 0 };
    char str[MESSAGE_MAX_CUSTOM_STRING_SIZE];

    // Make text skippable or instant depending on setting.
    if ((ctrl == TEXT_CTRL_UNSKIPPABLE && gSettingsContext.quickText >= QUICKTEXT_SKIPPABLE) ||
        (ctrl == TEXT_CTRL_INSTANT_TEXT_OFF && gSettingsContext.quickText >= QUICKTEXT_INSTANT)) {
        return 1; // Bypass control code
    }

    // When a custom control code is found, copy what FUN_0040b7d8 does to insert the player name,
    // but instead insert a custom string.
    if (ctrl == TEXT_CTRL_TRIFORCE_PIECE_COUNT) {
        snprintf_(str, MESSAGE_MAX_CUSTOM_STRING_SIZE, "%d", gExtSaveData.triforcePieces);
        utf8_to_utf16(utf16Str, (u8*)str, strlen(str));
        Message_UnkControlCodeHandler(textObj, &data);
        data->unk_05         = 0;
        data->stringToInsert = utf16Str;
        data->stringLength   = strlen(str);
        return 1;
    }

    return 0; // Vanilla control char, resume base game function.
}

char* Message_rCheckForControlCodes(void* unkStruct, char* nextChars, void* textObj, u32 charIdx) {
    // Set instant text when parsing the first character of the text or immediately after a box break.
    if (gSettingsContext.quickText >= QUICKTEXT_INSTANT &&
        (charIdx == 0 || (charIdx >= 2 && nextChars[-2] == '\x7F' && nextChars[-1] == TEXT_CTRL_WAIT_FOR_INPUT))) {
        Message_SetInstantText(textObj);
    }

    // If the next characters are either not a control code or a vanilla one,
    // use base game function.
    if (nextChars[0] != '\x7F' || nextChars[1] <= TEXT_CTRL_0x2F) {
        return Message_CheckForControlCodes(unkStruct, nextChars);
    }

    // Store control code identifier
    *(char*)(unkStruct + 4) = nextChars[1];
    // Return pointer to next char after this control code,
    // assuming all custom control codes will be 2 characters long.
    return nextChars + 2;
}
