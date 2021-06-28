#include "settings.h"

SettingsContext gSettingsContext = {0};
u8 Damage32 = 0;

s32 Settings_ApplyDamageMultiplier(GlobalContext* globalCtx, s32 changeHealth) {
    // Fairy healing also gets sent to this function and should be ignored
    if (changeHealth >= 0) {
        return changeHealth;
    }
    // If supposed to take damage on OHKO ignore everything else
    if (gSettingsContext.damageMultiplier == DAMAGEMULTIPLIER_OHKO) {
        return -1000;
    }

    s32 modifiedChangeHealth = changeHealth;
    //disregard master quest damage
    if (gSaveContext.masterQuestFlag) {
        modifiedChangeHealth /= 2;
    }

    // MQ damage is applied after this function so changeHealth can be -1
    // In this case modifiedChangeHealth would always be 0 which is wrong
    if (modifiedChangeHealth == 0) {
        modifiedChangeHealth = -(Damage32 >> 2);
        Damage32 ^= 4;
    }

    if (modifiedChangeHealth < 0) {
        switch (gSettingsContext.damageMultiplier) {
            case DAMAGEMULTIPLIER_HALF:
                modifiedChangeHealth /= 2;
                break;
            case DAMAGEMULTIPLIER_DEFAULT:
                break;
            case DAMAGEMULTIPLIER_DOUBLE:
                modifiedChangeHealth *= 2;
                break;
            case DAMAGEMULTIPLIER_QUADRUPLE:
                modifiedChangeHealth *= 4;
                break;
        }

        // Can only be 0 if supposed to be -0.5: alternate -1 and 0
        if (modifiedChangeHealth == 0) {
            modifiedChangeHealth = -(Damage32 & 1);
            Damage32 ^= 1;
        }
    }

    // Double defense seems to round up after halving so values of -1 should instead alternate between -2 and 0 (-1 would also work, but -2 was easier)
    if (gSaveContext.doubleDefense && modifiedChangeHealth == -1) {
        modifiedChangeHealth = -(Damage32 & 2);
        Damage32 ^= 2;
    }

    return modifiedChangeHealth;
}
//With the No Health Refill option on, full health refills from health upgrades and Bombchu Bowling are turned off, and fairies restore 3 hearts
//Otherwise, they grant a full heal, and the default effect applies (full heal from bottle, 8 hearts on contact)
u8 Settings_SetFullHealthRestore(u8 setAmount) {
    if((gSettingsContext.heartDropRefill == HEARTDROPREFILL_NOREFILL) || (gSettingsContext.heartDropRefill == HEARTDROPREFILL_NODROPREFILL)){
        return setAmount;
    } else {
        return 0x140;
    }
}
u8 NoHealFromHealthUpgrades(void) {
    return Settings_SetFullHealthRestore(0);
}
u8 NoHealFromBombchuBowlingPrize(void) {
    return Settings_SetFullHealthRestore(0);
}
u8 FairyReviveHealAmount(void) {
    return Settings_SetFullHealthRestore(0x30);
}
u8 FairyUseHealAmount(void) {
    return Settings_SetFullHealthRestore(0x30);
}
typedef void (*Health_ChangeBy_proc)(u32 arg1, u32 arg2);
#define Health_ChangeBy_addr 0x352dbc
#define Health_ChangeBy ((Health_ChangeBy_proc)Health_ChangeBy_addr)
u8 FairyPickupHealAmount(void) {
    if(gSettingsContext.heartDropRefill == HEARTDROPREFILL_NOREFILL || gSettingsContext.heartDropRefill == HEARTDROPREFILL_NODROPREFILL){
        Health_ChangeBy(gGlobalContext, 0x30);
    } else {
        Health_ChangeBy(gGlobalContext, 0x80);
    }
}

  const char hashIconNames[32][25] = {
    "Deku Stick",
    "Deku Nut",
    "Bow",
    "Slingshot",
    "Fairy Ocarina",
    "Bombchu",
    "Longshot",
    "Boomerang",
    "Lens of Truth",
    "Beans",
    "Megaton Hammer",
    "Bottled Fish",
    "Bottled Milk",
    "Mask of Truth",
    "SOLD OUT",
    "Cucco",
    "Mushroom",
    "Saw",
    "Frog",
    "Master Sword",
    "Mirror Shield",
    "Kokiri Tunic",
    "Hover Boots",
    "Silver Gauntlets",
    "Gold Scale",
    "Shard of Agony",
    "Skull Token",
    "Heart Container",
    "Boss Key",
    "Compass",
    "Map",
    "Big Magic",
  };
