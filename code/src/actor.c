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
}
