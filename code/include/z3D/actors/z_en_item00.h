#ifndef _EN_ITEM00_H_
#define _EN_ITEM00_H_

#include "z3D/z3D.h"

typedef enum Item00Type {
    /* 0x00 */ ITEM00_RUPEE_GREEN,
    /* 0x01 */ ITEM00_RUPEE_BLUE,
    /* 0x02 */ ITEM00_RUPEE_RED,
    /* 0x03 */ ITEM00_RECOVERY_HEART,
    /* 0x04 */ ITEM00_BOMBS_A,
    /* 0x05 */ ITEM00_ARROWS_SINGLE,
    /* 0x06 */ ITEM00_HEART_PIECE,
    /* 0x07 */ ITEM00_HEART_CONTAINER,
    /* 0x08 */ ITEM00_ARROWS_SMALL,
    /* 0x09 */ ITEM00_ARROWS_MEDIUM,
    /* 0x0A */ ITEM00_ARROWS_LARGE,
    /* 0x0B */ ITEM00_BOMBS_B,
    /* 0x0C */ ITEM00_NUTS,
    /* 0x0D */ ITEM00_STICK,
    /* 0x0E */ ITEM00_MAGIC_LARGE,
    /* 0x0F */ ITEM00_MAGIC_SMALL,
    /* 0x10 */ ITEM00_SEEDS,
    /* 0x11 */ ITEM00_SMALL_KEY,
    /* 0x12 */ ITEM00_FLEXIBLE,
    /* 0x13 */ ITEM00_RUPEE_ORANGE,
    /* 0x14 */ ITEM00_RUPEE_PURPLE,
    /* 0x15 */ ITEM00_SHIELD_DEKU,
    /* 0x16 */ ITEM00_SHIELD_HYLIAN,
    /* 0x17 */ ITEM00_TUNIC_ZORA,
    /* 0x18 */ ITEM00_TUNIC_GORON,
    /* 0x19 */ ITEM00_BOMBS_SPECIAL,
    /* 0x1A */ ITEM00_MAX,
    /* 0xFF */ ITEM00_NONE = 0xFF
} Item00Type;

typedef struct EnItem00 {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ void* action_fn;
    /* 0x1A8 */ u16 collectibleFlag;
    /* 0x1AA */ char unk_1AA[0x4];
    /* 0x1AE */ u16 unk_1AE;
    /* 0x1B0 */ u16 unk_1B0;
    /* 0x1B2 */ char unk_1B2[0x66];
} EnItem00; // size 0x218

#endif //_EN_ITEM00_H_
