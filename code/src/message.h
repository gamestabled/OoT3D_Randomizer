#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "z3D/z3D.h"

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
    u32  unk_04;
    u32  numEntries;
    u32  unk_0C;
} MessageFileHeader;

#endif //_MESSAGE_H_
