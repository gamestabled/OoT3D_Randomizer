#ifndef _RED_ICE_H_
#define _RED_ICE_H_

#include "z3D/z3D.h"

struct BgIceShelter;

typedef void (*BgIceShelterActionFunc)(struct BgIceShelter*, GlobalContext*);

typedef enum {
    /* 0 */ RED_ICE_LARGE,    // Large red ice block
    /* 1 */ RED_ICE_SMALL,    // Small red ice block
    /* 2 */ RED_ICE_PLATFORM, // Complex structure that can be climbed and walked on. Unused in vanilla OoT, used in MQ
                              // to cover the Ice Cavern Map chest
    /* 3 */ RED_ICE_WALL,     // Vertical ice sheets blocking corridors
    /* 4 */ RED_ICE_KING_ZORA // Giant red ice block covering King Zora
} RedIceType;

typedef struct BgIceShelter {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x01BC */ BgIceShelterActionFunc actionFunc;
    /* 0x01C0 */ ColliderCylinder cylinder1; // Used to detect blue fire and also as OC for no-dynapoly types
    /* 0x0218 */ ColliderCylinder cylinder2; // Only used by no-dynapoly types to make weapons bounce off
    /* 0x0270 */ s16 alpha;
} BgIceShelter; // size = 0x0204

void RedIce_CheckIceArrow(Collider* at, Collider* ac);

#endif
