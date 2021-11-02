#include "world_settings.hpp"

const std::string WorldSettings::setDungeonTypesDesc = "If set, you can choose specific dungeons to be vanilla, MQ, or random";

WorldSettings::WorldSettings() :
        randomizeWorld(std::move(Setting::Bool("Randomize Settings", "Randomize all World Settings except for MQ dungeons", {
            Setting::Option("No", ""),
            Setting::Option("Yes", ""),
        }))),
        startingAge(std::move(Setting::Int("Starting Age", "Choose which age Link will start as\n\n"
                                        "Starting as adult means you start with the Master Sword in your inventory\n\n"
                                        "Only the child option is compatible with Closed Forest", {
            Setting::Option("Adult", ""),
            Setting::Option("Child", ""),
            Setting::Option("Random", ""),
        }, Setting::Category::NonCosmetic, (size_t)AgeSetting::Child))),
        shuffleEntrances(std::move(Setting::Bool("Shuffle Entrances", "Shuffle where the entrances between areas lead to."
                                        " If turned on, select which kinds of entrances you want shuffled in the options below.", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleDungeonEntrances(std::move(Setting::Bool("  Dungeon Entrances", "Shuffle the pool of dungeon entrances, including"
                                        "Bottom of the Well, Ice Cavern, and Gerudo Training Grounds. However, Ganon's Castle is not"
                                        " shuffled.\n\n"
                                        "Additionally, the entrances of Deku Tree, Fire Temple and Bottom of the Well are opened for both"
                                        " adult and child.", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleOverworldEntrances(std::move(Setting::Bool("  Dungeon Entrances", "Shuffle the pool of Overworld entrances, which corresponds"
                                        " to almost all loading zones between Overworld areas.\n\n"
                                        "Some entrances are unshuffled to avoid issues:\n"
                                        "- Hyrule Castle Courtyard and Garden entrance\n"
                                        "- Both Market Back Alley entrances\n"
                                        "- Gerudo Valley to Lake Hylia (unless entrances are decoupled)", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleInteriorEntrances(std::move(Setting::Int("  Dungeon Entrances", "", {
            Setting::Option("Off", ""),
            Setting::Option("Simple", ""),
            Setting::Option("All", ""),
        }))),
        bombchusInLogic(std::move(Setting::Bool("Bombchus in Logic", "Bombchus are properly considered in logic. They can be replenished in shops,"
                                        " or through bombchu drops, if those are enabled.\n\n"
                                        "Bombchu Bowling is opened by bombchus", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        ammoDrops(std::move(Setting::Int("Ammo Drops", "", {
            Setting::Option("On", "Bombs, arrows, seeds, nuts, sticks and magic jars appear as normal"),
            Setting::Option("On + Bombchu", "Bombs, arrows, seeds, nuts, sticks and magic jars appear as normal.\n"
                                        "Bombchus can sometimes replace bomb drops"),
            Setting::Option("Off", "All ammo drops will be replaced by blue rupees, except for Deku Sticks.\n"
                                        "Ammo upgrades will only refill ammo by 10 units"),
        }, Setting::Category::NonCosmetic, (size_t)AmmoDrops::Bombchu))),
        heartDropRefill(std::move(Setting::Int("Heart Drops and Refills", "", {
            Setting::Option("On", "Heart drops will appear as normal.\n"
                                        "Health upgrades fully heal Link when picked up.\n"
                                        "Fairies heal Link as normal"),
            Setting::Option("No Drop", "Heart drops will be replaced by green rupees.\n"
                                        "Health upgrades fully heal Link when picked up.\n"
                                        "Fairies heal Link as normal"),
            Setting::Option("No Refill", "Heart drops will appear as normal.\n"
                                        "Health upgrades don't heal Link when picked up.\n"
                                        "Fairies heal Link by only 3 hearts"),
            Setting::Option("Off", "Heart drops will be replaced by green rupees.\n"
                                        "Health upgrades don't heal Link when picked up.\n"
                                        "Fairies heal Link by only 3 hearts"),
        }, Setting::Category::NonCosmetic, (size_t)HeartDropRefills::Vanilla))),
        mqDungeonCount(std::move(Setting::Range("MQ Dungeon Count", "Specify the number of Master Quest dungeons to appear in the game."
                                        " Which dungeons become Master Quest will be chosen at random.", 0, 13))),
        setDungeonTypes(std::move(Setting::Bool("Set Dungeon Types", setDungeonTypesDesc, {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        mqDeku(std::move(Setting::Int("  Deku Tree", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqDodongo(std::move(Setting::Int("  Dodongo's Cavern", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqJabu(std::move(Setting::Int("  Jabu-Jabu's Belly", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqForest(std::move(Setting::Int("  Forest Temple", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqFire(std::move(Setting::Int("  Fire Temple", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqWater(std::move(Setting::Int("  Water Temple", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqSpirit(std::move(Setting::Int("  Spirit Temple", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqShadow(std::move(Setting::Int("  Shadow Temple", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqBotW(std::move(Setting::Int("  Bottom of the Well", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqIceCavern(std::move(Setting::Int("  Ice Cavern", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqGTG(std::move(Setting::Int("  Training Grounds", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        mqCastle(std::move(Setting::Int("  Ganon's Castle", setDungeonTypesDesc, {
            Setting::Option("Vanilla", ""),
            Setting::Option("Master Quest", ""),
            Setting::Option("Random", ""),
        }))),
        dungeonSettings({
            &mqDeku,
            &mqDodongo,
            &mqJabu,
            &mqForest,
            &mqFire,
            &mqWater,
            &mqSpirit,
            &mqShadow,
            &mqBotW,
            &mqIceCavern,
            &mqGTG,
            &mqCastle,
        }) {
    mqDungeonCount.addOption("Random", "");

    push_back(&randomizeWorld);
    push_back(&startingAge);
    push_back(&shuffleEntrances);
    push_back(&shuffleDungeonEntrances);
    push_back(&shuffleOverworldEntrances);
    push_back(&shuffleInteriorEntrances);
    push_back(&bombchusInLogic);
    push_back(&ammoDrops);
    push_back(&heartDropRefill);
    push_back(&mqDungeonCount);
    push_back(&setDungeonTypes);
    push_back(&mqDeku);
    push_back(&mqDodongo);
    push_back(&mqJabu);
    push_back(&mqForest);
    push_back(&mqFire);
    push_back(&mqWater);
    push_back(&mqSpirit);
    push_back(&mqShadow);
    push_back(&mqBotW);
    push_back(&mqIceCavern);
    push_back(&mqGTG);
    push_back(&mqCastle);
}

void WorldSettings::update() {
    if (shuffleEntrances) {
        shuffleDungeonEntrances.unhide();
        shuffleOverworldEntrances.unhide();
        shuffleInteriorEntrances.unhide();
    } else {
        shuffleDungeonEntrances.setSelectedIndex(Setting::Off);
        shuffleDungeonEntrances.hide();
        shuffleOverworldEntrances.setSelectedIndex(Setting::Off);
        shuffleOverworldEntrances.hide();
        shuffleInteriorEntrances.setSelectedIndex((size_t)ShuffleInteriorEntrances::Off);
        shuffleInteriorEntrances.hide();
    }

    if (setDungeonTypes) {
        for (Setting* dungeonSetting : dungeonSettings) {
            dungeonSetting->unhide();
        }

        size_t mqCount = dungeonsOfType(DungeonSetting::MQ);
        size_t randomCount = dungeonsOfType(DungeonSetting::Random);

        if (mqDungeonCount.value<size_t>() < mqCount) {
            tooManyMQDungeonsSelectedError = true;
        } else {
            tooManyMQDungeonsSelectedError = false;
        }

        if ((mqDungeonCount.value<size_t>() != (size_t)MQDungeonCount::Random) && (mqDungeonCount.value<size_t>() > (mqCount + randomCount))) {
            notEnoughMQDungeonsSelectedError = true;
        } else {
            notEnoughMQDungeonsSelectedError = false;
        }
    } else {
        for (Setting* dungeonSetting : dungeonSettings) {
            dungeonSetting->setSelectedIndex((size_t)DungeonSetting::Random);
            dungeonSetting->hide();
        }
    }
}

size_t WorldSettings::dungeonsOfType(DungeonSetting type) {
    size_t count = 0;

    for (Setting* dungeonSetting : dungeonSettings) {
        if (dungeonSetting->value<size_t>() == (size_t)DungeonSetting::MQ) {
            count++;
        }
    }

    return count;
}
