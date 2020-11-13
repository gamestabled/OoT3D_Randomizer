#include "z3D/z3D.h"
#include "item_override.h"


//Patched over call to Item_Give
void Cutscene_OverrideOcarinaSongs(GlobalContext* GlobalContext, ItemID songId) {
    ItemOverride_PushDelayedOverride(songId - ITEM_SONG_MINUET + 0x20); //TODO remove the hardcoded constant?
}