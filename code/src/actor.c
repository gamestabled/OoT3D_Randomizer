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
#include "gerudos.h"
#include "shops.h"
#include "chest.h"
#include "gossip_stone.h"
#include "drawbridge.h"
#include "king_zora.h"
#include "collapsing_castle.h"
#include "demo_kankyo.h"
#include "lake_hylia_objects.h"
#include "graveyard_objects.h"
#include "windmill_man.h"
#include "deku_tree_mouth.h"
#include "well_stone.h"
#include "well_water.h"
#include "liftable_rock.h"
#include "player.h"
#include "rupee_trap.h"
#include "item_override.h"
#include "songs_visual_effects.h"
#include "shooting_gallery_man.h"
#include "gtg_gate.h"
#include "chest_minigame.h"
#include "door.h"
#include "malon.h"
#include "jabu.h"
#include "dampe.h"
#include "hookshot.h"
#include "web.h"
#include "boulder_red.h"
#include "skulltula.h"
#include "collapsing_platform.h"
#include "carpenter.h"
#include "pushblock.h"
#include "spin_attack.h"
#include "deku_scrubs.h"
#include "bean_plant.h"

#define OBJECT_GI_KEY 170
#define OBJECT_GI_BOSSKEY 185
#define OBJECT_GI_HEARTS 189
#define OBJECT_GI_OCARINA 222
#define OBJECT_GI_OCARINA_0 270

typedef void (*TitleCard_Update_proc)(GlobalContext* globalCtx, TitleCardContext* titleCtx);
#ifdef Version_EUR
    #define TitleCard_Update_addr 0x47955C
#else
    #define TitleCard_Update_addr 0x47953C
#endif
#define TitleCard_Update ((TitleCard_Update_proc)TitleCard_Update_addr)

