#ifndef _Z3DEQUIPMENT_H_
#define _Z3DEQUIPMENT_H_

enum {
    NO_BULLET_BAG = 0,
    BULLET_BAG_30 = 1,
    BULLET_BAG_40 = 2,
    BULLET_BAG_50 = 3,
} BulletBag;

enum {
    NO_QUIVER = 0,
    QUIVER_30 = 1,
    QUIVER_40 = 2,
    QUIVER_50 = 3,
} Quiver;

enum {
    NO_BOMB_BAG = 0,
    BOMB_BAG_20 = 1,
    BOMB_BAG_30 = 2,
    BOMB_BAG_40 = 3,
} BombBag;

enum {
    NO_STRENGTH      = 0,
    GORON_BRACELET   = 1,
    SILVER_GAUNTLETS = 2,
    GOLDEN_GAUNTLETS = 3,
} Strength;

enum {
    NO_DIVE_UPGRADE = 0,
    SILVER_SCALE    = 1,
    GOLDEN_SCALE    = 2,
} DiveMeter;

enum {
    DEFAULT_WALLET  = 0,
    ADULTS_WALLET   = 1,
    GIANTS_WALLET   = 2,
    NO_RUPEES_SHOWN = 3,
} Wallet;

#endif
