#include "z3D/z3D.h"
#include "message.h"
#include "dungeon_rewards.h"
#include <stddef.h>

// These consts are filled in by the app
volatile const u32 numCustomMessageEntries;
volatile const MessageEntry* ptrCustomMessageEntries;

typedef const MessageEntry* (*Message_GetEntry_proc)(void* param_1, u32 textId);
#define Message_GetEntry_addr 0x2DF4C4
#define Message_GetEntry ((Message_GetEntry_proc)Message_GetEntry_addr)

typedef const char* (*Message_GetText_proc)(void* param_1, u32 offset);
#define Message_GetText_addr 0x2DF4B0
#define Message_GetText ((Message_GetText_proc)Message_GetText_addr)

const MessageEntry* Message_GetCustomEntry(void* param_1, u32 textId_) {
    s32 start;
    s32 end;

    u32 textId = DungeonReward_GetOverrideText(textId_);
    start = 0;
    end = numCustomMessageEntries - 1;
    while ((end >= 0) && (start <= end)) {
        s32 cur = (start + end) / 2;
        s32 id = ptrCustomMessageEntries[cur].id;
        if (textId < id) {
            end = cur - 1;
        } else if (textId > id) {
            start = cur + 1;
        } else {
            return &ptrCustomMessageEntries[cur];
        }
    }
    return Message_GetEntry(param_1, textId);
}

// compares offset to 0x500000 to detect custom
const char* Message_GetCustomText(void* param_1, u32 offset) {
    return (offset > 0x500000) ? (char*)offset : Message_GetText(param_1, offset);
}
