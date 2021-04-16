#pragma once

#include <3ds.h>
#include <array>
#include <string>
#include <vector>

class Item;
class ItemLocation;

namespace Dungeon {
class DungeonInfo {
public:
    DungeonInfo(std::string name_, Item* map_, Item* compass_,
                Item* smallKey_, Item* bossKey_, u8 vanillaKeyCount_, u8 mqKeyCount_,
                std::vector<ItemLocation*> vanillaLocations_,
                std::vector<ItemLocation*> mqLocations_,
                std::vector<ItemLocation*> sharedLocations_);
    ~DungeonInfo();

    std::string_view GetName() const {
        return name;
    }

    void SetMQ() {
        masterQuest = true;
    }

    void ClearMQ() {
        masterQuest = false;
    }

    bool IsMQ() const {
        return masterQuest;
    }

    bool IsVanilla() const {
        return !masterQuest;
    }

    u8 GetSmallKeyCount() const {
        return (masterQuest) ? mqKeyCount : vanillaKeyCount;
    }

    const Item& GetSmallKey() const;
    const Item& GetMap() const;
    const Item& GetCompass() const;
    const Item& GetBossKey() const;

    void PlaceVanillaMap();
    void PlaceVanillaCompass();
    void PlaceVanillaBossKey();
    void PlaceVanillaSmallKeys();

    // Gets the chosen dungeon locations for a playthrough (so either MQ or Vanilla)
    std::vector<ItemLocation*> GetDungeonLocations() const;

    // Gets all dungeon locations (MQ + Vanilla)
    std::vector<ItemLocation*> GetEveryLocation() const;

private:
    std::string name;
    Item* map;
    Item* compass;
    Item* smallKey;
    Item* bossKey;
    u8 vanillaKeyCount;
    u8 mqKeyCount;
    bool masterQuest = false;
    std::vector<ItemLocation*> vanillaLocations;
    std::vector<ItemLocation*> mqLocations;
    std::vector<ItemLocation*> sharedLocations;
};

extern DungeonInfo DekuTree;
extern DungeonInfo DodongosCavern;
extern DungeonInfo JabuJabusBelly;
extern DungeonInfo ForestTemple;
extern DungeonInfo FireTemple;
extern DungeonInfo WaterTemple;
extern DungeonInfo SpiritTemple;
extern DungeonInfo ShadowTemple;
extern DungeonInfo BottomOfTheWell;
extern DungeonInfo IceCavern;
extern DungeonInfo GerudoTrainingGrounds;
extern DungeonInfo GanonsCastle;

using DungeonArray = std::array<DungeonInfo*, 12>;

extern const DungeonArray dungeonList;
} // namespace Dungeon
