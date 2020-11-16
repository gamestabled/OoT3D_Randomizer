#include "z3D/z3D.h"

typedef struct {
    // In the true file format, offset is the offset into the QM file.
    // In randomizer, offset will be a pointer to the text in the game's address space.
    // Since these pointers will be much larger as u32 than the original script's offsets,
    // We will be able to distinguish between original and custom text using their numerical value.
    const char* offset;
    u32 length;
} MessageLanguageInfo;

typedef struct {
    u32 id;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    MessageLanguageInfo japaneseJ;
    MessageLanguageInfo englishU;
    MessageLanguageInfo englishE;
    MessageLanguageInfo germanE;
    MessageLanguageInfo frenchE;
    MessageLanguageInfo frenchU;
    MessageLanguageInfo spanishE;
    MessageLanguageInfo spanishU;
    MessageLanguageInfo italianE;
    MessageLanguageInfo dutchE;
} MessageEntry; // size = 0x60

typedef struct {
    char magic[4]; //"QM\0\0"
    u32  unk_04;
    u32  numEntries;
    u32  unk_0C;
} MessageFileHeader;
