#include "chest.h"
#include "z3D/z3D.h"
#include "item_override.h"
#include "item_table.h"
#include "settings.h"

#define EnBox_Init_addr 0x1899EC
#define EnBox_Init ((ActorFunc)EnBox_Init_addr)

#define EnBox_Update_addr 0x1D5B70
#define EnBox_Update ((ActorFunc)EnBox_Update_addr)

//This variable is updated in rInit and used in Chest_OverrideDecoration,
//which runs inside a patch for the Init function. So it's only ever used
//by one chest at a time.
static u8 type = 0;

static u8 checkedForBombchus = 0;
Actor* lastTrapChest = 0;
Actor* bomb = 0;

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx){
    lastTrapChest = 0;
                                                                 // treasure box shop chests
    u8 vanilla = (gSettingsContext.chestSize == VANILLA_SIZE) || (globalCtx->sceneNum == 16 && thisx->room != 6);

    if(!checkedForBombchus && gSettingsContext.bombchusInLogic && gSaveContext.items[8] == 0xFF){
        ItemTable_SetBombchusChestType(0);
        checkedForBombchus = 1;
    }
    if(checkedForBombchus && gSaveContext.items[8] != 0xFF){
        ItemTable_SetBombchusChestType(1);
        checkedForBombchus = 0;
    }

    ItemOverride thisOverride = ItemOverride_Lookup(thisx, globalCtx->sceneNum, 0);
    ItemRow* thisItemRow;
    if(vanilla || thisOverride.key.all == 0){
        thisItemRow = ItemTable_GetItemRowFromIndex((thisx->params & 0x0FE0) >> 5); //get type from vanilla item table
    }
    else{
        thisItemRow = ItemTable_GetItemRow(ItemTable_ResolveUpgrades(thisOverride.value.itemId));
    }
    type = thisItemRow->chestType;

    EnBox_Init(thisx, globalCtx);

    if(vanilla){
        type = 0;
        return;
    }

    if(type == WOODEN_BIG || type == DECORATED_BIG){
        //Make chest BIG
        thisx->scale.x = 0.01f;
        thisx->scale.y = 0.01f;
        thisx->scale.z = 0.01f;
        //Move Ganon's Castle Zelda's Lullaby Chest back so it is reachable
        if((thisx->params & 0xF000) == 0x8000 && globalCtx->sceneNum==13 && thisx->room==9){
            thisx->world.pos.z = -962.0f;
        }
        //Move MQ Deku Tree SoT chest so it is reachable
        if(thisx->params==0x5AA0 && globalCtx->sceneNum==0 && thisx->room==5){
            thisx->world.pos.x = -1380.0f;
        }
    }
    else{
        //Make chest small
        thisx->scale.x = 0.005f;
        thisx->scale.y = 0.005f;
        thisx->scale.z = 0.005f;
        //Move Ganon's Castle Gold Gauntlets chest so it is reachable with hookshot from the switch platform
        if(thisx->params==0x36C5 && globalCtx->sceneNum==13 && thisx->room==12){
            thisx->world.pos.x =  1777.0f;
            thisx->world.pos.z = -3626.0f;
        }
        //Move Spirit Temple Compass Chest so it is reachable with hookshot
        else if(thisx->params==0x3804 && globalCtx->sceneNum==6 && thisx->room==14){
            thisx->world.pos.x = 400.0f;
        }
    }
    type = 0;
}

void EnBox_rUpdate(Actor* thisx, GlobalContext* globalCtx){

    if (bomb!=0 && thisx->xzDistToPlayer < 50.0f){
        *(((u8*)(bomb)) + 0x26C) = 2; //bomb timer
        bomb = 0;
    }

    EnBox_Update(thisx, globalCtx);
}

u8 Chest_OverrideAnimation(){

    if((gSettingsContext.chestAnimations == ALWAYS_FAST) || (rActiveItemActionId == 0)) //The animation is always fast for unused chests that aren't randomized
        return 0;

    if(!rActiveItemFastChest){
        PlaySound(0x1000599); //Play chest opening fanfare
    }
    return !rActiveItemFastChest;
}

u8 Chest_OverrideDecoration(){

    if(type == DECORATED_BIG || ((gSettingsContext.chestSize == SIZE_MATCHES_CONTENT) && (type == DECORATED_SMALL))){
        return 1;
    }
    return 0;
}

u8 Chest_OverrideIceSmoke(Actor* thisx){
    if(gSettingsContext.randomTrapDmg == OFF){
        return 0;
    }

    if(thisx != lastTrapChest && thisx->xzDistToPlayer < 50.0f){
        lastTrapChest = thisx;
        u8 damageType = gRandInt % 6;
        if(damageType == 3){
            return 0;
        }
        PLAYER->getItemId = 0;
        PLAYER->stateFlags1 &= ~0x20000C00;
        PLAYER->actor.colChkInfo.damage = Settings_ApplyDamageMultiplier(gGlobalContext, (gSettingsContext.mirrorWorld)? 16 : 8);
        if(damageType == 0 || ((damageType == 1 || damageType == 5) && gRandInt % 2)) { //For knockback
            PLAYER->stateFlags1 |= 0x4000; //Ledge Cancel
        }
        if(PLAYER->invincibilityTimer > 0){
            PLAYER->invincibilityTimer = 0;
        }
        //Big knockback, small knockback or shock
        if(damageType == 0 || damageType == 2 || damageType == 4){
            LinkDamage(gGlobalContext, PLAYER, damageType, 0.0f, 0.0f, 0, 20);
            return 1;
        }
        //Bomb surprise
        else if(damageType == 1 || damageType == 5){
            bomb = Actor_Spawn((&(gGlobalContext->actorCtx)), gGlobalContext, 0x10, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0);
            bomb->world.pos = thisx->world.pos;
        }
    }

    return 1;
}