void Actor_Init() {
    gActorOverlayTable[0x0].initInfo->init    = PlayerActor_rInit;
    gActorOverlayTable[0x0].initInfo->update  = PlayerActor_rUpdate;
    gActorOverlayTable[0x0].initInfo->destroy = PlayerActor_rDestroy;
    gActorOverlayTable[0x0].initInfo->draw    = PlayerActor_rDraw;

    gActorOverlayTable[0x4].initInfo->init         = ShopsanityItem_Init;
    gActorOverlayTable[0x4].initInfo->instanceSize = sizeof(ShopsanityItem);

    gActorOverlayTable[0x9].initInfo->update = (ActorFunc)EnDoor_rUpdate;

    gActorOverlayTable[0xA].initInfo->init   = EnBox_rInit;
    gActorOverlayTable[0xA].initInfo->update = EnBox_rUpdate;

    gActorOverlayTable[0xF].initInfo->update = (ActorFunc)BgYdanSp_rUpdate;

    gActorOverlayTable[0x15].initInfo->init    = EnItem00_rInit;
    gActorOverlayTable[0x15].initInfo->destroy = EnItem00_rDestroy;
    gActorOverlayTable[0x15].initInfo->update  = EnItem00_rUpdate;
    gActorOverlayTable[0x15].initInfo->draw    = EnItem00_rDraw;

    gActorOverlayTable[0x2E].initInfo->init   = DoorShutter_rInit;
    gActorOverlayTable[0x2E].initInfo->update = (ActorFunc)DoorShutter_rUpdate;

    gActorOverlayTable[0x3D].initInfo->destroy = EnOssan_rDestroy;

    gActorOverlayTable[0x3E].initInfo->init = BgTreemouth_rInit;

    gActorOverlayTable[0x4A].initInfo->update = BgSpot00Hanebasi_rUpdate;

    gActorOverlayTable[0x57].initInfo->init = EnMThunder_rInit;

    gActorOverlayTable[0x5F].initInfo->init    = ItemBHeart_rInit;
    gActorOverlayTable[0x5F].initInfo->destroy = ItemBHeart_rDestroy;
    gActorOverlayTable[0x5F].initInfo->update  = ItemBHeart_rUpdate;
    gActorOverlayTable[0x5F].initInfo->draw    = ItemBHeart_rDraw;

    gActorOverlayTable[0x66].initInfo->init = ArmsHook_rInit;

    gActorOverlayTable[0x85].initInfo->update = EnTk_rUpdate;

    gActorOverlayTable[0x8B].initInfo->init    = DemoEffect_rInit;
    gActorOverlayTable[0x8B].initInfo->destroy = DemoEffect_rDestroy;
    gActorOverlayTable[0x8B].initInfo->update  = DemoEffect_rUpdate;

    gActorOverlayTable[0x8C].initInfo->update = DemoKankyo_rUpdate;

    gActorOverlayTable[0x95].initInfo->update = EnSw_rUpdate;

    gActorOverlayTable[0x9C].initInfo->update = BgSpot02Objects_rUpdate;

    gActorOverlayTable[0xC1].initInfo->init   = EnSyatekiMan_rInit;
    gActorOverlayTable[0xC1].initInfo->update = EnSyatekiMan_rUpdate;

    gActorOverlayTable[0xC3].initInfo->draw = EnNb_rDraw;

    gActorOverlayTable[0xD5].initInfo->update  = BgSpot06Objects_rUpdate;
    gActorOverlayTable[0xD5].initInfo->destroy = BgSpot06Objects_rDestroy;

    gActorOverlayTable[0xDC].initInfo->init    = Boss_Tw_rInit;
    gActorOverlayTable[0xDC].initInfo->update  = Boss_Tw_rUpdate;
    gActorOverlayTable[0xDC].initInfo->draw    = Boss_Tw_rDraw;
    gActorOverlayTable[0xDC].initInfo->destroy = Boss_Tw_rDestroy;

    gActorOverlayTable[0xE6].initInfo->init = BgBdanSwitch_rInit;

    gActorOverlayTable[0xE7].initInfo->init = EnMa1_rInit;

    gActorOverlayTable[0xF1].initInfo->init    = ItemOcarina_rInit;
    gActorOverlayTable[0xF1].initInfo->destroy = ItemOcarina_rDestroy;
    gActorOverlayTable[0xF1].initInfo->draw    = ItemOcarina_rDraw;

    gActorOverlayTable[0xFF].initInfo->update = ObjOshihiki_rUpdate;

    gActorOverlayTable[0x104].initInfo->init = BgSpot01Idomizu_rInit;

    gActorOverlayTable[0x107].initInfo->update = BgSpot15Rrbox_rUpdate;

    gActorOverlayTable[0x10F].initInfo->init    = ItemEtcetera_rInit;
    gActorOverlayTable[0x10F].initInfo->destroy = ItemEtcetera_rDestroy;
    gActorOverlayTable[0x10F].initInfo->update  = ItemEtcetera_rUpdate;

    gActorOverlayTable[0x11A].initInfo->update = EnDns_rUpdate;

    gActorOverlayTable[0x11B].initInfo->update = NULL;

    gActorOverlayTable[0x126].initInfo->init   = (ActorFunc)ObjBean_rInit;
    gActorOverlayTable[0x126].initInfo->update = (ActorFunc)ObjBean_rUpdate;

    gActorOverlayTable[0x12A].initInfo->init = ObjSwitch_rInit;

    gActorOverlayTable[0x12C].initInfo->update = (ActorFunc)ObjLift_rUpdate;

    gActorOverlayTable[0x131].initInfo->update = EnExRuppy_rUpdate;

    gActorOverlayTable[0x133].initInfo->update = (ActorFunc)EnDaiku_rUpdate;

    gActorOverlayTable[0x138].initInfo->init   = EnGe1_rInit;
    gActorOverlayTable[0x138].initInfo->update = EnGe1_rUpdate;

    gActorOverlayTable[0x145].initInfo->init = BgSpot01Idosoko_rInit;

    gActorOverlayTable[0x147].initInfo->update = EnWonderTalk_rUpdate;

    gActorOverlayTable[0x14D].initInfo->init   = EnOwl_DespawnInit; // Despawns unnecessary owls
    gActorOverlayTable[0x14D].initInfo->update = EnOwl_rUpdate;

    gActorOverlayTable[0x14E].initInfo->init   = EnIshi_rInit;
    gActorOverlayTable[0x14E].initInfo->update = (ActorFunc)EnIshi_rUpdate;

    gActorOverlayTable[0x153].initInfo->update = EnFu_rUpdate;

    gActorOverlayTable[0x155].initInfo->init = EnChanger_rInit;

    gActorOverlayTable[0x15E].initInfo->init = EnGanonOrgan_rInit;

    gActorOverlayTable[0x164].initInfo->update = EnKz_rUpdate;

    gActorOverlayTable[0x168].initInfo->init    = EnExItem_rInit;
    gActorOverlayTable[0x168].initInfo->destroy = EnExItem_rDestroy;

    gActorOverlayTable[0x172].initInfo->update = (ActorFunc)DoorGerudo_rUpdate;

    gActorOverlayTable[0x174].initInfo->update = DemoGt_rUpdate;

    gActorOverlayTable[0x17C].initInfo->init = EnTakaraMan_rInit;

    gActorOverlayTable[0x17E].initInfo->update = OceffSpot_rUpdate;

    gActorOverlayTable[0x185].initInfo->update = EnWonderTalk2_rUpdate;

    gActorOverlayTable[0x18A].initInfo->update = OceffWipe_rUpdate;
    gActorOverlayTable[0x18B].initInfo->update = OceffStorm_rUpdate;

    gActorOverlayTable[0x191].initInfo->init   = BgSpot12Saku_rInit;
    gActorOverlayTable[0x191].initInfo->update = BgSpot12Saku_rUpdate;

    gActorOverlayTable[0x195].initInfo->init = EnShopnuts_rInit;

    gActorOverlayTable[0x198].initInfo->update = OceffWipe2_rUpdate;
    gActorOverlayTable[0x199].initInfo->update = OceffWipe3_rUpdate;

    gActorOverlayTable[0x19C].initInfo->init    = EnSi_rInit;
    gActorOverlayTable[0x19C].initInfo->destroy = EnSi_rDestroy;
    gActorOverlayTable[0x19C].initInfo->update  = EnSi_rUpdate;
    gActorOverlayTable[0x19C].initInfo->draw    = EnSi_rDraw;

    gActorOverlayTable[0x1A3].initInfo->update = EnDntNomal_rUpdate;

    gActorOverlayTable[0x1B9].initInfo->init = EnGs_rInit;

    gActorOverlayTable[0x1CB].initInfo->update = OceffWipe4_rUpdate;

    gActorOverlayTable[0x1C6].initInfo->init    = EnCow_rInit;
    gActorOverlayTable[0x1C6].initInfo->destroy = EnCow_rDestroy;

    gActorOverlayTable[0x1D2].initInfo->update = (ActorFunc)ObjHamishi_rUpdate;

    gActorOverlayTable[0x1D9].initInfo->update = EnHintstone_rUpdate;

    // Define object 4 to be by default the same as object 189
    strncpy(gObjectTable[OBJECT_CUSTOM_DOUBLE_DEFENSE].filename, gObjectTable[OBJECT_GI_HEARTS].filename, 0x40);

    // Define object 5 to be by default the same as object 270
    strncpy(gObjectTable[OBJECT_CUSTOM_CHILD_SONGS].filename, gObjectTable[OBJECT_GI_OCARINA_0].filename, 0x40);

    // Define object 16 to be by default the same as object 222
    strncpy(gObjectTable[OBJECT_CUSTOM_ADULT_SONGS].filename, gObjectTable[OBJECT_GI_OCARINA].filename, 0x40);

    // Define all the small key objects to be by default the same as object 170
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_FOREST].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_FIRE].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_WATER].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_SHADOW].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_BOTW].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_SPIRIT].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_FORTRESS].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_GTG].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);
    strncpy(gObjectTable[OBJECT_CUSTOM_SMALL_KEY_GANON].filename, gObjectTable[OBJECT_GI_KEY].filename, 0x40);

    // Define object 128 to be by default the same as object
    strncpy(gObjectTable[OBJECT_CUSTOM_BOSS_KEYS].filename, gObjectTable[OBJECT_GI_BOSSKEY].filename, 0x40);

    // Define draw item 3 (corresponding to gid 4) to be double defense custom model
    gDrawItemTable[3].objectId       = OBJECT_CUSTOM_DOUBLE_DEFENSE;
    gDrawItemTable[3].objectModelIdx = 0;

    // Define draw item 4 (corresponding to gid 5) to be a child song custom model
    gDrawItemTable[4].objectId       = OBJECT_CUSTOM_CHILD_SONGS;
    gDrawItemTable[4].objectModelIdx = 2;

    // Define draw item 5 (corresponding to gid 6) to be an adult song custom model
    gDrawItemTable[5].objectId       = OBJECT_CUSTOM_ADULT_SONGS;
    gDrawItemTable[5].objectModelIdx = 0;

    // Define draw item 6 (corresponding to gid 7) to be small key custom model
    gDrawItemTable[6].objectId       = OBJECT_CUSTOM_SMALL_KEY_FOREST;
    gDrawItemTable[6].objectModelIdx = 0;

    // Define draw item 7 (corresponding to gid 8) to be boss key custom model
    gDrawItemTable[7].objectId       = OBJECT_CUSTOM_BOSS_KEYS;
    gDrawItemTable[7].objectModelIdx = 0;
}

void TitleCard_rUpdate(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    if (ItemOverride_IsAPendingOverride()) {
        titleCtx->delayTimer    = 0;
        titleCtx->durationTimer = 0;
        titleCtx->alpha         = 0;
        titleCtx->intensity     = 0;
    }

    TitleCard_Update(globalCtx, titleCtx);
}
