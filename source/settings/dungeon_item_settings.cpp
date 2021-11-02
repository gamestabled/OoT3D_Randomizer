#include "dungeon_item_settings.hpp"

const std::string DungeonItemSettings::ganonsKeyLACSDesc = "These settings put the boss key on the Light Arrow Cutscene location, from Zelda in Temple of Time as adult, with differing requirements";

DungeonItemSettings::DungeonItemSettings() :
        randomizeDungeonItems(std::move(Setting::Bool("Randomize Settings", "Randomize all Dungeon Item settings", {
            Setting::Option("No", ""),
            Setting::Option("Yes", ""),
        }))),
        mapsAndCompasses(std::move(Setting::Int("Maps and Compasses", "", {
            Setting::Option("Start With", "Maps and Compasses are given to you from the start. This will add a small amount of money and refill items to the pool"),
            Setting::Option("Vanilla", "Maps and Compasses will appear in their vanilla locations"),
            Setting::Option("Own Dungeon", "Maps and Compasses can only appear in their respective dungeon"),
            Setting::Option("Any Dungeon", "Maps and Compasses can only appear in a dungeon but not necessarily the dungeon they are for"),
            Setting::Option("Overworld", "Maps and Compasses can only appear outside of dungeons"),
            Setting::Option("Anywhere", "Maps and Compasses can appear anywhere in the world"),
        }, Setting::Category::NonCosmetic, (size_t)MapsAndCompassesSetting::OwnDungeon))),
        smallKeys(std::move(Setting::Int("Small Keys", "", {
            Setting::Option("Start With", "Small Keys are given to you from the start so you won't have to worry about locked doors. An easier mode"),
            Setting::Option("Vanilla", "Small Keys will appear in their vanilla locations. You start with 3 keys in Spirit Temple MQ because the vanilla key layout is not beatable in logic"),
            Setting::Option("Own Dungeon", "Small Keys can only appear in their respective dungeon. If Fire Temple is not a Master Quest dungeon, the door to the Boss Key chest will be unlocked"),
            Setting::Option("Any Dungeon", "Small Keys can only appear inside of any dungeon, but won't necessarily be in the dungeon that the key is for. A difficult mode since it is more likely to need to enter a dungeon multiple times"),
            Setting::Option("Overworld", "Small Keys can only appear outside of dungeons. You may need to enter a dungeon multiple times to gain items to access the overworld locations with the keys required to finish a dungeon"),
            Setting::Option("Anywhere", "Small Keys can appear anywhere in the world. A difficult mode since it is more likely to need to enter a dungeon multiple times"),
        }, Setting::Category::NonCosmetic, (size_t)SmallKeysSetting::OwnDungeon))),
        gerudoKeys(std::move(Setting::Int("Gerudo Fortress Keys", "", {
            Setting::Option("Vanilla", "Gerudo Fortress Keys will appear in their vanilla location, dropping from fighting Gerudo guards that attack when trying to free the jailed carpenters"),
            Setting::Option("Any Dungeon", "Gerudo Fortress Keys can only appear inside of dungeons"),
            Setting::Option("Overworld", "Gerudo Fortress Keys can only appear outside of dungeons"),
            Setting::Option("Anywhere", "Gerudo Fortress Keys can appear anywhere in the world"),
        }))),
        bossKeys(std::move(Setting::Int("Boss Keys", "", {
            Setting::Option("Start With", "Boss Keys are given to you from the start so you won't have to worry about boss doors. An easier mode"),
            Setting::Option("Vanilla", "Boss Keys will appear in their vanilla locations"),
            Setting::Option("Own Dungeon", "Boss Keys can only appear in their respective dungeon"),
            Setting::Option("Any Dungeon", "Boss Keys can only appear inside of any dungeon, but won't necessarily be in the dungeon that the key is for. A difficult mode since it is more likely to need to enter a dungeon multiple times"),
            Setting::Option("Overworld", "Boss Keys can only appear outside of dungeons. You may need to enter a dungeon without the boss key to get items required to find the key in the overworld"),
            Setting::Option("Anywhere", "Boss Keys can appear anywhere in the world. A difficult mode since it is more likely to need to enter a dungeon multiple times"),
        }, Setting::Category::NonCosmetic, (size_t)BossKeysSetting::OwnDungeon))),
        ganonsBossKey(std::move(Setting::Int("Ganon's Castle Boss Key", "", {
            Setting::Option("Start With", "Ganon's Castle Boss Key is given to you from the start and you don't have to worry about finding it"),
            Setting::Option("Vanilla", "Ganon's Castle Boss Key will appear in the vanilla location"),
            Setting::Option("Own Dungeon", "Ganon's Castle Boss Key can only appear inside Ganon's Castle"),
            Setting::Option("Any Dungeon", "Ganon's Castle Boss Key can only appear inside of a dungeon, but not necessarily Ganon's Castle"),
            Setting::Option("Overworld", "Ganon's Castle Boss Key can only appear outside of dungeons"),
            Setting::Option("Anywhere", "Ganon's Castle Boss Key can appear anywhere in the world"),
            Setting::Option("LACS-Vanilla", ganonsKeyLACSDesc),
            Setting::Option("LACS-Medallions", ganonsKeyLACSDesc),
            Setting::Option("LACS-Stones", ganonsKeyLACSDesc),
            Setting::Option("LACS-Rewards", ganonsKeyLACSDesc),
            Setting::Option("LACS-Dungeons", ganonsKeyLACSDesc),
            Setting::Option("LACS-Tokens", ganonsKeyLACSDesc),
        }, Setting::Category::NonCosmetic, (size_t)GanonsBossKeySetting::OwnDungeon))),
        lacsMedallionCount(std::move(Setting::Range("  Medallion Count", "Set the number of Medallions required to trigger the Light Arrow Cutscene", 0, 7, Setting::Category::NonCosmetic, 1, true))),
        lacsStoneCount(std::move(Setting::Range("  Stone Count", "Set the number of Spiritual Stones required to trigger the Light Arrow Cutscene", 0, 4, Setting::Category::NonCosmetic, 1, true))),
        lacsRewardCount(std::move(Setting::Range("  Reward Count", "Set the number of Dungeon Rewards (Spiritual Stones and Medallions) required to trigger the Light Arrow Cutscene", 0, 10, Setting::Category::NonCosmetic, 1, true))),
        lacsDungeonCount(std::move(Setting::Range("  Dungeon Count", "Set the number of completed dungeons required to trigger the Light Arrow Cutscene\n\nDungeons are considered complete when Link steps into the blue warp at the end of them", 0, 9, Setting::Category::NonCosmetic, 1, true))),
        lacsTokenCount(std::move(Setting::Range("  Token Count", "Set the number of Gold Skulltula Tokens required to trigger the Light Arrow Cutscene", 0, 101, Setting::Category::NonCosmetic, 1, true))) {
    push_back(&randomizeDungeonItems);
    push_back(&mapsAndCompasses);
    push_back(&smallKeys);
    push_back(&gerudoKeys);
    push_back(&bossKeys);
    push_back(&ganonsBossKey);
    push_back(&lacsMedallionCount);
    push_back(&lacsStoneCount);
    push_back(&lacsRewardCount);
    push_back(&lacsDungeonCount);
    push_back(&lacsTokenCount);
}

void DungeonItemSettings::update() {
    if (ganonsBossKey.is(GanonsBossKeySetting::LACSMedallions)) {
        lacsMedallionCount.unhide();
    } else {
        lacsMedallionCount.setSelectedIndex(6);
        lacsMedallionCount.hide();
    }

    if (ganonsBossKey.is(GanonsBossKeySetting::LACSStones)) {
        lacsStoneCount.unhide();
    } else {
        lacsStoneCount.setSelectedIndex(3);
        lacsStoneCount.hide();
    }

    if (ganonsBossKey.is(GanonsBossKeySetting::LACSRewards)) {
        lacsRewardCount.unhide();
    } else {
        lacsRewardCount.setSelectedIndex(9);
        lacsRewardCount.hide();
    }

    if (ganonsBossKey.is(GanonsBossKeySetting::LACSDungeons)) {
        lacsDungeonCount.unhide();
    } else {
        lacsDungeonCount.setSelectedIndex(8);
        lacsDungeonCount.hide();
    }

    if (ganonsBossKey.is(GanonsBossKeySetting::LACSTokens)) {
        lacsTokenCount.unhide();
    } else {
        lacsTokenCount.setSelectedIndex(100);
        lacsTokenCount.hide();
    }
}
