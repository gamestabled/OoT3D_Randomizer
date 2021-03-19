#include "settings.h"

SettingsContext gSettingsContext = {0};

s32 Settings_ApplyDamageMultiplier(GlobalContext* globalCtx, s32 changeHealth) {
    s32 modifiedChangeHealth = changeHealth;

    //disregard master quest damage
    if (gSaveContext.masterQuestFlag) {
      modifiedChangeHealth /= 2;
    }

    if (changeHealth < 0) {
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
            case DAMAGEMULTIPLIER_OHKO:
                modifiedChangeHealth = -1000;
                break;
        }
    }

    return modifiedChangeHealth;
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
