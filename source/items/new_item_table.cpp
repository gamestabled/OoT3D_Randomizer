#include "new_item_table.hpp"

#include "../code/include/z3D/z3Ditem.h"

NewItemTable::NewItemTable() : 
    kokiriSword(Text{"Kokiri Sword",                    "Épée Kokiri",                      "Espada Kokiri"},                     NewItem::Type::Item,  GI_SWORD_KOKIRI,   true),
    // masterSword,
    giantsKnife(Text{"Giant's Knife",                   "Lame de géant",                    "Espada de Biggoron"},                NewItem::Type::Item,  GI_SWORD_KNIFE,    false),
    biggoronSword(Text{"Biggoron's Sword",                "Épée de Grogoron",                 "Espada de Biggoron"},              NewItem::Type::Item,  GI_SWORD_BGS,      true),
    dekuShield(Text{"Deku Shield",                     "Bouclier Mojo",                    "Escudo deku"},                        NewItem::Type::Item,  GI_SHIELD_DEKU,    false),
    hylianShield(Text{"Hylian Shield",                   "Bouclier Hylien",                  "Escudo hyliano"},                   NewItem::Type::Item,  GI_SHIELD_HYLIAN,  false),
    mirrorShield(Text{"Mirror Shield",                   "Bouclier miroir",                  "Escudo espejo"},                    NewItem::Type::Item,  GI_SHIELD_MIRROR,  true)
{
}
