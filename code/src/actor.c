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
#include "string.h"

#define OBJECT_CUSTOM_DOUBLE_DEFENSE 4
#define OBJECT_CUSTOM_ZELDAS_LULLABY 5
#define OBJECT_CUSTOM_SARIAS_SONG 16
#define OBJECT_CUSTOM_SUNS_SONG 17
#define OBJECT_CUSTOM_EPONAS_SONG 58
#define OBJECT_CUSTOM_SONG_OF_STORMS 120
#define OBJECT_CUSTOM_SONG_OF_TIME 121

#define OBJECT_GI_HEARTS 189
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

    gActorOverlayTable[0xF1].initInfo->init = ItemOcarina_rInit;
    gActorOverlayTable[0xF1].initInfo->destroy = ItemOcarina_rDestroy;
    gActorOverlayTable[0xF1].initInfo->draw = ItemOcarina_rDraw;

    gActorOverlayTable[0x10F].initInfo->init = ItemEtcetera_rInit;
    gActorOverlayTable[0x10F].initInfo->destroy = ItemEtcetera_rDestroy;

    gActorOverlayTable[0x168].initInfo->init = EnExItem_rInit;
    gActorOverlayTable[0x168].initInfo->destroy = EnExItem_rDestroy;

    gActorOverlayTable[0x195].initInfo->init = EnShopnuts_rInit;

    gActorOverlayTable[0x19C].initInfo->init = EnSi_rInit;
    gActorOverlayTable[0x19C].initInfo->destroy = EnSi_rDestroy;
    gActorOverlayTable[0x19C].initInfo->draw = EnSi_rDraw;

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

    // Define draw item 3 (corresponding to gi 4) to be double defense custom model
    gDrawItemTable[3].objectId = OBJECT_CUSTOM_DOUBLE_DEFENSE;
    gDrawItemTable[3].objectModelIdx = 0;

    // Define draw item 4 (corresponding to gi 5) to be a child song custom model
    gDrawItemTable[4].objectId = OBJECT_CUSTOM_ZELDAS_LULLABY;
    gDrawItemTable[4].objectModelIdx = 2;
}
