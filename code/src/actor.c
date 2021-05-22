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
#include "nabooru.h"
#include "custom_models.h"
#include "obj_switch.h"
#include "gerudo_archery_manager.h"
#include "chest.h"
#include "gossip_stone.h"
#include "drawbridge.h"
#include "king_zora.h"
#include "collapsing_castle.h"
#include "demo_kankyo.h"
#include "lake_hylia_objects.h"

#define OBJECT_GI_HEARTS 189
#define OBJECT_GI_OCARINA 222
#define OBJECT_GI_OCARINA_0 270

void Actor_Init() {
    gActorOverlayTable[0xA].initInfo->init = EnBox_rInit;

    gActorOverlayTable[0x15].initInfo->init = EnItem00_rInit;
    gActorOverlayTable[0x15].initInfo->destroy = EnItem00_rDestroy;
    gActorOverlayTable[0x15].initInfo->draw = EnItem00_rDraw;

    gActorOverlayTable[0x4A].initInfo->update = BgSpot00Hanebasi_rUpdate;

    gActorOverlayTable[0x5F].initInfo->init = ItemBHeart_rInit;
    gActorOverlayTable[0x5F].initInfo->destroy = ItemBHeart_rDestroy;
    gActorOverlayTable[0x5F].initInfo->draw = ItemBHeart_rDraw;

    gActorOverlayTable[0x8B].initInfo->init = DemoEffect_rInit;
    gActorOverlayTable[0x8B].initInfo->destroy = DemoEffect_rDestroy;

    gActorOverlayTable[0x8C].initInfo->update = DemoKankyo_rUpdate;

    gActorOverlayTable[0xC3].initInfo->draw = EnNb_rDraw;

    gActorOverlayTable[0xD5].initInfo->update = BgSpot06Objects_rUpdate;
    gActorOverlayTable[0xD5].initInfo->destroy = BgSpot06Objects_rDestroy;

    gActorOverlayTable[0xDC].initInfo->init = Boss_Tw_rInit;
    gActorOverlayTable[0xDC].initInfo->update = Boss_Tw_rUpdate;
    gActorOverlayTable[0xDC].initInfo->draw = Boss_Tw_rDraw;
    gActorOverlayTable[0xDC].initInfo->destroy = Boss_Tw_rDestroy;

    gActorOverlayTable[0xF1].initInfo->init = ItemOcarina_rInit;
    gActorOverlayTable[0xF1].initInfo->destroy = ItemOcarina_rDestroy;
    gActorOverlayTable[0xF1].initInfo->draw = ItemOcarina_rDraw;

    gActorOverlayTable[0x10F].initInfo->init = ItemEtcetera_rInit;
    gActorOverlayTable[0x10F].initInfo->destroy = ItemEtcetera_rDestroy;

    gActorOverlayTable[0x11B].initInfo->update = NULL;

    gActorOverlayTable[0x12A].initInfo->init = ObjSwitch_rInit;

    gActorOverlayTable[0x138].initInfo->update = EnGe1_rUpdate;

    gActorOverlayTable[0x14D].initInfo->init = EnOwl_DespawnInit; //Despawns unnecessary owls
    gActorOverlayTable[0x14D].initInfo->update = EnOwl_rUpdate;

    gActorOverlayTable[0x15E].initInfo->init = EnGanonOrgan_rInit;

    gActorOverlayTable[0x164].initInfo->update = EnKz_rUpdate;

    gActorOverlayTable[0x168].initInfo->init = EnExItem_rInit;
    gActorOverlayTable[0x168].initInfo->destroy = EnExItem_rDestroy;

    gActorOverlayTable[0x174].initInfo->update = DemoGt_rUpdate;

    gActorOverlayTable[0x185].initInfo->update = EnWonderTalk2_rUpdate;

    gActorOverlayTable[0x195].initInfo->init = EnShopnuts_rInit;

    gActorOverlayTable[0x19C].initInfo->init = EnSi_rInit;
    gActorOverlayTable[0x19C].initInfo->destroy = EnSi_rDestroy;
    gActorOverlayTable[0x19C].initInfo->draw = EnSi_rDraw;

    gActorOverlayTable[0x1B9].initInfo->init = EnGs_rInit;

    gActorOverlayTable[0x1C6].initInfo->init = EnCow_rInit;
    gActorOverlayTable[0x1C6].initInfo->destroy = EnCow_rDestroy;

    // Define object 4 to be by default the same as object 189
    strncpy(gObjectTable[OBJECT_CUSTOM_DOUBLE_DEFENSE].filename, gObjectTable[OBJECT_GI_HEARTS].filename, 0x40);

    // Define object 5 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_CHILD_SONGS].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 16 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_ADULT_SONGS].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define draw item 3 (corresponding to gid 4) to be double defense custom model
    gDrawItemTable[3].objectId = OBJECT_CUSTOM_DOUBLE_DEFENSE;
    gDrawItemTable[3].objectModelIdx = 0;

    // Define draw item 4 (corresponding to gid 5) to be a child song custom model
    gDrawItemTable[4].objectId = OBJECT_CUSTOM_CHILD_SONGS;
    gDrawItemTable[4].objectModelIdx = 2;

    // Define draw item 5 (corresponding to gid 6) to be an adult song custom model
    gDrawItemTable[5].objectId = OBJECT_CUSTOM_ADULT_SONGS;
    gDrawItemTable[5].objectModelIdx = 0;
}
