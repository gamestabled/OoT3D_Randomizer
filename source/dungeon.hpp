#pragma once

#include <string>

#include "category.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "pool_functions.hpp"

namespace Dungeon {
class DungeonInfo {
public:
      DungeonInfo(std::string name_, Item* map_, Item* compass_, Item* smallKey_, Item* bossKey_, u8 vanillaKeyCount_, u8 mqKeyCount_,
              std::vector<ItemLocation*> vanillaLocations_, std::vector<ItemLocation*> mqLocations_, std::vector<ItemLocation*> sharedLocations_)
            : name(std::move(name_)),
              map(map_),
              compass(compass_),
              smallKey(smallKey_),
              bossKey(bossKey_),
              vanillaKeyCount(vanillaKeyCount_),
              mqKeyCount(mqKeyCount_),
              vanillaLocations(std::move(vanillaLocations_)),
              mqLocations(std::move(mqLocations_)),
              sharedLocations(std::move(sharedLocations_)) {}

      std::string GetName() const {
          return name;
      }

      void SetMQ() {
          masterQuest = true;
      }

      bool IsMQ() const {
          return masterQuest;
      }

      bool IsVanilla() const {
          return !masterQuest;
      }

      Item GetSmallKey() const {
          return *smallKey;
      }

      Item GetMap() const {
          return *map;
      }

      Item GetCompass() const {
          return *compass;
      }

      Item GetBossKey() const {
          return *bossKey;
      }

      u8 GetSmallKeyCount() const {
          return (masterQuest) ? mqKeyCount : vanillaKeyCount;
      }

      void PlaceVanillaMap() {
          if (*map != NoItem) {
              auto dungeonLocations = GetDungeonLocations();
              auto mapLocation = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaMap); })[0];
              PlaceItemInLocation(mapLocation, *map);
          }
      }

      void PlaceVanillaCompass() {
          if (*compass != NoItem) {
              auto dungeonLocations = GetDungeonLocations();
              auto compassLocation = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaCompass); })[0];
              PlaceItemInLocation(compassLocation, *compass);
          }
      }

      void PlaceVanillaBossKey() {
          if (*bossKey != NoItem) {
              auto dungeonLocations = GetDungeonLocations();
              auto bossKeyLocation = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaBossKey); })[0];
              PlaceItemInLocation(bossKeyLocation, *bossKey);
          }
      }

      void PlaceVanillaSmallKeys() {
          if (*smallKey != NoItem) {
              auto dungeonLocations = GetDungeonLocations();
              auto smallKeyLocations = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaSmallKey); });
              for (auto location : smallKeyLocations) {
                  PlaceItemInLocation(location, *smallKey);
              }
          }
      }

      //Gets the chosen dungeon locations for a playthrough (so either MQ or Vanilla)
      std::vector<ItemLocation*> GetDungeonLocations() const {
          auto locations = masterQuest ? mqLocations : vanillaLocations;
          AddElementsToPool(locations, sharedLocations);
          return locations;
      }

      //Gets all dungeon locations (MQ + Vanilla)
      std::vector<ItemLocation*> GetEveryLocation() const {
          auto locations = vanillaLocations;
          AddElementsToPool(locations, mqLocations);
          AddElementsToPool(locations, sharedLocations);
          return locations;
      }

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

extern std::vector<DungeonInfo*> dungeonList;
} // namespace Dungeon
