#include "z3D/z3D.h"
#include "owl.h"
#include "item00.h"
#include "heart_container.h"
#include "token.h"
#include "item_etcetera.h"
#include "en_ex_item.h"
#include "demo_effect.h"
#include "business_scrubs.h"
#include "ocarina.h"
#include "cow.h"
#include "string.h"
#include "ganondorf_organ.h"
#include "checkable_spot.h"
#include "twinrova.h"

#define OBJECT_CUSTOM_DOUBLE_DEFENSE 4
#define OBJECT_CUSTOM_ZELDAS_LULLABY 5
#define OBJECT_CUSTOM_SARIAS_SONG 16
#define OBJECT_CUSTOM_SUNS_SONG 17
#define OBJECT_CUSTOM_EPONAS_SONG 58
#define OBJECT_CUSTOM_SONG_OF_STORMS 120
#define OBJECT_CUSTOM_SONG_OF_TIME 121
#define OBJECT_CUSTOM_MINUET_OF_FOREST 122
#define OBJECT_CUSTOM_BOLERO_OF_FIRE 123
#define OBJECT_CUSTOM_SERENADE_OF_WATER 125
#define OBJECT_CUSTOM_REQUIEM_OF_SPIRIT 126
#define OBJECT_CUSTOM_NOCTURNE_OF_SHADOW 127
#define OBJECT_CUSTOM_PRELUDE_OF_LIGHT 128

#define OBJECT_GI_HEARTS 189
#define OBJECT_GI_OCARINA 222
#define OBJECT_GI_OCARINA_0 270

void Actor_Init() {
    gActorOverlayTable[0x14D].initInfo->init = EnOwl_DespawnInit; //Despawns unneccesary owls

    gActorOverlayTable[0x15].initInfo->init = EnItem00_rInit;
    gActorOverlayTable[0x15].initInfo->destroy = EnItem00_rDestroy;
    gActorOverlayTable[0x15].initInfo->draw = EnItem00_rDraw;

    gActorOverlayTable[0x5F].initInfo->init = ItemBHeart_rInit;
    gActorOverlayTable[0x5F].initInfo->destroy = ItemBHeart_rDestroy;
    gActorOverlayTable[0x5F].initInfo->draw = ItemBHeart_rDraw;

    gActorOverlayTable[0x8B].initInfo->init = DemoEffect_rInit;
    gActorOverlayTable[0x8B].initInfo->destroy = DemoEffect_rDestroy;
    
    gActorOverlayTable[0xDC].initInfo->update = Boss_Tw_rUpdate;
    gActorOverlayTable[0xDC].initInfo->draw = Boss_Tw_rDraw;

    gActorOverlayTable[0xF1].initInfo->init = ItemOcarina_rInit;
    gActorOverlayTable[0xF1].initInfo->destroy = ItemOcarina_rDestroy;
    gActorOverlayTable[0xF1].initInfo->draw = ItemOcarina_rDraw;

    gActorOverlayTable[0x10F].initInfo->init = ItemEtcetera_rInit;
    gActorOverlayTable[0x10F].initInfo->destroy = ItemEtcetera_rDestroy;

    gActorOverlayTable[0x11B].initInfo->update = NULL;

    gActorOverlayTable[0x15E].initInfo->init = EnGanonOrgan_rInit;

    gActorOverlayTable[0x168].initInfo->init = EnExItem_rInit;
    gActorOverlayTable[0x168].initInfo->destroy = EnExItem_rDestroy;

    gActorOverlayTable[0x185].initInfo->update = EnWonderTalk2_rUpdate;

    gActorOverlayTable[0x195].initInfo->init = EnShopnuts_rInit;

    gActorOverlayTable[0x19C].initInfo->init = EnSi_rInit;
    gActorOverlayTable[0x19C].initInfo->destroy = EnSi_rDestroy;
    gActorOverlayTable[0x19C].initInfo->draw = EnSi_rDraw;

    gActorOverlayTable[0x1C6].initInfo->init = EnCow_rInit;
    gActorOverlayTable[0x1C6].initInfo->destroy = EnCow_rDestroy;

    // Define object 4 to be by default the same as object 189
    strncpy(gObjectTable[OBJECT_CUSTOM_DOUBLE_DEFENSE].filename, gObjectTable[OBJECT_GI_HEARTS].filename, 0x40);

    // Define object 5 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_ZELDAS_LULLABY].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 16 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_SARIAS_SONG].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 17 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_SUNS_SONG].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 58 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_EPONAS_SONG].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 120 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_SONG_OF_STORMS].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 121 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_SONG_OF_TIME].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 122 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_MINUET_OF_FOREST].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define object 123 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_BOLERO_OF_FIRE].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define object 125 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_SERENADE_OF_WATER].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define object 126 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_REQUIEM_OF_SPIRIT].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define object 127 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_NOCTURNE_OF_SHADOW].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define object 128 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_PRELUDE_OF_LIGHT].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define draw item 3 (corresponding to gi 4) to be double defense custom model
    gDrawItemTable[3].objectId = OBJECT_CUSTOM_DOUBLE_DEFENSE;
    gDrawItemTable[3].objectModelIdx = 0;

    // Define draw item 4 (corresponding to gi 5) to be a child song custom model
    gDrawItemTable[4].objectId = OBJECT_CUSTOM_ZELDAS_LULLABY;
    gDrawItemTable[4].objectModelIdx = 2;

    // Define draw item 5 (corresponding to gi 6) to be an adult song custom model
    gDrawItemTable[5].objectId = OBJECT_CUSTOM_MINUET_OF_FOREST;
    gDrawItemTable[5].objectModelIdx = 0;
}
