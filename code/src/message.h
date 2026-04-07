#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "s_message.h"

#include "z3D/z3D.h"

typedef struct UnkTextControlData {
    /* 0x00 */ char unk_00[0x5];
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk_06[0x2];
    /* 0x08 */ u16* stringToInsert;
    /* 0x0C */ u32 stringLength;
    // ... size unknown
} UnkTextControlData;

void Message_UnkControlCodeHandler(void* textObj, UnkTextControlData** data);
char* Message_CheckForControlCodes(void* data, char* nextChars);
void Message_SetInstantText(void* textObj);

#endif //_MESSAGE_H_
