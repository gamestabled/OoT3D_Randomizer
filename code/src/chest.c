#include "chest.h"
#include "z3D/z3D.h"
#include "item_override.h"
#include "item_table.h"
#include "settings.h"

#define EnBox_Init_addr 0x1899EC
#define EnBox_Init ((ActorFunc)EnBox_Init_addr)

#define PlaySound_addr 0x35C528
#define PlaySound ((void(*)(u32))PlaySound_addr) //this function plays sound effects

static u8 type = 0;

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx){
    // treasure box shop chests
    if((gSettingsContext.chestSize == 0) || (globalCtx->sceneNum == 16 && thisx->room != 6)){
        return EnBox_Init(thisx, globalCtx);
    }
    
    ItemOverride thisOverride = ItemOverride_Lookup(thisx, globalCtx->sceneNum, 0);
    ItemRow* thisItemRow;
    if (thisOverride.key.all == 0){
        thisItemRow = ItemTable_GetItemRowFromIndex((thisx->params & 0x0FE0) >> 5); //needed for non-randomized chests (small keys should be golden chests?)
    }       
    else{
        thisItemRow = ItemTable_GetItemRow(ItemTable_ResolveUpgrades(thisOverride.value.itemId));
    }
    type = thisItemRow->chestType;
    
    EnBox_Init(thisx, globalCtx);
    
    if(type == 0 || type == 2){
        thisx->scale.x = 0.01f;
        thisx->scale.y = 0.01f;
        thisx->scale.z = 0.01f;
    }
    else{
        thisx->scale.x = 0.005f;
        thisx->scale.y = 0.005f;
        thisx->scale.z = 0.005f;
    }
}

u8 Chest_OverrideAnimation(){
    
    if((gSettingsContext.chestAnimations == 0) || (rActiveItemActionId == 0)) //The animation is always fast for chests that the randomizer doesn't touch
        return 0;

    u8 isSlow = (rActiveItemFastChest==0 || rActiveItemFastChest==2);
    if(isSlow){
        PlaySound(0x1000599); //Play chest opening fanfare
    }
    return isSlow;
}

u8 Chest_OverrideDecoration(){
        
    if(type == 2 || ((gSettingsContext.chestSize != 0) && (type == 3))){
        return 1;
    }
    return 0;
}
