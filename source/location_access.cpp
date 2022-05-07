#include "location_access.hpp"

#include "dungeon.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "item_pool.hpp"
#include "logic.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "trial.hpp"
#include "entrance.hpp"

#include <unistd.h>
#include <fstream>
#include <iostream>

using namespace Logic;
using namespace Settings;

bool DAY_NIGHT_CYCLE    = true;
bool NO_DAY_NIGHT_CYCLE = false;

//generic grotto event list
static std::vector<EventAccess> grottoEvents = {
  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
  EventAccess(&ButterflyFairy,   {[]{return ButterflyFairy   || (CanUse(STICKS));}}),
  EventAccess(&BugShrub,         {[]{return CanCutShrubs;}}),
  EventAccess(&LoneFish,         {[]{return true;}}),
};

//set the logic to be a specific age and time of day and see if the condition still holds
bool LocationAccess::CheckConditionAtAgeTime(bool& age, bool& time) const {

  IsChild = false;
  IsAdult = false;
  AtDay   = false;
  AtNight = false;

  time = true;
  age = true;

  UpdateHelpers();
  return GetConditionsMet();
}

bool LocationAccess::ConditionsMet() const {

  Area* parentRegion = AreaTable(Location(location)->GetParentRegionKey());
  bool conditionsMet = false;

  if ((parentRegion->childDay   && CheckConditionAtAgeTime(IsChild, AtDay))   ||
      (parentRegion->childNight && CheckConditionAtAgeTime(IsChild, AtNight)) ||
      (parentRegion->adultDay   && CheckConditionAtAgeTime(IsAdult, AtDay))   ||
      (parentRegion->adultNight && CheckConditionAtAgeTime(IsAdult, AtNight))) {
        conditionsMet = true;
  }

  return conditionsMet && CanBuy();
}

bool LocationAccess::CanBuy() const {
  //Not a shop location, don't need to check if buyable
  if (!(Location(location)->IsCategory(Category::cShop))) {
    return true;
  }

  //Check if wallet is large enough to buy item
  bool SufficientWallet = true;
  if (Location(location)->GetPrice() > 500) {
    SufficientWallet = ProgressiveWallet >= 3;
  } else if (Location(location)->GetPrice() > 200) {
    SufficientWallet = ProgressiveWallet >= 2;
  } else if (Location(location)->GetPrice() > 99) {
    SufficientWallet = ProgressiveWallet >= 1;
  }

  bool OtherCondition = true;
  u32 placed = Location(location)->GetPlacedItemKey();
  //Need bottle to buy bottle items, only logically relevant bottle items included here
  if (placed == BUY_BLUE_FIRE || placed == BUY_BOTTLE_BUG || placed == BUY_FISH || placed == BUY_FAIRYS_SPIRIT) {
    OtherCondition = HasBottle;
  }
  //If bombchus in logic, need to have found chus to buy; if not just need bomb bag
  else if (placed == BUY_BOMBCHU_5 || placed == BUY_BOMBCHU_10 || placed == BUY_BOMBCHU_20) {
    OtherCondition = (!BombchusInLogic && Bombs) || (BombchusInLogic && FoundBombchus);
  }

  return SufficientWallet && OtherCondition;
}

Area::Area() = default;
Area::Area(std::string regionName_, std::string scene_, u32 hintKey_,
         bool timePass_,
         std::vector<EventAccess> events_,
         std::vector<LocationAccess> locations_,
         std::list<Entrance> exits_)
  : regionName(std::move(regionName_)),
    scene(std::move(scene_)),
    hintKey(hintKey_),
    timePass(timePass_),
    events(std::move(events_)),
    locations(std::move(locations_)),
    exits(std::move(exits_)) {}

Area::~Area() = default;

bool Area::UpdateEvents(SearchMode mode) {

  if (timePass && mode != SearchMode::TimePassAccess) {
    if (Child()) {
      childDay = true;
      childNight = true;
      AreaTable(ROOT)->childDay = true;
      AreaTable(ROOT)->childNight = true;
    }
    if (Adult()) {
      adultDay = true;
      adultNight = true;
      AreaTable(ROOT)->adultDay = true;
      AreaTable(ROOT)->adultNight = true;
    }
  }

  bool eventsUpdated =  false;

  for (EventAccess& event : events) {
    //If the event has already happened, there's no reason to check it
    if (event.GetEvent()) {
      continue;
    }

    if ((childDay   && event.CheckConditionAtAgeTime(IsChild, AtDay))    ||
        (childNight && event.CheckConditionAtAgeTime(IsChild, AtNight))  ||
        (adultDay   && event.CheckConditionAtAgeTime(IsAdult, AtDay))    ||
        (adultNight && event.CheckConditionAtAgeTime(IsAdult, AtNight))) {
          event.EventOccurred();
          eventsUpdated = true;
    }
  }
  return eventsUpdated;
}

void Area::AddExit(AreaKey parentKey, AreaKey newExitKey, ConditionFn condition) {
  Entrance newExit = Entrance(newExitKey, {condition});
  newExit.SetParentRegion(parentKey);
  exits.push_front(newExit);
}

//The exit will be completely removed from this area
void Area::RemoveExit(Entrance* exitToRemove) {
  exits.remove_if([exitToRemove](const auto exit){return &exit == exitToRemove;});
}

void Area::SetAsPrimary(AreaKey exitToBePrimary) {
  for (auto& exit : exits) {
    if (exit.GetAreaKey() == exitToBePrimary) {
      exit.SetAsPrimary();
      return;
    }
  }
}

Entrance* Area::GetExit(AreaKey exitToReturn) {
  for (auto& exit : exits) {
    if (exit.GetAreaKey() == exitToReturn) {
      return &exit;
    }
  }
  auto message = "ERROR: EXIT " + AreaTable(exitToReturn)->regionName + " DOES NOT EXIST IN " + this->regionName;
  CitraPrint(message);
  return nullptr;
}

bool Area::CanPlantBeanCheck() const {
  return (Logic::MagicBean || Logic::MagicBeanPack) && BothAgesCheck();
}

bool Area::AllAccountedFor() const {
  for (const EventAccess& event : events) {
    if (!event.GetEvent()) {
      return false;
    }
  }

  for (const LocationAccess& loc : locations) {
    if (!(Location(loc.GetLocation())->IsAddedToPool())) {
      return false;
    }
  }

  for (const auto& exit : exits) {
    if (!exit.GetConnectedRegion()->AllAccess()) {
      return false;
    }
  }

  return AllAccess();
}

bool Area::CheckAllAccess(const AreaKey exitKey) {
  if (!AllAccess()) {
    return false;
  }

  for (Entrance& exit : exits) {
    if (exit.GetAreaKey() == exitKey) {
      return exit.CheckConditionAtAgeTime(Logic::IsChild, Logic::AtDay)   &&
             exit.CheckConditionAtAgeTime(Logic::IsChild, Logic::AtNight) &&
             exit.CheckConditionAtAgeTime(Logic::IsAdult, Logic::AtDay)   &&
             exit.CheckConditionAtAgeTime(Logic::IsAdult, Logic::AtNight);
    }
  }
  return false;
}

void Area::ResetVariables() {
  childDay = false;
  childNight = false;
  adultDay = false;
  adultNight = false;
  addedToPool = false;
  for (auto& exit : exits) {
    exit.RemoveFromPool();
  }
}

static std::array<Area, KEY_ENUM_MAX> areaTable;

bool Here(const AreaKey area, ConditionFn condition) {
  return areaTable[area].HereCheck(condition);
}

bool CanPlantBean(const AreaKey area) {
  return areaTable[area].CanPlantBeanCheck();
}

bool BothAges(const AreaKey area) {
  return areaTable[area].BothAgesCheck();
}

bool ChildCanAccess(const AreaKey area) {
  return areaTable[area].Child();
}

bool HasAccessTo(const AreaKey area) {
  return areaTable[area].HasAccess();
}



void AreaTable_Init() {
  //Clear the array from any previous playthrough attempts. This is important so that
  //locations which appear in both MQ and Vanilla dungeons don't get set in both areas.
  areaTable.fill(Area("Invalid Area", "Invalid Area", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {}));

                       //name, scene, hint text,                       events, locations, exits
  areaTable[ROOT] = Area("Root", "", LINKS_POCKET, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LINKS_POCKET, {[]{return true;}})
                }, {
                  //Exits
                  Entrance(ROOT_EXITS, {[]{return true;}})
  });

  areaTable[ROOT_EXITS] = Area("Root Exits", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KF_LINKS_HOUSE,            {[]{return IsChild;}}),
                  Entrance(TEMPLE_OF_TIME,            {[]{return (CanPlay(PreludeOfLight)   && CanLeaveForest) || IsAdult;}}),
                  Entrance(SACRED_FOREST_MEADOW,      {[]{return  CanPlay(MinuetOfForest);}}),
                  Entrance(DMC_CENTRAL_LOCAL,         {[]{return  CanPlay(BoleroOfFire)     && CanLeaveForest;}}),
                  Entrance(LAKE_HYLIA,                {[]{return  CanPlay(SerenadeOfWater)  && CanLeaveForest;}}),
                  Entrance(GRAVEYARD_WARP_PAD_REGION, {[]{return  CanPlay(NocturneOfShadow) && CanLeaveForest;}}),
                  Entrance(DESERT_COLOSSUS,           {[]{return  CanPlay(RequiemOfSpirit)  && CanLeaveForest;}}),
  });

  areaTable[KOKIRI_FOREST] = Area("Kokiri Forest", "Kokiri Forest", KOKIRI_FOREST, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BeanPlantFairy,           {[]{return BeanPlantFairy   || (CanPlantBean(KOKIRI_FOREST) && CanPlay(SongOfStorms));}}),
                  EventAccess(&GossipStoneFairy,         {[]{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}}),
                  EventAccess(&ShowedMidoSwordAndShield, {[]{return ShowedMidoSwordAndShield || (IsChild && KokiriSword && DekuShield);}}),
                }, {
                  //Locations
                  LocationAccess(KF_KOKIRI_SWORD_CHEST,   {[]{return IsChild;}}),
                  LocationAccess(KF_GS_KNOW_IT_ALL_HOUSE, {[]{return IsChild && CanChildAttack && AtNight && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) && CanGetNightTimeGS;}}),
                  LocationAccess(KF_GS_BEAN_PATCH,        {[]{return CanPlantBugs && CanChildAttack;}}),
                  LocationAccess(KF_GS_HOUSE_OF_TWINS,    {[]{return IsAdult && AtNight && CanUse(HOOKSHOT) && CanGetNightTimeGS;}}),
                  LocationAccess(KF_GOSSIP_STONE,         {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KF_LINKS_HOUSE,        {[]{return true;}}),
                  Entrance(KF_MIDOS_HOUSE,        {[]{return true;}}),
                  Entrance(KF_SARIAS_HOUSE,       {[]{return true;}}),
                  Entrance(KF_HOUSE_OF_TWINS,     {[]{return true;}}),
                  Entrance(KF_KNOW_IT_ALL_HOUSE,  {[]{return true;}}),
                  Entrance(KF_KOKIRI_SHOP,        {[]{return true;}}),
                  Entrance(KF_OUTSIDE_DEKU_TREE,  {[]{return IsAdult || OpenForest.Is(OPENFOREST_OPEN) || ShowedMidoSwordAndShield;}}),
                  Entrance(THE_LOST_WOODS,        {[]{return true;}}),
                  Entrance(LW_BRIDGE_FROM_FOREST, {[]{return CanLeaveForest;}}),
                  Entrance(KF_STORMS_GROTTO,      {[]{return CanOpenStormGrotto;}}),
  });

  areaTable[KF_OUTSIDE_DEKU_TREE] = Area("KF Outside Deku Tree", "Kokiri Forest", KOKIRI_FOREST, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks, {[]{return DekuBabaSticks || ((IsAdult && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF)) || KokiriSword || Boomerang);}}),
                  EventAccess(&DekuBabaNuts,   {[]{return DekuBabaNuts   || ((IsAdult && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF)) || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(DINS_FIRE));}}),
                }, {
                  //Locations
                  LocationAccess(KF_DEKU_TREE_GOSSIP_STONE_LEFT,  {[]{return true;}}),
                  LocationAccess(KF_DEKU_TREE_GOSSIP_STONE_RIGHT, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DEKU_TREE_ENTRYWAY, {[]{return IsChild || (ShuffleDungeonEntrances.IsNot(SHUFFLEDUNGEONS_OFF) && (OpenForest.Is(OPENFOREST_OPEN) || ShowedMidoSwordAndShield));}}),
                  Entrance(KOKIRI_FOREST,      {[]{return true;}}),
  });

  areaTable[KF_LINKS_HOUSE] = Area("KF Link's House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KF_LINKS_HOUSE_COW, {[]{return IsAdult && CanPlay(EponasSong) && LinksCow;}}),
                }, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}})
  });

  areaTable[KF_MIDOS_HOUSE] = Area("KF Mido's House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KF_MIDOS_TOP_LEFT_CHEST,     {[]{return true;}}),
                  LocationAccess(KF_MIDOS_TOP_RIGHT_CHEST,    {[]{return true;}}),
                  LocationAccess(KF_MIDOS_BOTTOM_LEFT_CHEST,  {[]{return true;}}),
                  LocationAccess(KF_MIDOS_BOTTOM_RIGHT_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}}),
  });

  areaTable[KF_SARIAS_HOUSE] = Area("KF Saria's House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}}),
  });

  areaTable[KF_HOUSE_OF_TWINS] = Area("KF House of Twins", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}}),
  });

  areaTable[KF_KNOW_IT_ALL_HOUSE] = Area("KF Know It All House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}}),
  });

  areaTable[KF_KOKIRI_SHOP] = Area("KF Kokiri Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KF_SHOP_ITEM_1, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_2, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_3, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_4, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_5, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_6, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_7, {[]{return true;}}),
                  LocationAccess(KF_SHOP_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}}),
  });

  areaTable[KF_STORMS_GROTTO] = Area("KF Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(KF_STORMS_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(KF_STORMS_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}})
  });

  areaTable[LW_FOREST_EXIT] = Area("LW Forest Exit", "Lost Woods", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KOKIRI_FOREST, {[]{return true;}})
  });

  areaTable[THE_LOST_WOODS] = Area("Lost Woods", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&OddMushroomAccess, {[]{return OddMushroomAccess || (IsAdult && (CojiroAccess || Cojiro));}}),
                  EventAccess(&PoachersSawAccess, {[]{return PoachersSawAccess || (IsAdult && OddPoulticeAccess);}}),
                  EventAccess(&GossipStoneFairy,  {[]{return GossipStoneFairy  || CanSummonGossipFairyWithoutSuns;}}),
                  EventAccess(&BeanPlantFairy,    {[]{return BeanPlantFairy    || CanPlay(SongOfStorms);}}),
                  EventAccess(&BugShrub,          {[]{return IsChild && CanCutShrubs;}}),
                }, {
                  //Locations
                  LocationAccess(LW_SKULL_KID,                 {[]{return IsChild && CanPlay(SariasSong);}}),
                  LocationAccess(LW_TRADE_COJIRO,              {[]{return IsAdult && Cojiro;}}),
                  LocationAccess(LW_TRADE_ODD_POULTICE,        {[]{return IsAdult && OddPoultice && Cojiro;}}),
                  LocationAccess(LW_OCARINA_MEMORY_GAME,       {[]{return IsChild && Ocarina;}}),
                  LocationAccess(LW_TARGET_IN_WOODS,           {[]{return CanUse(SLINGSHOT);}}),
                  LocationAccess(LW_DEKU_SCRUB_NEAR_BRIDGE,    {[]{return IsChild && CanStunDeku;}}),
                  LocationAccess(LW_GS_BEAN_PATCH_NEAR_BRIDGE, {[]{return CanPlantBugs && CanChildAttack;}}),
                  LocationAccess(LW_GOSSIP_STONE,              {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(LW_FOREST_EXIT,           {[]{return true;}}),
                  Entrance(GC_WOODS_WARP,            {[]{return true;}}),
                  Entrance(LW_BRIDGE,                {[]{return IsAdult && (CanUse(HOVER_BOOTS) || CanUse(LONGSHOT) || CanPlantBean(THE_LOST_WOODS));}}),
                  Entrance(ZORAS_RIVER,              {[]{return CanLeaveForest && (CanDive || CanUse(IRON_BOOTS));}}),
                  Entrance(LW_BEYOND_MIDO,           {[]{return IsChild || CanPlay(SariasSong);},
                                          /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}),
                  Entrance(LW_NEAR_SHORTCUTS_GROTTO, {[]{return Here(THE_LOST_WOODS, []{return CanBlastOrSmash;});}})
  });

  areaTable[LW_BEYOND_MIDO] = Area("LW Beyond Mido", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ButterflyFairy, {[]{return ButterflyFairy || CanUse(STICKS);}}),
                }, {
                  //Locations
                  LocationAccess(LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, {[]{return IsChild && CanStunDeku;}}),
                  LocationAccess(LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,  {[]{return IsChild && CanStunDeku;}}),
                  LocationAccess(LW_GS_ABOVE_THEATER,                   {[]{return IsAdult && AtNight && (CanPlantBean(LW_BEYOND_MIDO) || (LogicLostWoodsGSBean && CanUse(HOOKSHOT) && (CanUse(LONGSHOT) || CanUse(BOW) || HasBombchus || CanUse(DINS_FIRE)))) && CanGetNightTimeGS;}}),
                  LocationAccess(LW_GS_BEAN_PATCH_NEAR_THEATER,         {[]{return CanPlantBugs && (CanChildAttack || (Scrubsanity.Is(SCRUBSANITY_OFF) && DekuShield));}}),
                }, {
                  //Exits
                  Entrance(LW_FOREST_EXIT,   {[]{return true;}}),
                  Entrance(THE_LOST_WOODS,   {[]{return IsChild || CanPlay(SariasSong);}}),
                  Entrance(SFM_ENTRYWAY,     {[]{return true;}}),
                  Entrance(DEKU_THEATER,     {[]{return true;}}),
                  Entrance(LW_SCRUBS_GROTTO, {[]{return Here(LW_BEYOND_MIDO, []{return CanBlastOrSmash;});}}),
  });

  areaTable[LW_NEAR_SHORTCUTS_GROTTO] = Area("LW Near Shortcuts Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(LW_NEAR_SHORTCUTS_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(THE_LOST_WOODS, {[]{return true;}}),
  });

  areaTable[DEKU_THEATER] = Area("Deku Theater", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_THEATER_SKULL_MASK,    {[]{return IsChild && SkullMask;}}),
                  LocationAccess(DEKU_THEATER_MASK_OF_TRUTH, {[]{return IsChild && MaskOfTruth;}}),
                }, {
                  //Exits
                  Entrance(LW_BEYOND_MIDO, {[]{return true;}}),
  });

  areaTable[LW_SCRUBS_GROTTO] = Area("LW Scrubs Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LW_DEKU_SCRUB_GROTTO_REAR,  {[]{return CanStunDeku;}}),
                  LocationAccess(LW_DEKU_SCRUB_GROTTO_FRONT, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(LW_BEYOND_MIDO, {[]{return true;}}),
  });

  areaTable[SFM_ENTRYWAY] = Area("SFM Entryway", "Sacred Forest Meadow", SACRED_FOREST_MEADOW, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(LW_BEYOND_MIDO,       {[]{return true;}}),
                  Entrance(SACRED_FOREST_MEADOW, {[]{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse(DINS_FIRE);}}),
                  Entrance(SFM_WOLFOS_GROTTO,    {[]{return CanOpenBombGrotto;}}),
  });

  areaTable[SACRED_FOREST_MEADOW] = Area("Sacred Forest Meadow", "Sacred Forest Meadow", SACRED_FOREST_MEADOW, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}}),
                }, {
                  //Locations
                  LocationAccess(SONG_FROM_SARIA,             {[]{return IsChild && ZeldasLetter;}}),
                  LocationAccess(SHEIK_IN_FOREST,             {[]{return IsAdult;}}),
                  LocationAccess(SFM_GS,                      {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(SFM_MAZE_GOSSIP_STONE_LOWER, {[]{return true;}}),
                  LocationAccess(SFM_MAZE_GOSSIP_STONE_UPPER, {[]{return true;}}),
                  LocationAccess(SFM_SARIA_GOSSIP_STONE,      {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(SFM_ENTRYWAY,           {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_ENTRYWAY, {[]{return CanUse(HOOKSHOT);}}),
                  Entrance(SFM_FAIRY_GROTTO,       {[]{return true;}}),
                  Entrance(SFM_STORMS_GROTTO,      {[]{return CanOpenStormGrotto;}}),
  });

  areaTable[SFM_FAIRY_GROTTO] = Area("SFM Fairy Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FreeFairies, {[]{return true;}}),
                }, {}, {
                  //Exits
                  Entrance(SACRED_FOREST_MEADOW, {[]{return true;}}),
  });

  areaTable[SFM_WOLFOS_GROTTO] = Area("SFM Wolfos Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SFM_WOLFOS_GROTTO_CHEST, {[]{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse(DINS_FIRE);}}),
                }, {
                  //Exits
                  Entrance(SFM_ENTRYWAY, {[]{return true;}}),
  });

  areaTable[SFM_STORMS_GROTTO] = Area("SFM Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SFM_DEKU_SCRUB_GROTTO_REAR,  {[]{return CanStunDeku;}}),
                  LocationAccess(SFM_DEKU_SCRUB_GROTTO_FRONT, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(SACRED_FOREST_MEADOW, {[]{return true;}}),
  });

  areaTable[LW_BRIDGE_FROM_FOREST] = Area("LW Bridge From Forest", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LW_GIFT_FROM_SARIA, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(LW_BRIDGE, {[]{return true;}}),
  });

  areaTable[LW_BRIDGE] = Area("LW Bridge", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KOKIRI_FOREST,  {[]{return true;}}),
                  Entrance(HYRULE_FIELD,   {[]{return true;}}),
                  Entrance(THE_LOST_WOODS, {[]{return CanUse(LONGSHOT);}}),
  });

  areaTable[HYRULE_FIELD] = Area("Hyrule Field", "Hyrule Field", HYRULE_FIELD, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BigPoeKill, {[]{return CanUse(BOW) && CanRideEpona && HasBottle;}}),
                }, {
                  //Locations
                  LocationAccess(HF_OCARINA_OF_TIME_ITEM,   {[]{return IsChild && HasAllStones;}}),
                  LocationAccess(SONG_FROM_OCARINA_OF_TIME, {[]{return IsChild && HasAllStones;}}),
                }, {
                  //Exits
                  Entrance(LW_BRIDGE,              {[]{return true;}}),
                  Entrance(LAKE_HYLIA,             {[]{return true;}}),
                  Entrance(GERUDO_VALLEY,          {[]{return true;}}),
                  Entrance(MARKET_ENTRANCE,        {[]{return true;}}),
                  Entrance(KAKARIKO_VILLAGE,       {[]{return true;}}),
                  Entrance(ZR_FRONT,               {[]{return true;}}),
                  Entrance(LON_LON_RANCH,          {[]{return true;}}),
                  Entrance(HF_SOUTHEAST_GROTTO,    {[]{return Here(HYRULE_FIELD, []{return CanBlastOrSmash;});}}),
                  Entrance(HF_OPEN_GROTTO,         {[]{return true;}}),
                  Entrance(HF_INSIDE_FENCE_GROTTO, {[]{return CanOpenBombGrotto;}}),
                  Entrance(HF_COW_GROTTO,          {[]{return (CanUse(MEGATON_HAMMER) || IsChild) && CanOpenBombGrotto;}}),
                  Entrance(HF_NEAR_MARKET_GROTTO,  {[]{return Here(HYRULE_FIELD, []{return CanBlastOrSmash;});}}),
                  Entrance(HF_FAIRY_GROTTO,        {[]{return Here(HYRULE_FIELD, []{return CanBlastOrSmash;});}}),
                  Entrance(HF_NEAR_KAK_GROTTO,     {[]{return CanOpenBombGrotto;}}),
                  Entrance(HF_TEKTITE_GROTTO,      {[]{return CanOpenBombGrotto;}}),
  });

  areaTable[HF_SOUTHEAST_GROTTO] = Area("HF Southeast Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(HF_SOUTHEAST_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(HF_SOUTHEAST_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_OPEN_GROTTO] = Area("HF Open Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(HF_OPEN_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(HF_OPEN_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_INSIDE_FENCE_GROTTO] = Area("HF Inside Fence Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(HF_DEKU_SCRUB_GROTTO, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_COW_GROTTO] = Area("HF Cow Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(HF_GS_COW_GROTTO,           {[]{return HasFireSource && HookshotOrBoomerang;}}),
                  LocationAccess(HF_COW_GROTTO_COW,          {[]{return HasFireSource && CanPlay(EponasSong);}}),
                  LocationAccess(HF_COW_GROTTO_GOSSIP_STONE, {[]{return HasFireSource;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_NEAR_MARKET_GROTTO] = Area("HF Near Market Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(HF_NEAR_MARKET_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(HF_NEAR_MARKET_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_FAIRY_GROTTO] = Area("HF Fairy Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FreeFairies, {[]{return true;}}),
                }, {}, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_NEAR_KAK_GROTTO] = Area("HF Near Kak Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(HF_GS_NEAR_KAK_GROTTO, {[]{return HookshotOrBoomerang;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[HF_TEKTITE_GROTTO] = Area("HF Tektite Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(HF_TEKTITE_GROTTO_FREESTANDING_POH, {[]{return ProgressiveScale >= 2 || CanUse(IRON_BOOTS);}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[LAKE_HYLIA] = Area("Lake Hylia", "Lake Hylia", LAKE_HYLIA, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
                  EventAccess(&BeanPlantFairy,   {[]{return BeanPlantFairy   || (CanPlantBean(LAKE_HYLIA) && CanPlay(SongOfStorms));}}),
                  EventAccess(&ButterflyFairy,   {[]{return ButterflyFairy   || CanUse(STICKS);}}),
                  EventAccess(&BugShrub,         {[]{return BugShrub         || (IsChild && CanCutShrubs);}}),
                  EventAccess(&ScarecrowSong,    {[]{return ScarecrowSong    || (Ocarina && BothAges(LAKE_HYLIA));}}),
                }, {
                  //Locations
                  LocationAccess(LH_UNDERWATER_ITEM,        {[]{return IsChild && CanDive;}}),
                  LocationAccess(LH_SUN,                    {[]{return IsAdult && WaterTempleClear && CanUse(BOW);}}),
                  LocationAccess(LH_FREESTANDING_POH,       {[]{return IsAdult && (CanUse(SCARECROW) || CanPlantBean(LAKE_HYLIA));}}),
                  LocationAccess(LH_GS_BEAN_PATCH,          {[]{return CanPlantBugs && CanChildAttack;}}),
                  LocationAccess(LH_GS_LAB_WALL,            {[]{return IsChild && (Boomerang || (LogicLabWallGS && (Sticks || KokiriSword))) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(LH_GS_SMALL_ISLAND,        {[]{return IsChild && CanChildAttack && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(LH_GS_TREE,                {[]{return CanUse(LONGSHOT) && AtNight && CanGetNightTimeGS;},
                                                 /*Glitched*/[]{return (CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE)) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(LH_LAB_GOSSIP_STONE,       {[]{return true;}}),
                  LocationAccess(LH_GOSSIP_STONE_SOUTHEAST, {[]{return true;}}),
                  LocationAccess(LH_GOSSIP_STONE_SOUTHWEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD,          {[]{return true;}}),
                  Entrance(ZORAS_DOMAIN,          {[]{return IsChild && CanDive;}}),
                  Entrance(LH_OWL_FLIGHT,         {[]{return IsChild;}}),
                  Entrance(LH_FISHING_ISLAND,     {[]{return IsChild || CanUse(SCARECROW) || CanPlantBean(LAKE_HYLIA) || WaterTempleClear;}}),
                  Entrance(LH_LAB,                {[]{return true;}}),
                  Entrance(WATER_TEMPLE_ENTRYWAY, {[]{return CanUse(HOOKSHOT) && (CanUse(IRON_BOOTS) || ((CanUse(LONGSHOT)) && ProgressiveScale >= 2));},
                                       /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE);}}),
                  Entrance(LH_GROTTO,             {[]{return true;}}),
  });

  areaTable[LH_FISHING_ISLAND] = Area("LH Fishing Island", "Lake Hylia", LAKE_HYLIA, DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(LAKE_HYLIA,      {[]{return true;}}),
                  Entrance(LH_FISHING_HOLE, {[]{return true;}}),
  });

  areaTable[LH_OWL_FLIGHT] = Area("LH Owl Flight", "Lake Hylia", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[LH_LAB] = Area("LH Lab", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&EyedropsAccess, {[]{return EyedropsAccess || (IsAdult && (EyeballFrogAccess || (EyeballFrog && DisableTradeRevert)));}}),
                }, {
                  //Locations
                  LocationAccess(LH_LAB_DIVE,     {[]{return ProgressiveScale >= 2 || (LogicLabDiving && IronBoots && CanUse(HOOKSHOT));}}),
                  LocationAccess(LH_TRADE_FROG,   {[]{return IsAdult && EyeballFrog;}}),
                  LocationAccess(LH_GS_LAB_CRATE, {[]{return IronBoots && CanUse(HOOKSHOT);}}),
                }, {
                  //Exits
                  Entrance(LAKE_HYLIA, {[]{return true;}}),
  });

  areaTable[LH_FISHING_HOLE] = Area("LH Fishing Hole", "", NONE, DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LH_CHILD_FISHING, {[]{return IsChild;}}),
                  LocationAccess(LH_ADULT_FISHING, {[]{return IsAdult;}}),
                }, {
                  //Exits
                  Entrance(LH_FISHING_ISLAND, {[]{return true;}}),
  });

  areaTable[LH_GROTTO] = Area("LH Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LH_DEKU_SCRUB_GROTTO_LEFT,   {[]{return CanStunDeku;}}),
                  LocationAccess(LH_DEKU_SCRUB_GROTTO_RIGHT,  {[]{return CanStunDeku;}}),
                  LocationAccess(LH_DEKU_SCRUB_GROTTO_CENTER, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(LAKE_HYLIA, {[]{return true;}}),
  });

  areaTable[GERUDO_VALLEY] = Area("Gerudo Valley", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BugRock, {[]{return IsChild;}}),
                }, {
                  //Locations
                  LocationAccess(GV_GS_SMALL_BRIDGE, {[]{return CanUse(BOOMERANG) && AtNight && CanGetNightTimeGS;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD,      {[]{return true;}}),
                  Entrance(GV_UPPER_STREAM,   {[]{return true;}}),
                  Entrance(GV_CRATE_LEDGE,    {[]{return IsChild || CanUse(LONGSHOT);}}),
                  Entrance(GV_GROTTO_LEDGE,   {[]{return true;}}),
                  Entrance(GV_FORTRESS_SIDE,  {[]{return IsAdult && (CanRideEpona || CanUse(LONGSHOT) || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue);},
                                   /*Glitched*/[]{return IsAdult && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}),
  });

  areaTable[GV_UPPER_STREAM] = Area("GV Upper Stream", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
                  EventAccess(&BeanPlantFairy,   {[]{return BeanPlantFairy   || (CanPlantBean(GV_UPPER_STREAM) && CanPlay(SongOfStorms));}}),
                }, {
                  //Locations
                  LocationAccess(GV_WATERFALL_FREESTANDING_POH, {[]{return true;}}),
                  LocationAccess(GV_GS_BEAN_PATCH,              {[]{return CanPlantBugs && CanChildAttack;}}),
                  LocationAccess(GV_COW,                        {[]{return IsChild && CanPlay(EponasSong);}}),
                  LocationAccess(GV_GOSSIP_STONE,               {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(GV_LOWER_STREAM, {[]{return true;}}),
  });

  areaTable[GV_LOWER_STREAM] = Area("GV Lower Stream", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(LAKE_HYLIA, {[]{return true;}}),
  });

  areaTable[GV_GROTTO_LEDGE] = Area("GV Grotto Ledge", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GV_LOWER_STREAM,   {[]{return true;}}),
                  Entrance(GV_OCTOROK_GROTTO, {[]{return CanUse(SILVER_GAUNTLETS);}}),
                  Entrance(GV_CRATE_LEDGE,    {[]{return CanUse(LONGSHOT);}}),
  });

  areaTable[GV_CRATE_LEDGE] = Area("GV Crate Ledge", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GV_CRATE_FREESTANDING_POH, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(GV_LOWER_STREAM, {[]{return true;}}),
  });

  areaTable[GV_FORTRESS_SIDE] = Area("GV Fortress Side", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BrokenSwordAccess, {[]{return IsAdult && (PoachersSawAccess || PoachersSaw);}}),
                }, {
                  //Locations
                  LocationAccess(GV_CHEST,          {[]{return CanUse(MEGATON_HAMMER) || (LogicGVHammerChest && IsAdult);}}),
                  LocationAccess(GV_TRADE_SAW,      {[]{return IsAdult && PoachersSaw;}}),
                  LocationAccess(GV_GS_BEHIND_TENT, {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(GV_GS_PILLAR,      {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                }, {
                  //Exits
                  Entrance(GERUDO_FORTRESS,   {[]{return true;}}),
                  Entrance(GV_UPPER_STREAM,   {[]{return true;}}),
                  Entrance(GERUDO_VALLEY,     {[]{return IsChild || CanRideEpona || CanUse(LONGSHOT) || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue;}}),
                  Entrance(GV_CARPENTER_TENT, {[]{return IsAdult;}}),
                  Entrance(GV_STORMS_GROTTO,  {[]{return IsAdult && CanOpenStormGrotto;}}),
  });

  areaTable[GV_CARPENTER_TENT] = Area("GV Carpenter Tent", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GV_FORTRESS_SIDE, {[]{return true;}}),
  });

  areaTable[GV_OCTOROK_GROTTO] = Area("GV Octorok Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GV_GROTTO_LEDGE, {[]{return true;}}),
  });

  areaTable[GV_STORMS_GROTTO] = Area("GV Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GV_DEKU_SCRUB_GROTTO_REAR,  {[]{return CanStunDeku;}}),
                  LocationAccess(GV_DEKU_SCRUB_GROTTO_FRONT, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(GV_FORTRESS_SIDE, {[]{return true;}}),
  });

  areaTable[GERUDO_FORTRESS] = Area("Gerudo Fortress", "Gerudo Fortress", GERUDO_FORTRESS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&CarpenterRescue, {[]{return CanFinishGerudoFortress;}}),
                  EventAccess(&GF_GateOpen,     {[]{return IsAdult && GerudoToken;}}),
                  EventAccess(&GtG_GateOpen,    {[]{return GtG_GateOpen || (IsAdult && GerudoToken);}}),
                }, {
                  //Locations
                  LocationAccess(GF_CHEST,              {[]{return CanUse(HOVER_BOOTS) || CanUse(SCARECROW) || CanUse(LONGSHOT);}}),
                  LocationAccess(GF_HBA_1000_POINTS,    {[]{return GerudoToken && CanRideEpona && Bow && AtDay;}}),
                  LocationAccess(GF_HBA_1500_POINTS,    {[]{return GerudoToken && CanRideEpona && Bow && AtDay;}}),
                  LocationAccess(GF_NORTH_F1_CARPENTER, {[]{return  IsAdult || KokiriSword;}}),
                  LocationAccess(GF_NORTH_F2_CARPENTER, {[]{return (IsAdult || KokiriSword) && (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || LogicGerudoKitchen);}}),
                  LocationAccess(GF_SOUTH_F1_CARPENTER, {[]{return  IsAdult || KokiriSword;}}),
                  LocationAccess(GF_SOUTH_F2_CARPENTER, {[]{return  IsAdult || KokiriSword;}}),
                  LocationAccess(GF_GERUDO_TOKEN,       {[]{return CanFinishGerudoFortress;}}),
                  LocationAccess(GF_GS_ARCHERY_RANGE,   {[]{return CanUse(HOOKSHOT) && GerudoToken && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(GF_GS_TOP_FLOOR,       {[]{return IsAdult && AtNight && (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || LogicGerudoKitchen) && CanGetNightTimeGS;}}),
                }, {
                  //Exits
                  Entrance(GV_FORTRESS_SIDE,                 {[]{return true;}}),
                  Entrance(GF_OUTSIDE_GATE,                  {[]{return GF_GateOpen;}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_ENTRYWAY, {[]{return GtG_GateOpen && (IsAdult || ShuffleDungeonEntrances);}}),
                  Entrance(GF_STORMS_GROTTO,                 {[]{return IsAdult && CanOpenStormGrotto;}}),
  });

  areaTable[GF_OUTSIDE_GATE] = Area("GF Outside Gate", "Gerudo Fortress", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GF_GateOpen, {[]{return IsAdult && GerudoToken && (ShuffleGerudoToken || ShuffleOverworldEntrances /*|| ShuffleSpecialIndoorEntrances*/);}}),
                }, {}, {
                  //Exits
                  Entrance(GERUDO_FORTRESS,         {[]{return (IsAdult && (Hookshot || !ShuffleOverworldEntrances)) || GF_GateOpen;}}),
                  Entrance(WASTELAND_NEAR_FORTRESS, {[]{return true;}}),
  });

  areaTable[GF_STORMS_GROTTO] = Area("GF Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FreeFairies, {[]{return true;}}),
                }, {}, {
                  //Exits
                  Entrance(GERUDO_FORTRESS, {[]{return true;}}),
  });

  areaTable[WASTELAND_NEAR_FORTRESS] = Area("Wasteland Near Fortress", "Haunted Wasteland", HAUNTED_WASTELAND, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GF_OUTSIDE_GATE,   {[]{return true;}}),
                  Entrance(HAUNTED_WASTELAND, {[]{return CanUse(HOVER_BOOTS) || CanUse(LONGSHOT);}}),
  });

  areaTable[HAUNTED_WASTELAND] = Area("Haunted Wasteland", "Haunted Wasteland", HAUNTED_WASTELAND, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}),
                  EventAccess(&NutPot,   {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(WASTELAND_CHEST,            {[]{return HasFireSource;}}),
                  LocationAccess(WASTELAND_BOMBCHU_SALESMAN, {[]{return AdultsWallet && (IsAdult || Sticks || KokiriSword);}}),
                  LocationAccess(WASTELAND_GS,               {[]{return HookshotOrBoomerang;}}),
                }, {
                  //Exits
                  Entrance(WASTELAND_NEAR_COLOSSUS, {[]{return LogicLensWasteland || CanUse(LENS_OF_TRUTH);}}),
                  Entrance(WASTELAND_NEAR_FORTRESS, {[]{return CanUse(HOVER_BOOTS) || CanUse(LONGSHOT);}}),
  });

  areaTable[WASTELAND_NEAR_COLOSSUS] = Area("Wasteland Near Colossus", "Haunted Wasteland", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DESERT_COLOSSUS,   {[]{return true;}}),
                  Entrance(HAUNTED_WASTELAND, {[]{return LogicReverseWasteland || false;}}),
  });

  areaTable[DESERT_COLOSSUS] = Area("Desert Colossus", "Desert Colossus", DESERT_COLOSSUS, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPond, {[]{return FairyPond || CanPlay(SongOfStorms);}}),
                  EventAccess(&BugRock,   {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(COLOSSUS_FREESTANDING_POH, {[]{return IsAdult && CanPlantBean(DESERT_COLOSSUS);}}),
                  LocationAccess(SHEIK_AT_COLOSSUS,         {[]{return true;}}),
                  LocationAccess(COLOSSUS_GS_BEAN_PATCH,    {[]{return CanPlantBugs && CanChildAttack;}}),
                  LocationAccess(COLOSSUS_GS_TREE,          {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(COLOSSUS_GS_HILL,          {[]{return IsAdult && AtNight && (CanPlantBean(DESERT_COLOSSUS) || CanUse(LONGSHOT) || (LogicColossusGS && CanUse(HOOKSHOT))) && CanGetNightTimeGS;}}),
                  LocationAccess(COLOSSUS_GOSSIP_STONE,     {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(COLOSSUS_GREAT_FAIRY_FOUNTAIN, {[]{return HasExplosives;}}),
                  Entrance(SPIRIT_TEMPLE_ENTRYWAY,        {[]{return true;}}),
                  Entrance(WASTELAND_NEAR_COLOSSUS,       {[]{return true;}}),
                  Entrance(COLOSSUS_GROTTO,               {[]{return CanUse(SILVER_GAUNTLETS);}}),
  });

  areaTable[COLOSSUS_GREAT_FAIRY_FOUNTAIN] = Area("Colossus Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(COLOSSUS_GREAT_FAIRY_REWARD, {[]{return CanPlay(ZeldasLullaby);}}),
                }, {
                  //Exits
                  Entrance(DESERT_COLOSSUS, {[]{return true;}}),
  });

  areaTable[COLOSSUS_GROTTO] = Area("Colossus Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(COLOSSUS_DEKU_SCRUB_GROTTO_REAR,  {[]{return CanStunDeku;}}),
                  LocationAccess(COLOSSUS_DEKU_SCRUB_GROTTO_FRONT, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(DESERT_COLOSSUS, {[]{return true;}}),
  });

  areaTable[MARKET_ENTRANCE] = Area("Market Entrance", "Market Entrance", THE_MARKET, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(HYRULE_FIELD,       {[]{return IsAdult || AtDay;}}),
                  Entrance(THE_MARKET,         {[]{return true;}}),
                  Entrance(MARKET_GUARD_HOUSE, {[]{return true;}}),
  });

  areaTable[THE_MARKET] = Area("Market", "Market", THE_MARKET, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(MARKET_ENTRANCE,            {[]{return true;}}),
                  Entrance(TOT_ENTRANCE,               {[]{return true;}}),
                  Entrance(CASTLE_GROUNDS,             {[]{return true;}}),
                  Entrance(MARKET_BAZAAR,              {[]{return IsChild && AtDay;}}),
                  Entrance(MARKET_MASK_SHOP,           {[]{return IsChild && AtDay;}}),
                  Entrance(MARKET_SHOOTING_GALLERY,    {[]{return IsChild && AtDay;}}),
                  Entrance(MARKET_BOMBCHU_BOWLING,     {[]{return IsChild;}}),
                  Entrance(MARKET_TREASURE_CHEST_GAME, {[]{return IsChild && AtNight;}}),
                  Entrance(MARKET_POTION_SHOP,         {[]{return IsChild && AtDay;}}),
                  Entrance(MARKET_BACK_ALLEY,          {[]{return IsChild;}}),
  });

  areaTable[MARKET_BACK_ALLEY] = Area("Market Back Alley", "Market", THE_MARKET, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(THE_MARKET,                 {[]{return true;}}),
                  Entrance(MARKET_BOMBCHU_SHOP,        {[]{return AtNight;}}),
                  Entrance(MARKET_DOG_LADY_HOUSE,      {[]{return true;}}),
                  Entrance(MARKET_MAN_IN_GREEN_HOUSE,  {[]{return AtNight;}}),
  });

  areaTable[TOT_ENTRANCE] = Area("ToT Entrance", "ToT Entrance", THE_MARKET, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}}),
                }, {
                  //Locations
                  LocationAccess(TOT_GOSSIP_STONE_LEFT,         {[]{return true;}}),
                  LocationAccess(TOT_GOSSIP_STONE_LEFT_CENTER,  {[]{return true;}}),
                  LocationAccess(TOT_GOSSIP_STONE_RIGHT_CENTER, {[]{return true;}}),
                  LocationAccess(TOT_GOSSIP_STONE_RIGHT,        {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(THE_MARKET,  {[]{return true;}}),
                  Entrance(TEMPLE_OF_TIME, {[]{return true;}}),
  });

  areaTable[TEMPLE_OF_TIME] = Area("Temple of Time", "", TEMPLE_OF_TIME, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(TOT_LIGHT_ARROWS_CUTSCENE, {[]{return IsAdult && CanTriggerLACS;}}),
                }, {
                  //Exits
                  Entrance(TOT_ENTRANCE,            {[]{return true;}}),
                  Entrance(TOT_BEYOND_DOOR_OF_TIME, {[]{return OpenDoorOfTime.Is(OPENDOOROFTIME_OPEN) || (CanPlay(SongOfTime) && (OpenDoorOfTime.Is(OPENDOOROFTIME_CLOSED) || (HasAllStones && OcarinaOfTime)));}}),
  });

  areaTable[TOT_BEYOND_DOOR_OF_TIME] = Area("Beyond Door of Time", "", TEMPLE_OF_TIME, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventAccess(&TimeTravel, {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(SHEIK_AT_TEMPLE, {[]{return ForestMedallion && IsAdult;}}),
                }, {
                  //Exits
                  Entrance(TEMPLE_OF_TIME, {[]{return true;}}),
  });

  areaTable[CASTLE_GROUNDS] = Area("Castle Grounds", "Castle Grounds", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(THE_MARKET,            {[]{return true;}}),
                  Entrance(HYRULE_CASTLE_GROUNDS, {[]{return IsChild;}}),
                  Entrance(GANONS_CASTLE_GROUNDS, {[]{return IsAdult;}}),
  });

  areaTable[HYRULE_CASTLE_GROUNDS] = Area("Hyrule Castle Grounds", "Castle Grounds", HYRULE_CASTLE, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
                  EventAccess(&ButterflyFairy,   {[]{return ButterflyFairy   || CanUse(STICKS);}}),
                  EventAccess(&BugRock,          {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(HC_MALON_EGG,              {[]{return true;}}),
                  LocationAccess(HC_GS_TREE,                {[]{return CanChildAttack;}}),
                  LocationAccess(HC_MALON_GOSSIP_STONE,     {[]{return true;}}),
                  LocationAccess(HC_ROCK_WALL_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(CASTLE_GROUNDS,          {[]{return true;}}),
                  Entrance(HC_GARDEN,               {[]{return WeirdEgg || !ShuffleWeirdEgg;}}),
                  Entrance(HC_GREAT_FAIRY_FOUNTAIN, {[]{return HasExplosives;}}),
                  Entrance(HC_STORMS_GROTTO,        {[]{return CanOpenStormGrotto;}}),
  });

  areaTable[HC_GARDEN] = Area("HC Garden", "Castle Grounds", HYRULE_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                }, {
                  //Locations
                  LocationAccess(HC_ZELDAS_LETTER, {[]{return true;}}),
                  LocationAccess(SONG_FROM_IMPA,   {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_CASTLE_GROUNDS, {[]{return true;}}),
  });

  areaTable[HC_GREAT_FAIRY_FOUNTAIN] = Area("HC Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(HC_GREAT_FAIRY_REWARD, {[]{return CanPlay(ZeldasLullaby);}}),
                }, {
                  //Exits
                  Entrance(CASTLE_GROUNDS, {[]{return true;}}),
  });

  areaTable[HC_STORMS_GROTTO] = Area("HC Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot,           {[]{return NutPot           || CanBlastOrSmash;}}),
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || (CanBlastOrSmash && CanSummonGossipFairy);}}),
                  EventAccess(&WanderingBugs,    {[]{return WanderingBugs    || CanBlastOrSmash;}}),
                }, {
                  //Locations
                  LocationAccess(HC_GS_STORMS_GROTTO,           {[]{return CanBlastOrSmash && HookshotOrBoomerang;}}),
                  LocationAccess(HC_STORMS_GROTTO_GOSSIP_STONE, {[]{return CanBlastOrSmash;}}),
                }, {
                  //Exits
                  Entrance(CASTLE_GROUNDS, {[]{return true;}}),
  });

  areaTable[GANONS_CASTLE_GROUNDS] = Area("Ganon's Castle Grounds", "Castle Grounds", OUTSIDE_GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations                                   //the terrain was lowered such that you can't get this GS with a simple sword slash
                  LocationAccess(OGC_GS, {[]{return HasExplosives || (IsAdult && (LogicOutsideGanonsGS || Bow || Hookshot || CanUse(DINS_FIRE)));}}),
                }, {
                  //Exits
                  Entrance(CASTLE_GROUNDS,           {[]{return AtNight;}}),
                  Entrance(OGC_GREAT_FAIRY_FOUNTAIN, {[]{return CanUse(GOLDEN_GAUNTLETS) && AtNight;}}),
                  Entrance(GANONS_CASTLE_ENTRYWAY,   {[]{return CanBuildRainbowBridge;}}),

  });

  areaTable[OGC_GREAT_FAIRY_FOUNTAIN] = Area("OGC Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(OGC_GREAT_FAIRY_REWARD, {[]{return CanPlay(ZeldasLullaby);}}),
                }, {
                  //Exits
                  Entrance(CASTLE_GROUNDS, {[]{return true;}}),
  });

  areaTable[MARKET_GUARD_HOUSE] = Area("Market Guard House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_10_BIG_POES,    {[]{return IsAdult && BigPoeKill;}}),
                  LocationAccess(MARKET_GS_GUARD_HOUSE, {[]{return IsChild;}}),
                }, {
                  //Exits
                  Entrance(MARKET_ENTRANCE, {[]{return true;}}),
  });

  areaTable[MARKET_BAZAAR] = Area("Market Bazaar", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_BAZAAR_ITEM_1, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_2, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_3, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_4, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_5, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_6, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_7, {[]{return true;}}),
                  LocationAccess(MARKET_BAZAAR_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(THE_MARKET, {[]{return true;}}),
  });

  areaTable[MARKET_MASK_SHOP] = Area("Market Mask Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&SkullMask,   {[]{return SkullMask   || (ZeldasLetter && (CompleteMaskQuest ||  ChildCanAccess(KAKARIKO_VILLAGE)));}}),
                  EventAccess(&MaskOfTruth, {[]{return MaskOfTruth || (SkullMask && (CompleteMaskQuest || (ChildCanAccess(THE_LOST_WOODS) && CanPlay(SariasSong) && AreaTable(THE_GRAVEYARD)->childDay && ChildCanAccess(HYRULE_FIELD) && HasAllStones)));}}),
                }, {}, {
                  //Exits
                  Entrance(THE_MARKET, {[]{return true;}}),
  });

  areaTable[MARKET_SHOOTING_GALLERY] = Area("Market Shooting Gallery", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_SHOOTING_GALLERY_REWARD, {[]{return IsChild;}}),
                }, {
                  //Exits
                  Entrance(THE_MARKET, {[]{return true;}}),
  });

  areaTable[MARKET_BOMBCHU_BOWLING] = Area("Market Bombchu Bowling", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,  {[]{return CanPlayBowling;}}),
                  LocationAccess(MARKET_BOMBCHU_BOWLING_SECOND_PRIZE, {[]{return CanPlayBowling;}}),
                  LocationAccess(MARKET_BOMBCHU_BOWLING_BOMBCHUS,     {[]{return CanPlayBowling;}}),
                }, {
                  //Exits
                  Entrance(THE_MARKET, {[]{return true;}}),
  });

  areaTable[MARKET_POTION_SHOP] = Area("Market Potion Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_POTION_SHOP_ITEM_1, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_2, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_3, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_4, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_5, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_6, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_7, {[]{return true;}}),
                  LocationAccess(MARKET_POTION_SHOP_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(THE_MARKET, {[]{return true;}}),
  });

  areaTable[MARKET_TREASURE_CHEST_GAME] = Area("Market Treasure Chest Game", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_TREASURE_CHEST_GAME_REWARD, {[]{return (CanUse(LENS_OF_TRUTH) && !ShuffleChestMinigame) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS) && SmallKeys(TreasureGameKeys, 6)) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK) && SmallKeys(TreasureGameKeys, 1));}}),
                  LocationAccess(MARKET_TREASURE_CHEST_GAME_ITEM_1, {[]{return (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS) && SmallKeys(TreasureGameKeys, 1)) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK) && SmallKeys(TreasureGameKeys, 1)) || (CanUse(LENS_OF_TRUTH) && !ShuffleChestMinigame);}}),
                  LocationAccess(MARKET_TREASURE_CHEST_GAME_ITEM_2, {[]{return (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS) && SmallKeys(TreasureGameKeys, 2)) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK) && SmallKeys(TreasureGameKeys, 1)) || (CanUse(LENS_OF_TRUTH) && !ShuffleChestMinigame);}}),
                  LocationAccess(MARKET_TREASURE_CHEST_GAME_ITEM_3, {[]{return (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS) && SmallKeys(TreasureGameKeys, 3)) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK) && SmallKeys(TreasureGameKeys, 1)) || (CanUse(LENS_OF_TRUTH) && !ShuffleChestMinigame);}}),
                  LocationAccess(MARKET_TREASURE_CHEST_GAME_ITEM_4, {[]{return (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS) && SmallKeys(TreasureGameKeys, 4)) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK) && SmallKeys(TreasureGameKeys, 1)) || (CanUse(LENS_OF_TRUTH) && !ShuffleChestMinigame);}}),
                  LocationAccess(MARKET_TREASURE_CHEST_GAME_ITEM_5, {[]{return (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS) && SmallKeys(TreasureGameKeys, 5)) || (ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK) && SmallKeys(TreasureGameKeys, 1)) || (CanUse(LENS_OF_TRUTH) && !ShuffleChestMinigame);}}),
                }, {
                  //Exits
                  Entrance(THE_MARKET, {[]{return true;}}),
  });

  areaTable[MARKET_BOMBCHU_SHOP] = Area("Market Bombchu Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_1, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_2, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_3, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_4, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_5, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_6, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_7, {[]{return true;}}),
                  LocationAccess(MARKET_BOMBCHU_SHOP_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(MARKET_BACK_ALLEY, {[]{return true;}}),
  });

  areaTable[MARKET_DOG_LADY_HOUSE] = Area("Market Dog Lady House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(MARKET_LOST_DOG, {[]{return AtNight;}}),
                }, {
                  //Exits
                  Entrance(MARKET_BACK_ALLEY, {[]{return true;}}),
  });

  areaTable[MARKET_MAN_IN_GREEN_HOUSE] = Area("Market Man in Green House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                }, {
                  //Exits
                  Entrance(MARKET_BACK_ALLEY, {[]{return true;}}),
  });

  areaTable[KAKARIKO_VILLAGE] = Area("Kakariko Village", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&CojiroAccess,            {[]{return CojiroAccess || (IsAdult && WakeUpAdultTalon);}}),
                  EventAccess(&BugRock,                 {[]{return true;}}),
                  EventAccess(&KakarikoVillageGateOpen, {[]{return KakarikoVillageGateOpen || (IsChild && (ZeldasLetter || OpenKakariko.Is(OPENKAKARIKO_OPEN)));}}),
                }, {
                  //Locations
                  LocationAccess(SHEIK_IN_KAKARIKO,               {[]{return IsAdult && ForestMedallion && FireMedallion && WaterMedallion;}}),
                  LocationAccess(KAK_ANJU_AS_CHILD,               {[]{return IsChild && AtDay;}}),
                  LocationAccess(KAK_ANJU_AS_ADULT,               {[]{return IsAdult && AtDay;}}),
                  LocationAccess(KAK_TRADE_POCKET_CUCCO,          {[]{return IsAdult && AtDay && PocketEgg && WakeUpAdultTalon;}}),
                  LocationAccess(KAK_GS_HOUSE_UNDER_CONSTRUCTION, {[]{return IsChild && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(KAK_GS_SKULLTULA_HOUSE,          {[]{return IsChild && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(KAK_GS_GUARDS_HOUSE,             {[]{return IsChild && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(KAK_GS_TREE,                     {[]{return IsChild && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(KAK_GS_WATCHTOWER,               {[]{return IsChild && (Slingshot || HasBombchus) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(KAK_GS_ABOVE_IMPAS_HOUSE,        {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD,                {[]{return true;}}),
                  Entrance(KAK_CARPENTER_BOSS_HOUSE,    {[]{return true;}}),
                  Entrance(KAK_HOUSE_OF_SKULLTULA,      {[]{return true;}}),
                  Entrance(KAK_IMPAS_HOUSE,             {[]{return true;}}),
                  Entrance(KAK_WINDMILL,                {[]{return true;}}),
                  Entrance(KAK_BAZAAR,                  {[]{return IsAdult && AtDay;},
                                             /*Glitched*/[]{return CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE);}}),
                  Entrance(KAK_SHOOTING_GALLERY,        {[]{return IsAdult && AtDay;}}),
                  Entrance(BOTTOM_OF_THE_WELL_ENTRYWAY, {[]{return DrainWell && (IsChild || ShuffleDungeonEntrances.IsNot(SHUFFLEDUNGEONS_OFF));}}),
                  Entrance(KAK_POTION_SHOP_FRONT,       {[]{return AtDay || IsChild;}}),
                  Entrance(KAK_REDEAD_GROTTO,           {[]{return CanOpenBombGrotto;}}),
                  Entrance(KAK_IMPAS_LEDGE,             {[]{return (IsChild && AtDay) || CanUse(HOOKSHOT);}}),
                  Entrance(KAK_ROOFTOP,                 {[]{return CanUse(HOOKSHOT) || (LogicManOnRoof && (IsAdult || AtDay || Slingshot || HasBombchus));}}),
                  Entrance(THE_GRAVEYARD,               {[]{return true;}}),
                  Entrance(KAK_BEHIND_GATE,             {[]{return IsAdult || (KakarikoVillageGateOpen);}}),
  });

  areaTable[KAK_IMPAS_LEDGE] = Area("Kak Impas Ledge", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KAK_IMPAS_HOUSE_BACK, {[]{return true;}}),
                  Entrance(KAKARIKO_VILLAGE,     {[]{return true;}}),
  });

  areaTable[KAK_ROOFTOP] = Area("Kak Rooftop", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_MAN_ON_ROOF, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KAK_BACKYARD, {[]{return true;}}),
  });

  areaTable[KAK_BACKYARD] = Area("Kak Backyard", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE,          {[]{return true;}}),
                  Entrance(KAK_OPEN_GROTTO,           {[]{return true;}}),
                  Entrance(KAK_ODD_POULTICE_BUILDING, {[]{return IsAdult;}}),
                  Entrance(KAK_POTION_SHOP_BACK,      {[]{return IsAdult && AtDay;}}),
  });

  areaTable[KAK_CARPENTER_BOSS_HOUSE] = Area("Kak Carpenter Boss House", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&WakeUpAdultTalon, {[]{return WakeUpAdultTalon || (IsAdult && PocketEgg);}}),
                }, {}, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE, {[]{return true;}}),
  });

  areaTable[KAK_HOUSE_OF_SKULLTULA] = Area("Kak House of Skulltula", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_10_GOLD_SKULLTULA_REWARD, {[]{return GoldSkulltulaTokens >= 10;}}),
                  LocationAccess(KAK_20_GOLD_SKULLTULA_REWARD, {[]{return GoldSkulltulaTokens >= 20;}}),
                  LocationAccess(KAK_30_GOLD_SKULLTULA_REWARD, {[]{return GoldSkulltulaTokens >= 30;}}),
                  LocationAccess(KAK_40_GOLD_SKULLTULA_REWARD, {[]{return GoldSkulltulaTokens >= 40;}}),
                  LocationAccess(KAK_50_GOLD_SKULLTULA_REWARD, {[]{return GoldSkulltulaTokens >= 50;}}),
                }, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE, {[]{return true;}}),
  });

  areaTable[KAK_IMPAS_HOUSE] = Area("Kak Impas House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KAK_IMPAS_HOUSE_NEAR_COW, {[]{return true;}}),
                  Entrance(KAKARIKO_VILLAGE,         {[]{return true;}}),
  });

  areaTable[KAK_IMPAS_HOUSE_BACK] = Area("Kak Impas House Back", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_IMPAS_HOUSE_FREESTANDING_POH, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KAK_IMPAS_LEDGE,          {[]{return true;}}),
                  Entrance(KAK_IMPAS_HOUSE_NEAR_COW, {[]{return true;}}),
  });

  areaTable[KAK_IMPAS_HOUSE_NEAR_COW] = Area("Kak Impas House Near Cow", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_IMPAS_HOUSE_COW, {[]{return CanPlay(EponasSong);}}),
  }, {});

  areaTable[KAK_WINDMILL] = Area("Kak Windmill", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DrainWell, {[]{return DrainWell || (IsChild && CanPlay(SongOfStorms));}}),
                }, {
                  //Locations
                  LocationAccess(KAK_WINDMILL_FREESTANDING_POH, {[]{return CanUse(BOOMERANG) || DampesWindmillAccess;}}),
                  LocationAccess(SONG_FROM_WINDMILL,            {[]{return IsAdult && Ocarina;}}),
                }, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE, {[]{return true;}}),
  });

  areaTable[KAK_BAZAAR] = Area("Kak Bazaar", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_BAZAAR_ITEM_1, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_2, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_3, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_4, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_5, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_6, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_7, {[]{return true;}}),
                  LocationAccess(KAK_BAZAAR_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE, {[]{return true;}}),
  });

  areaTable[KAK_SHOOTING_GALLERY] = Area("Kak Shooting Gallery", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_SHOOTING_GALLERY_REWARD, {[]{return IsAdult && Bow;}}),
                }, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE, {[]{return true;}}),
  });

  areaTable[KAK_POTION_SHOP_FRONT] = Area("Kak Potion Shop Front", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_POTION_SHOP_ITEM_1, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_2, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_3, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_4, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_5, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_6, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_7, {[]{return IsAdult;}}),
                  LocationAccess(KAK_POTION_SHOP_ITEM_8, {[]{return IsAdult;}}),
                }, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE,     {[]{return true;}}),
                  Entrance(KAK_POTION_SHOP_BACK, {[]{return IsAdult;}}),
  });

  areaTable[KAK_POTION_SHOP_BACK] = Area("Kak Potion Shop Back", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KAK_BACKYARD,          {[]{return IsAdult;}}),
                  Entrance(KAK_POTION_SHOP_FRONT, {[]{return true;}}),
  });

  areaTable[KAK_ODD_POULTICE_BUILDING] = Area("Kak Granny's Potion Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&OddPoulticeAccess, {[]{return OddPoulticeAccess || (IsAdult && (OddMushroomAccess || (OddMushroom && DisableTradeRevert)));}}),
                }, {
                  LocationAccess(KAK_TRADE_ODD_MUSHROOM, {[]{return IsAdult && OddMushroom;}}),
                }, {
                  //Exits
                  Entrance(KAK_BACKYARD, {[]{return true;}}),
  });

  areaTable[KAK_REDEAD_GROTTO] = Area("Kak Redead Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(KAK_REDEAD_GROTTO_CHEST, {[]{return IsAdult || (Sticks || KokiriSword || CanUse(DINS_FIRE));}}),
                }, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE, {[]{return true;}}),
  });

  areaTable[KAK_OPEN_GROTTO] = Area("Kak Open Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(KAK_OPEN_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(KAK_OPEN_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(KAK_BACKYARD, {[]{return true;}}),
  });

  areaTable[THE_GRAVEYARD] = Area("The Graveyard", "The Graveyard", THE_GRAVEYARD, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ButterflyFairy, {[]{return ButterflyFairy || (CanUse(STICKS) && AtDay);}}),
                  EventAccess(&BeanPlantFairy, {[]{return BeanPlantFairy || (CanPlantBean(THE_GRAVEYARD) && CanPlay(SongOfStorms));}}),
                  EventAccess(&BugRock,        {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(GRAVEYARD_FREESTANDING_POH,        {[]{return (IsAdult && (CanPlantBean(THE_GRAVEYARD) || CanUse(LONGSHOT))) || (LogicGraveyardPoH && CanUse(BOOMERANG));}}),
                  LocationAccess(GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR, {[]{return IsChild && AtNight;}}), //This needs to change
                  LocationAccess(GRAVEYARD_GS_WALL,                 {[]{return CanUse(BOOMERANG) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(GRAVEYARD_GS_BEAN_PATCH,           {[]{return CanPlantBugs && CanChildAttack;}}),
                }, {
                  //Exits
                  Entrance(GRAVEYARD_SHIELD_GRAVE,       {[]{return IsAdult || AtNight;}}),
                  Entrance(GRAVEYARD_COMPOSERS_GRAVE,    {[]{return CanPlay(ZeldasLullaby);}}),
                  Entrance(GRAVEYARD_HEART_PIECE_GRAVE,  {[]{return IsAdult || AtNight;}}),
                  Entrance(GRAVEYARD_DAMPES_GRAVE,       {[]{return IsAdult;}}),
                  Entrance(GRAVEYARD_DAMPES_HOUSE,       {[]{return IsAdult || AtDampeTime;}}), //TODO: This needs to be handled
                  Entrance(KAKARIKO_VILLAGE,             {[]{return true;}}),
                  Entrance(GRAVEYARD_WARP_PAD_REGION,    {[]{return false;},
                                              /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE);}}),
  });

  areaTable[GRAVEYARD_SHIELD_GRAVE] = Area("Graveyard Shield Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GRAVEYARD_SHIELD_GRAVE_CHEST, {[]{return true;}}),
                  //Free Fairies
                }, {
                  //Exits
                  Entrance(THE_GRAVEYARD, {[]{return true;}}),
  });

  areaTable[GRAVEYARD_HEART_PIECE_GRAVE] = Area("Graveyard Heart Piece Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GRAVEYARD_HEART_PIECE_GRAVE_CHEST, {[]{return CanPlay(SunsSong);}}),
                }, {
                  //Exits
                  Entrance(THE_GRAVEYARD, {[]{return true;}}),
  });

  areaTable[GRAVEYARD_COMPOSERS_GRAVE] = Area("Graveyard Composers Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GRAVEYARD_COMPOSERS_GRAVE_CHEST, {[]{return HasFireSource;}}),
                  LocationAccess(SONG_FROM_COMPOSERS_GRAVE,       {[]{return IsAdult || (Slingshot || Boomerang || Sticks || HasExplosives || KokiriSword);}}),
                }, {
                  //Exits
                  Entrance(THE_GRAVEYARD, {[]{return true;}}),
  });

  areaTable[GRAVEYARD_DAMPES_GRAVE] = Area("Graveyard Dampes Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot,               {[]{return true;}}),
                  EventAccess(&DampesWindmillAccess, {[]{return DampesWindmillAccess || (IsAdult && CanPlay(SongOfTime));}}),
                }, {
                  //Locations
                  LocationAccess(GRAVEYARD_HOOKSHOT_CHEST,              {[]{return true;}}),
                  LocationAccess(GRAVEYARD_DAMPE_RACE_FREESTANDING_POH, {[]{return IsAdult || LogicChildDampeRacePoH;}}),
                }, {
                  //Exits
                  Entrance(THE_GRAVEYARD, {[]{return true;}}),
                  Entrance(KAK_WINDMILL,  {[]{return IsAdult && CanPlay(SongOfTime);}}),
  });

  areaTable[GRAVEYARD_DAMPES_HOUSE] = Area("Graveyard Dampes House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(THE_GRAVEYARD, {[]{return true;}}),
  });

  areaTable[GRAVEYARD_WARP_PAD_REGION] = Area("Graveyard Warp Pad Region", "Graveyard", THE_GRAVEYARD, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}}),
                }, {
                  //Locations
                  LocationAccess(GRAVEYARD_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(THE_GRAVEYARD,             {[]{return true;}}),
                  Entrance(SHADOW_TEMPLE_ENTRYWAY,    {[]{return CanUse(DINS_FIRE) || (LogicShadowFireArrowEntry && CanUse(FIRE_ARROWS));},
                                           /*Glitched*/[]{return (CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE)) && CanTakeDamage;}}),
  });

  areaTable[KAK_BEHIND_GATE] = Area("Kak Behind Gate", "Kakariko Village", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KAKARIKO_VILLAGE,     {[]{return IsAdult || LogicVisibleCollision || KakarikoVillageGateOpen || OpenKakariko.Is(OPENKAKARIKO_OPEN);}}),
                  Entrance(DEATH_MOUNTAIN_TRAIL, {[]{return true;}}),
  });

  areaTable[DEATH_MOUNTAIN_TRAIL] = Area("Death Mountain", "Death Mountain", DEATH_MOUNTAIN_TRAIL, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BeanPlantFairy, {[]{return BeanPlantFairy || (CanPlantBean(DEATH_MOUNTAIN_TRAIL) && CanPlay(SongOfStorms) && (HasExplosives || GoronBracelet));}}),
                }, {
                  //Locations
                  LocationAccess(DMT_CHEST,                    {[]{return CanBlastOrSmash || (LogicDMTBombable && IsChild && GoronBracelet);}}),
                  LocationAccess(DMT_FREESTANDING_POH,         {[]{return CanTakeDamage || CanUse(HOVER_BOOTS) || (IsAdult && CanPlantBean(DEATH_MOUNTAIN_TRAIL) && (HasExplosives || GoronBracelet));}}),
                  LocationAccess(DMT_GS_BEAN_PATCH,            {[]{return CanPlantBugs && (HasExplosives || GoronBracelet || (LogicDMTSoilGS && CanUse(BOOMERANG)));}}),
                  LocationAccess(DMT_GS_NEAR_KAK,              {[]{return CanBlastOrSmash;}}),
                  LocationAccess(DMT_GS_ABOVE_DODONGOS_CAVERN, {[]{return IsAdult && AtNight && CanUse(MEGATON_HAMMER) && CanGetNightTimeGS;}}),
                }, {
                  //Exits
                  Entrance(KAK_BEHIND_GATE,          {[]{return true;}}),
                  Entrance(GORON_CITY,               {[]{return true;}}),
                  Entrance(DEATH_MOUNTAIN_SUMMIT,    {[]{return Here(DEATH_MOUNTAIN_TRAIL, []{return CanBlastOrSmash;}) || (IsAdult && (CanPlantBean(DEATH_MOUNTAIN_TRAIL) && GoronBracelet));}}),
                  Entrance(DODONGOS_CAVERN_ENTRYWAY, {[]{return HasExplosives || GoronBracelet || IsAdult;}}),
                  Entrance(DMT_STORMS_GROTTO,        {[]{return CanOpenStormGrotto;}}),
  });

  areaTable[DEATH_MOUNTAIN_SUMMIT] = Area("Death Mountain Summit", "Death Mountain", DEATH_MOUNTAIN_TRAIL, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&PrescriptionAccess, {[]{return PrescriptionAccess || (IsAdult && (BrokenSwordAccess || BrokenSword));}}),
                  EventAccess(&GossipStoneFairy,   {[]{return GossipStoneFairy   || CanSummonGossipFairy;}}),
                  EventAccess(&BugRock,            {[]{return IsChild;}}),
                }, {
                  //Locations
                  LocationAccess(DMT_TRADE_BROKEN_SWORD,    {[]{return IsAdult && BrokenSword;}}),
                  LocationAccess(DMT_TRADE_EYEDROPS,        {[]{return IsAdult && Eyedrops;}}),
                  LocationAccess(DMT_TRADE_CLAIM_CHECK,     {[]{return IsAdult && ClaimCheck;}}),
                  LocationAccess(DMT_GS_FALLING_ROCKS_PATH, {[]{return IsAdult && AtNight && CanUse(MEGATON_HAMMER) && CanGetNightTimeGS;}}),
                  LocationAccess(DMT_GOSSIP_STONE,          {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DEATH_MOUNTAIN_TRAIL,     {[]{return true;}}),
                  Entrance(DMC_UPPER_LOCAL,          {[]{return true;}}),
                  Entrance(DMT_OWL_FLIGHT,           {[]{return IsChild;}}),
                  Entrance(DMT_COW_GROTTO,           {[]{return Here(DEATH_MOUNTAIN_SUMMIT, []{return CanBlastOrSmash;});}}),
                  Entrance(DMT_GREAT_FAIRY_FOUNTAIN, {[]{return Here(DEATH_MOUNTAIN_SUMMIT, []{return CanBlastOrSmash;});}}),
  });

  areaTable[DMT_OWL_FLIGHT] = Area("DMT Owl Flight", "Death Mountain", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(KAK_IMPAS_LEDGE, {[]{return true;}}),
  });

  areaTable[DMT_COW_GROTTO] = Area("DMT Cow Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DMT_COW_GROTTO_COW, {[]{return CanPlay(EponasSong);}}),
                }, {
                  //Exits
                  Entrance(DEATH_MOUNTAIN_SUMMIT, {[]{return true;}}),

  });

  areaTable[DMT_STORMS_GROTTO] = Area("DMT Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(DMT_STORMS_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(DMT_STORMS_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DEATH_MOUNTAIN_TRAIL, {[]{return true;}}),
  });

  areaTable[DMT_GREAT_FAIRY_FOUNTAIN] = Area("DMT Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DMT_GREAT_FAIRY_REWARD, {[]{return CanPlay(ZeldasLullaby);}}),
                }, {
                  //Exits
                  Entrance(DEATH_MOUNTAIN_SUMMIT, {[]{return true;}}),
  });

  areaTable[GORON_CITY] = Area("Goron City", "Goron City", GORON_CITY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy,          {[]{return GossipStoneFairy          || CanSummonGossipFairyWithoutSuns;}}),
                  EventAccess(&StickPot,                  {[]{return StickPot                  || IsChild;}}),
                  EventAccess(&BugRock,                   {[]{return CanBlastOrSmash || CanUse(SILVER_GAUNTLETS);}}),
                  EventAccess(&GoronCityChildFire,        {[]{return GoronCityChildFire        || (IsChild && CanUse(DINS_FIRE));}}),
                  EventAccess(&GCWoodsWarpOpen,           {[]{return GCWoodsWarpOpen           || (CanBlastOrSmash || CanUse(DINS_FIRE) || CanUse(BOW) || GoronBracelet || GoronCityChildFire);}}),
                  EventAccess(&StopGCRollingGoronAsAdult, {[]{return StopGCRollingGoronAsAdult || (IsAdult && (GoronBracelet || HasExplosives || Bow || (LogicLinkGoronDins && CanUse(DINS_FIRE))));}}),
                }, {
                  //Locations
                  LocationAccess(GC_MAZE_LEFT_CHEST,        {[]{return CanUse(MEGATON_HAMMER) || CanUse(SILVER_GAUNTLETS) || (LogicGoronCityLeftMost && HasExplosives && CanUse(HOVER_BOOTS));}}),
                  LocationAccess(GC_MAZE_CENTER_CHEST,      {[]{return CanBlastOrSmash  || CanUse(SILVER_GAUNTLETS);}}),
                  LocationAccess(GC_MAZE_RIGHT_CHEST,       {[]{return CanBlastOrSmash  || CanUse(SILVER_GAUNTLETS);}}),
                  LocationAccess(GC_POT_FREESTANDING_POH,   {[]{return IsChild && GoronCityChildFire && (Bombs || (GoronBracelet && LogicGoronCityPotWithStrength) || (HasBombchus && LogicGoronCityPot));}}),
                  LocationAccess(GC_ROLLING_GORON_AS_CHILD, {[]{return IsChild && (HasExplosives || (GoronBracelet && LogicChildRollingWithStrength));}}),
                  LocationAccess(GC_ROLLING_GORON_AS_ADULT, {[]{return StopGCRollingGoronAsAdult;}}),
                  LocationAccess(GC_GS_BOULDER_MAZE,        {[]{return IsChild && HasExplosives;}}),
                  LocationAccess(GC_GS_CENTER_PLATFORM,     {[]{return IsAdult;}}),
                  LocationAccess(GC_MEDIGORON,              {[]{return IsAdult && AdultsWallet && (CanBlastOrSmash || GoronBracelet);}}),
                  LocationAccess(GC_MAZE_GOSSIP_STONE,      {[]{return CanBlastOrSmash || CanUse(SILVER_GAUNTLETS);}}),
                  LocationAccess(GC_MEDIGORON_GOSSIP_STONE, {[]{return CanBlastOrSmash || GoronBracelet;}}),
                }, {
                  //Exits
                  Entrance(DEATH_MOUNTAIN_TRAIL, {[]{return true;}}),
                  Entrance(GC_WOODS_WARP,        {[]{return GCWoodsWarpOpen;}}),
                  Entrance(GC_SHOP,              {[]{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && (HasExplosives || GoronBracelet || GoronCityChildFire));}}),
                  Entrance(GC_DARUNIAS_CHAMBER,  {[]{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && CanPlay(ZeldasLullaby));}}),
                  Entrance(GC_GROTTO_PLATFORM,   {[]{return IsAdult &&
                                                            ((CanPlay(SongOfTime) &&
                                                                    ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) &&
                                                                      DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE)) ||
                                                                          CanUse(GORON_TUNIC) || CanUse(LONGSHOT) || CanUse(NAYRUS_LOVE))) ||
                                                                    (CanUse(HOOKSHOT) &&
                                                                          ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && CanUse(GORON_TUNIC)) ||
                                                                                CanUse(NAYRUS_LOVE))));}}),
  });

  areaTable[GC_WOODS_WARP] = Area("GC Woods Warp", "Goron City", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GCWoodsWarpOpen, {[]{return GCWoodsWarpOpen || (CanBlastOrSmash || CanUse(DINS_FIRE));}}),
                }, {}, {
                  //Exits
                  Entrance(GORON_CITY,     {[]{return CanLeaveForest && GCWoodsWarpOpen;}}),
                  Entrance(THE_LOST_WOODS, {[]{return true;}}),
  });

  areaTable[GC_DARUNIAS_CHAMBER] = Area("GC Darunias Chamber", "Goron City", GORON_CITY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GoronCityChildFire, {[]{return GoronCityChildFire || (CanUse(STICKS));}}),
                }, {
                  //Locations
                  LocationAccess(GC_DARUNIAS_JOY, {[]{return IsChild && CanPlay(SariasSong);}}),
                }, {
                  //Exits
                  Entrance(GORON_CITY,      {[]{return true;}}),
                  Entrance(DMC_LOWER_LOCAL, {[]{return IsAdult;}}),
  });

  areaTable[GC_GROTTO_PLATFORM] = Area("GC Grotto Platform", "Goron City", GORON_CITY, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GC_GROTTO,  {[]{return true;}}),
                  Entrance(GORON_CITY, {[]{return (DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE)) ||
                                                  CanUse(GORON_TUNIC) || CanUse(NAYRUS_LOVE) || (CanPlay(SongOfTime) && CanUse(LONGSHOT));}}),
  });

  areaTable[GC_SHOP] = Area("GC Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GC_SHOP_ITEM_1, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_2, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_3, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_4, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_5, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_6, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_7, {[]{return true;}}),
                  LocationAccess(GC_SHOP_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(GORON_CITY, {[]{return true;}}),
  });

  areaTable[GC_GROTTO] = Area("GC Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GC_DEKU_SCRUB_GROTTO_LEFT,   {[]{return CanStunDeku;}}),
                  LocationAccess(GC_DEKU_SCRUB_GROTTO_RIGHT,  {[]{return CanStunDeku;}}),
                  LocationAccess(GC_DEKU_SCRUB_GROTTO_CENTER, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(GC_GROTTO_PLATFORM, {[]{return true;}}),
  });

  areaTable[DMC_UPPER_NEARBY] = Area("DMC Upper Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DMC_UPPER_LOCAL,       {[]{return CanUse(GORON_TUNIC);}}),
                  Entrance(DEATH_MOUNTAIN_SUMMIT, {[]{return true;}}),
                  Entrance(DMC_UPPER_GROTTO,      {[]{return Here(DMC_UPPER_NEARBY, []{return CanBlastOrSmash;});}})
  });

  areaTable[DMC_UPPER_LOCAL] = Area("DMC Upper Local", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || (HasExplosives && CanSummonGossipFairyWithoutSuns);}}),
                }, {
                  //Locations
                  LocationAccess(DMC_WALL_FREESTANDING_POH, {[]{return true;}}),
                  LocationAccess(DMC_GS_CRATE,              {[]{return IsChild && CanChildAttack;}}),
                  LocationAccess(DMC_GOSSIP_STONE,          {[]{return HasExplosives;}}),
                }, {
                  //Exits
                  Entrance(DMC_UPPER_NEARBY,       {[]{return true;}}),
                  Entrance(DMC_LADDER_AREA_NEARBY, {[]{return true;}}),
                  Entrance(DMC_CENTRAL_NEARBY,     {[]{return CanUse(GORON_TUNIC) && CanUse(LONGSHOT) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE)) || (Fairy && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF)) || CanUse(NAYRUS_LOVE));}}),
                  Entrance(DMC_CENTRAL_LOCAL,      {[]{return false;},
                                        /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}),
  });

  areaTable[DMC_LADDER_AREA_NEARBY] = Area("DMC Ladder Area Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DMC_DEKU_SCRUB, {[]{return IsChild && CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(DMC_UPPER_NEARBY, {[]{return IsAdult;}}),
                  Entrance(DMC_LOWER_NEARBY, {[]{return CanUse(HOVER_BOOTS) || (LogicCraterUpperToLower && CanUse(MEGATON_HAMMER));}}),
  });

  areaTable[DMC_LOWER_NEARBY] = Area("DMC Lower Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DMC_LOWER_LOCAL,          {[]{return CanUse(GORON_TUNIC);}}),
                  Entrance(GC_DARUNIAS_CHAMBER,      {[]{return true;}}),
                  Entrance(DMC_GREAT_FAIRY_FOUNTAIN, {[]{return CanUse(MEGATON_HAMMER);}}),
                  Entrance(DMC_HAMMER_GROTTO,        {[]{return CanUse(MEGATON_HAMMER);}}),
  });

  areaTable[DMC_LOWER_LOCAL] = Area("DMC Lower Local", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DMC_LOWER_NEARBY,       {[]{return true;}}),
                  Entrance(DMC_LADDER_AREA_NEARBY, {[]{return true;}}),
                  Entrance(DMC_CENTRAL_NEARBY,     {[]{return CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT);}}),
                  Entrance(DMC_CENTRAL_LOCAL,      {[]{return (CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT)) && (LogicFewerTunicRequirements || CanUse(GORON_TUNIC));}}),
  });

  areaTable[DMC_CENTRAL_NEARBY] = Area("DMC Central Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DMC_VOLCANO_FREESTANDING_POH, {[]{return IsAdult && (CanPlantBean(DMC_CENTRAL_LOCAL) || (LogicCraterBeanPoHWithHovers && HoverBoots));}}),
                  LocationAccess(SHEIK_IN_CRATER,              {[]{return IsAdult;}}),
                }, {
                  //Exits
                  Entrance(DMC_CENTRAL_LOCAL, {[]{return CanUse(GORON_TUNIC);}}),
  });

  areaTable[DMC_CENTRAL_LOCAL] = Area("DMC Central Local", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BeanPlantFairy, {[]{return BeanPlantFairy || (CanPlantBean(DMC_CENTRAL_LOCAL) && CanPlay(SongOfStorms));}}),
                }, {
                  //Locations
                  LocationAccess(DMC_GS_BEAN_PATCH, {[]{return CanPlantBugs && CanChildAttack;}}),
                }, {
                  //Exits
                  Entrance(DMC_CENTRAL_NEARBY,   {[]{return true;}}),
                  Entrance(DMC_LOWER_NEARBY,     {[]{return IsAdult && (CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT) || CanPlantBean(DMC_CENTRAL_LOCAL));}}),
                  Entrance(DMC_UPPER_NEARBY,     {[]{return IsAdult && CanPlantBean(DMC_CENTRAL_LOCAL);}}),
                  Entrance(FIRE_TEMPLE_ENTRYWAY, {[]{return (IsChild && ShuffleDungeonEntrances.IsNot(SHUFFLEDUNGEONS_OFF)) || (IsAdult && (LogicFewerTunicRequirements || CanUse(GORON_TUNIC)));}}),
  });

  areaTable[DMC_GREAT_FAIRY_FOUNTAIN] = Area("DMC Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DMC_GREAT_FAIRY_REWARD, {[]{return CanPlay(ZeldasLullaby);}}),
                }, {
                  //Exits
                  Entrance(DMC_LOWER_LOCAL, {[]{return true;}}),
  });

  areaTable[DMC_UPPER_GROTTO] = Area("DMC Upper Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(DMC_UPPER_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(DMC_UPPER_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DMC_UPPER_LOCAL, {[]{return true;}}),
  });

  areaTable[DMC_HAMMER_GROTTO] = Area("DMC Hammer Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DMC_DEKU_SCRUB_GROTTO_LEFT,   {[]{return CanStunDeku;}}),
                  LocationAccess(DMC_DEKU_SCRUB_GROTTO_RIGHT,  {[]{return CanStunDeku;}}),
                  LocationAccess(DMC_DEKU_SCRUB_GROTTO_CENTER, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(DMC_LOWER_LOCAL, {[]{return true;}}),
  });

  areaTable[ZR_FRONT] = Area("ZR Front", "Zora River", ZORAS_RIVER, DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(ZR_GS_TREE, {[]{return IsChild && CanChildAttack;}}),
                }, {
                  //Exits
                  Entrance(ZORAS_RIVER,  {[]{return IsAdult || HasExplosives;}}),
                  Entrance(HYRULE_FIELD, {[]{return true;}}),
  });

  areaTable[ZORAS_RIVER] = Area("Zora River", "Zora River", ZORAS_RIVER, DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
                  EventAccess(&BeanPlantFairy,   {[]{return BeanPlantFairy   || (CanPlantBean(ZORAS_RIVER) && CanPlay(SongOfStorms));}}),
                  EventAccess(&ButterflyFairy,   {[]{return ButterflyFairy   || CanUse(STICKS);}}),
                  EventAccess(&BugShrub,         {[]{return BugShrub         || CanCutShrubs;}}),
                }, {
                  //Locations
                  LocationAccess(ZR_MAGIC_BEAN_SALESMAN,               {[]{return IsChild;}}),
                  LocationAccess(ZR_FROGS_OCARINA_GAME,                {[]{return IsChild && CanPlay(ZeldasLullaby) && CanPlay(SariasSong) && CanPlay(SunsSong) && CanPlay(EponasSong) && CanPlay(SongOfTime) && CanPlay(SongOfStorms);}}),
                  LocationAccess(ZR_FROGS_IN_THE_RAIN,                 {[]{return IsChild && CanPlay(SongOfStorms);}}),
                  LocationAccess(ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH, {[]{return IsChild || CanUse(HOVER_BOOTS) || (IsAdult && LogicZoraRiverLower);}}),
                  LocationAccess(ZR_NEAR_DOMAIN_FREESTANDING_POH,      {[]{return IsChild || CanUse(HOVER_BOOTS) || (IsAdult && LogicZoraRiverUpper);}}),
                  LocationAccess(ZR_GS_LADDER,                         {[]{return IsChild && AtNight && CanChildAttack && CanGetNightTimeGS;}}),
                  LocationAccess(ZR_GS_NEAR_RAISED_GROTTOS,            {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(ZR_GS_ABOVE_BRIDGE,                   {[]{return CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(ZR_NEAR_GROTTOS_GOSSIP_STONE,         {[]{return true;}}),
                  LocationAccess(ZR_NEAR_DOMAIN_GOSSIP_STONE,          {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(ZR_FRONT,            {[]{return true;}}),
                  Entrance(ZR_OPEN_GROTTO,      {[]{return true;}}),
                  Entrance(ZR_FAIRY_GROTTO,     {[]{return Here(ZORAS_RIVER, []{return CanBlastOrSmash;});}}),
                  Entrance(THE_LOST_WOODS,      {[]{return CanDive || CanUse(IRON_BOOTS);}}),
                  Entrance(ZR_STORMS_GROTTO,    {[]{return CanOpenStormGrotto;}}),
                  Entrance(ZR_BEHIND_WATERFALL, {[]{return CanPlay(ZeldasLullaby);}}),
  });

  areaTable[ZR_BEHIND_WATERFALL] = Area("ZR Behind Waterfall", "Zora River", NONE, DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(ZORAS_RIVER,  {[]{return true;}}),
                  Entrance(ZORAS_DOMAIN, {[]{return true;}}),
  });

  areaTable[ZR_OPEN_GROTTO] = Area("ZR Open Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  LocationAccess(ZR_OPEN_GROTTO_CHEST,        {[]{return true;}}),
                  LocationAccess(ZR_OPEN_GROTTO_GOSSIP_STONE, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(ZORAS_RIVER, {[]{return true;}}),
  });

  areaTable[ZR_FAIRY_GROTTO] = Area("ZR Fairy Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Event
                  EventAccess(&FreeFairies, {[]{return true;}}),
                }, {}, {
                  //Exits
                  Entrance(ZORAS_RIVER, {[]{return true;}}),
  });

  areaTable[ZR_STORMS_GROTTO] = Area("ZR Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(ZR_DEKU_SCRUB_GROTTO_REAR,  {[]{return CanStunDeku;}}),
                  LocationAccess(ZR_DEKU_SCRUB_GROTTO_FRONT, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(ZORAS_RIVER, {[]{return true;}}),
  });

  areaTable[ZORAS_DOMAIN] = Area("Zoras Domain", "Zoras Domain", ZORAS_DOMAIN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&EyeballFrogAccess, {[]{return EyeballFrogAccess || (IsAdult && KingZoraThawed && (Eyedrops || EyeballFrog || Prescription || PrescriptionAccess));}}),
                  EventAccess(&GossipStoneFairy,  {[]{return GossipStoneFairy  || CanSummonGossipFairyWithoutSuns;}}),
                  EventAccess(&NutPot,            {[]{return true;}}),
                  EventAccess(&StickPot,          {[]{return StickPot          || IsChild;}}),
                  EventAccess(&FishGroup,         {[]{return FishGroup         || IsChild;}}),
                  EventAccess(&KingZoraThawed,    {[]{return KingZoraThawed    || (IsAdult   && BlueFire);}}),
                  EventAccess(&DeliverLetter,     {[]{return DeliverLetter     || (RutosLetter && IsChild && ZorasFountain.IsNot(ZORASFOUNTAIN_OPEN));}}),
                }, {
                  //Locations
                  LocationAccess(ZD_DIVING_MINIGAME,     {[]{return IsChild;}}),
                  LocationAccess(ZD_CHEST,               {[]{return CanUse(STICKS);}}),
                  LocationAccess(ZD_KING_ZORA_THAWED,    {[]{return KingZoraThawed;}}),
                  LocationAccess(ZD_TRADE_PRESCRIPTION,  {[]{return KingZoraThawed && Prescription;}}),
                  LocationAccess(ZD_GS_FROZEN_WATERFALL, {[]{return IsAdult && AtNight && (Hookshot || Bow || MagicMeter) && CanGetNightTimeGS;}}),
                  LocationAccess(ZD_GOSSIP_STONE,        {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(ZR_BEHIND_WATERFALL, {[]{return true;}}),
                  Entrance(LAKE_HYLIA,          {[]{return IsChild && CanDive;}}),
                  Entrance(ZD_BEHIND_KING_ZORA, {[]{return DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) || (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult);},
                                     /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::NOVICE) || (IsChild && CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE));}}),
                  Entrance(ZD_SHOP,             {[]{return IsChild || BlueFire;}}),
                  Entrance(ZD_STORMS_GROTTO,    {[]{return CanOpenStormGrotto;}}),
  });

  areaTable[ZD_BEHIND_KING_ZORA] = Area("ZD Behind King Zora", "Zoras Domain", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(ZORAS_DOMAIN,   {[]{return DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) || (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult);}}),
                  Entrance(ZORAS_FOUNTAIN, {[]{return true;}}),
  });

  areaTable[ZD_SHOP] = Area("ZD Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(ZD_SHOP_ITEM_1, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_2, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_3, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_4, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_5, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_6, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_7, {[]{return true;}}),
                  LocationAccess(ZD_SHOP_ITEM_8, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(ZORAS_DOMAIN, {[]{return true;}}),
  });

  areaTable[ZD_STORMS_GROTTO] = Area("ZD Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FreeFairies, {[]{return true;}}),
                }, {}, {
                  //Exits
                  Entrance(ZORAS_DOMAIN, {[]{return true;}}),
  });

  areaTable[ZORAS_FOUNTAIN] = Area("Zoras Fountain", "Zoras Fountain", ZORAS_FOUNTAIN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}}),
                  EventAccess(&ButterflyFairy,   {[]{return ButterflyFairy   || (CanUse(STICKS) && AtDay);}}),
                }, {
                  //Locations
                  LocationAccess(ZF_ICEBERG_FREESTANDING_POH, {[]{return IsAdult;}}),
                  LocationAccess(ZF_BOTTOM_FREESTANDING_POH,  {[]{return IsAdult && IronBoots && (LogicFewerTunicRequirements || CanUse(ZORA_TUNIC));}}),
                  LocationAccess(ZF_GS_TREE,                  {[]{return IsChild;}}),
                  LocationAccess(ZF_GS_ABOVE_THE_LOG,         {[]{return CanUse(BOOMERANG) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(ZF_GS_HIDDEN_CAVE,           {[]{return CanUse(SILVER_GAUNTLETS) && CanBlastOrSmash && CanUse(HOOKSHOT) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(ZF_FAIRY_GOSSIP_STONE,       {[]{return true;}}),
                  LocationAccess(ZF_JABU_GOSSIP_STONE,        {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(ZD_BEHIND_KING_ZORA,       {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_ENTRYWAY, {[]{return (IsChild && Fish);}}),
                  Entrance(ICE_CAVERN_ENTRYWAY,       {[]{return IsAdult;}}),
                  Entrance(ZF_GREAT_FAIRY_FOUNTAIN,   {[]{return HasExplosives;}}),
  });

  areaTable[ZF_GREAT_FAIRY_FOUNTAIN] = Area("ZF Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(ZF_GREAT_FAIRY_REWARD, {[]{return CanPlay(ZeldasLullaby);}}),
                }, {
                  //Exits
                  Entrance(ZORAS_FOUNTAIN, {[]{return true;}}),
  });

  areaTable[LON_LON_RANCH] = Area("Lon Lon Ranch", "Lon Lon Ranch", LON_LON_RANCH, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&Epona,    {[]{return Epona    || (CanPlay(EponasSong) && IsAdult && AtDay);}}),
                  EventAccess(&LinksCow, {[]{return LinksCow || (CanPlay(EponasSong) && IsAdult && AtDay);}}),
                }, {
                  //Locations
                  LocationAccess(SONG_FROM_MALON,     {[]{return IsChild && ZeldasLetter && Ocarina && AtDay;}}),
                  LocationAccess(LLR_GS_TREE,         {[]{return IsChild;}}),
                  LocationAccess(LLR_GS_RAIN_SHED,    {[]{return IsChild && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(LLR_GS_HOUSE_WINDOW, {[]{return CanUse(BOOMERANG) && AtNight && CanGetNightTimeGS;}}),
                  LocationAccess(LLR_GS_BACK_WALL,    {[]{return CanUse(BOOMERANG) && AtNight && CanGetNightTimeGS;},
                                           /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && AtNight && CanGetNightTimeGS;}}),
                }, {
                  //Exits
                  Entrance(HYRULE_FIELD,     {[]{return true;}}),
                  Entrance(LLR_TALONS_HOUSE, {[]{return true;}}),
                  Entrance(LLR_STABLES,      {[]{return true;}}),
                  Entrance(LLR_TOWER,        {[]{return true;}}),
                  Entrance(LLR_GROTTO,       {[]{return IsChild;}}),
  });

  areaTable[LLR_TALONS_HOUSE] = Area("LLR Talons House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LLR_TALONS_CHICKENS, {[]{return IsChild && AtDay && ZeldasLetter;}}),
                }, {
                  //Exits
                  Entrance(LON_LON_RANCH, {[]{return true;}}),
  });

  areaTable[LLR_STABLES] = Area("LLR Stables", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LLR_STABLES_LEFT_COW,  {[]{return CanPlay(EponasSong);}}),
                  LocationAccess(LLR_STABLES_RIGHT_COW, {[]{return CanPlay(EponasSong);}}),
                }, {
                  //Exits
                  Entrance(LON_LON_RANCH, {[]{return true;}}),
  });

  areaTable[LLR_TOWER] = Area("LLR Tower", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LLR_FREESTANDING_POH, {[]{return IsChild;}}),
                  LocationAccess(LLR_TOWER_LEFT_COW,   {[]{return CanPlay(EponasSong);}}),
                  LocationAccess(LLR_TOWER_RIGHT_COW,  {[]{return CanPlay(EponasSong);}}),
                }, {
                  //Exits
                  Entrance(LON_LON_RANCH, {[]{return true;}}),
  });

  areaTable[LLR_GROTTO] = Area("LLR Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(LLR_DEKU_SCRUB_GROTTO_LEFT,   {[]{return CanStunDeku;}}),
                  LocationAccess(LLR_DEKU_SCRUB_GROTTO_RIGHT,  {[]{return CanStunDeku;}}),
                  LocationAccess(LLR_DEKU_SCRUB_GROTTO_CENTER, {[]{return CanStunDeku;}}),
                }, {
                  //Exits
                  Entrance(LON_LON_RANCH, {[]{return true;}}),
  });

  /*--------------------------
  |    VANILLA/MQ DECIDERS   |
  ---------------------------*/
  areaTable[DEKU_TREE_ENTRYWAY] = Area("Deku Tree Entryway", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DEKU_TREE_LOBBY,      {[]{return Dungeon::DekuTree.IsVanilla();}}),
                  Entrance(DEKU_TREE_MQ_LOBBY,   {[]{return Dungeon::DekuTree.IsMQ();}}),
                  Entrance(KF_OUTSIDE_DEKU_TREE, {[]{return true;}}),
  });

  areaTable[DODONGOS_CAVERN_ENTRYWAY] = Area("Dodongos Cavern Entryway", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_BEGINNING,    {[]{return Dungeon::DodongosCavern.IsVanilla();}}),
                  Entrance(DODONGOS_CAVERN_MQ_BEGINNING, {[]{return Dungeon::DodongosCavern.IsMQ();}}),
                  Entrance(DEATH_MOUNTAIN_TRAIL,         {[]{return true;}}),
  });

  areaTable[JABU_JABUS_BELLY_ENTRYWAY] = Area("Jabu Jabus Belly Entryway", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_BEGINNING,    {[]{return Dungeon::JabuJabusBelly.IsVanilla();}}),
                  Entrance(JABU_JABUS_BELLY_MQ_BEGINNING, {[]{return Dungeon::JabuJabusBelly.IsMQ();}}),
                  Entrance(ZORAS_FOUNTAIN,                {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_ENTRYWAY] = Area("Forest Temple Entryway", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(FOREST_TEMPLE_LOBBY,    {[]{return Dungeon::ForestTemple.IsVanilla();}}),
                  Entrance(FOREST_TEMPLE_MQ_LOBBY, {[]{return Dungeon::ForestTemple.IsMQ();}}),
                  Entrance(SACRED_FOREST_MEADOW,   {[]{return true;}}),
  });

  areaTable[FIRE_TEMPLE_ENTRYWAY] = Area("Fire Temple Entryway", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(FIRE_TEMPLE_LOWER,    {[]{return Dungeon::FireTemple.IsVanilla();}}),
                  Entrance(FIRE_TEMPLE_MQ_LOWER, {[]{return Dungeon::FireTemple.IsMQ();}}),
                  Entrance(DMC_CENTRAL_LOCAL,    {[]{return true;}}),
  });

  areaTable[WATER_TEMPLE_ENTRYWAY] = Area("Water Temple Entryway", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(WATER_TEMPLE_LOBBY,    {[]{return Dungeon::WaterTemple.IsVanilla();}}),
                  Entrance(WATER_TEMPLE_MQ_LOBBY, {[]{return Dungeon::WaterTemple.IsMQ();}}),
                  Entrance(LAKE_HYLIA,            {[]{return true;}}),
  });

  areaTable[SPIRIT_TEMPLE_ENTRYWAY] = Area("Spirit Temple Entryway", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_LOBBY,    {[]{return Dungeon::SpiritTemple.IsVanilla();}}),
                  Entrance(SPIRIT_TEMPLE_MQ_LOBBY, {[]{return Dungeon::SpiritTemple.IsMQ();}}),
                  Entrance(DESERT_COLOSSUS,        {[]{return true;}}),
  });

  areaTable[SHADOW_TEMPLE_ENTRYWAY] = Area("Shadow Temple Entryway", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_BEGINNING,    {[]{return Dungeon::ShadowTemple.IsVanilla() && (LogicLensShadow || CanUse(LENS_OF_TRUTH)) && (CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT));},
                                            /*Glitched*/[]{return Dungeon::ShadowTemple.IsVanilla() && (LogicLensShadow || CanUse(LENS_OF_TRUTH)) && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);}}),
                  Entrance(SHADOW_TEMPLE_MQ_BEGINNING, {[]{return Dungeon::ShadowTemple.IsMQ()    && (LogicLensShadowMQ || CanUse(LENS_OF_TRUTH)) && (CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT));},
                                            /*Glitched*/[]{return Dungeon::ShadowTemple.IsMQ()    && (LogicLensShadowMQ || CanUse(LENS_OF_TRUTH)) && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);}}),
                  Entrance(GRAVEYARD_WARP_PAD_REGION,  {[]{return true;}}),
  });

  areaTable[BOTTOM_OF_THE_WELL_ENTRYWAY] = Area("Bottom of the Well Entryway", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(BOTTOM_OF_THE_WELL_MAIN_AREA,    {[]{return Dungeon::BottomOfTheWell.IsVanilla() && IsChild && (CanChildAttack || Nuts);}}),
                  Entrance(BOTTOM_OF_THE_WELL_MQ_PERIMETER, {[]{return Dungeon::BottomOfTheWell.IsMQ()      && IsChild;}}),
                  Entrance(KAKARIKO_VILLAGE,                {[]{return true;}}),
  });

  areaTable[ICE_CAVERN_ENTRYWAY] = Area("Ice Cavern Entryway", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(ICE_CAVERN_BEGINNING,    {[]{return Dungeon::IceCavern.IsVanilla();}}),
                  Entrance(ICE_CAVERN_MQ_BEGINNING, {[]{return Dungeon::IceCavern.IsMQ();}}),
                  Entrance(ZORAS_FOUNTAIN,          {[]{return true;}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_ENTRYWAY] = Area("Gerudo Training Grounds Entryway", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_LOBBY,    {[]{return Dungeon::GerudoTrainingGrounds.IsVanilla();}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_LOBBY, {[]{return Dungeon::GerudoTrainingGrounds.IsMQ();}}),
                  Entrance(GERUDO_FORTRESS,                  {[]{return true;}}),
  });

  areaTable[GANONS_CASTLE_ENTRYWAY] = Area("Ganon's Castle Entryway", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GANONS_CASTLE_LOBBY,    {[]{return Dungeon::GanonsCastle.IsVanilla();}}),
                  Entrance(GANONS_CASTLE_MQ_LOBBY, {[]{return Dungeon::GanonsCastle.IsMQ();}}),
                  Entrance(GANONS_CASTLE_GROUNDS,  {[]{return true;}}),
  });

  /*--------------------------
  |    VANILLA DUNGEONS      |
  ---------------------------*/
  if (Dungeon::DekuTree.IsVanilla()) {

  areaTable[DEKU_TREE_LOBBY] = Area("Deku Tree Lobby", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks, {[]{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}}),
                  EventAccess(&DekuBabaNuts,   {[]{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(DINS_FIRE));}}),
                }, {
                  //Locations
                  LocationAccess(DEKU_TREE_MAP_CHEST,               {[]{return true;}}),
                  LocationAccess(DEKU_TREE_COMPASS_CHEST,           {[]{return true;}}),
                  LocationAccess(DEKU_TREE_COMPASS_ROOM_SIDE_CHEST, {[]{return true;}}),
                  LocationAccess(DEKU_TREE_BASEMENT_CHEST,          {[]{return IsAdult || CanChildAttack || Nuts;}}),
                  LocationAccess(DEKU_TREE_GS_COMPASS_ROOM,         {[]{return IsAdult || CanChildAttack;}}),
                  LocationAccess(DEKU_TREE_GS_BASEMENT_VINES,       {[]{return CanUseProjectile || CanUse(DINS_FIRE) || (LogicDekuBasementGS && (IsAdult || Sticks || KokiriSword));}}),
                  LocationAccess(DEKU_TREE_GS_BASEMENT_GATE,        {[]{return IsAdult || CanChildAttack;}}),
                }, {
                  //Exits
                  Entrance(DEKU_TREE_ENTRYWAY,           {[]{return true;}}),
                  Entrance(DEKU_TREE_SLINGSHOT_ROOM,     {[]{return Here(DEKU_TREE_LOBBY, []{return HasShield;});}}),
                  Entrance(DEKU_TREE_BASEMENT_BACK_ROOM, {[]{return (Here(DEKU_TREE_LOBBY, []{return HasFireSourceWithTorch || CanUse(BOW);}) &&
                                                                            Here(DEKU_TREE_LOBBY, []{return CanUse(SLINGSHOT) || CanUse(BOW);})) ||
                                                                            (IsChild && (LogicDekuB1Skip || Here(DEKU_TREE_LOBBY, []{return IsAdult;})));}}),
                  Entrance(DEKU_TREE_BOSS_ROOM,          {[]{return Here(DEKU_TREE_LOBBY, []{return HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse(BOW));}) &&
                                                                            (LogicDekuB1Skip || Here(DEKU_TREE_LOBBY, []{return IsAdult || CanUse(SLINGSHOT);}));}}),
  });

  areaTable[DEKU_TREE_SLINGSHOT_ROOM] = Area("Deku Tree Slingshot Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_TREE_SLINGSHOT_CHEST,           {[]{return true;}}),
                  LocationAccess(DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DEKU_TREE_LOBBY, {[]{return true;}}),
  });

  areaTable[DEKU_TREE_BASEMENT_BACK_ROOM] = Area("Deku Tree Basement Backroom", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_TREE_GS_BASEMENT_BACK_ROOM,  {[]{return Here(DEKU_TREE_BASEMENT_BACK_ROOM, []{return HasFireSourceWithTorch || CanUse(BOW);}) &&
                                                                                  Here(DEKU_TREE_BASEMENT_BACK_ROOM, []{return CanBlastOrSmash;}) &&
                                                                                    HookshotOrBoomerang;}}),
                }, {
                  //Exits
                  Entrance(DEKU_TREE_LOBBY, {[]{return true;}}),

  });

  areaTable[DEKU_TREE_BOSS_ROOM] = Area("Deku Tree Boss Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuTreeClear, {[]{return DekuTreeClear || (Here(DEKU_TREE_BOSS_ROOM, []{return HasShield;}) && (IsAdult || KokiriSword || Sticks) &&
                                                                              (Nuts || CanUse(SLINGSHOT) || CanUse(BOW) || HookshotOrBoomerang));}}),
                }, {
                  //Locations
                  LocationAccess(QUEEN_GOHMA,                 {[]{return Here(DEKU_TREE_BOSS_ROOM, []{return HasShield;}) && (IsAdult || KokiriSword || Sticks) &&
                                                                            (Nuts || CanUse(SLINGSHOT) || CanUse(BOW) || HookshotOrBoomerang);}}),
                  LocationAccess(DEKU_TREE_QUEEN_GOHMA_HEART, {[]{return Here(DEKU_TREE_BOSS_ROOM, []{return HasShield;}) && (IsAdult || KokiriSword || Sticks) &&
                                                                            (Nuts || CanUse(SLINGSHOT) || CanUse(BOW) || HookshotOrBoomerang);}}),
                }, {
                  //Exits
                  Entrance(DEKU_TREE_LOBBY, {[]{return true;}}),
  });
  }

  if (Dungeon::DodongosCavern.IsVanilla()) {
  areaTable[DODONGOS_CAVERN_BEGINNING] = Area("Dodongos Cavern Beginning", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_ENTRYWAY, {[]{return true;}}),
                  Entrance(DODONGOS_CAVERN_LOBBY,    {[]{return Here(DODONGOS_CAVERN_BEGINNING, []{return CanBlastOrSmash || GoronBracelet;});}}),
  });

  areaTable[DODONGOS_CAVERN_LOBBY] = Area("Dodongos Cavern Lobby", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
                }, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_MAP_CHEST,                          {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_COMPASS_CHEST,                      {[]{return IsAdult || Sticks || (CanUse(DINS_FIRE) && (Slingshot || HasExplosives || KokiriSword));}}),
                  LocationAccess(DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS,   {[]{return HasExplosives || IsAdult || Slingshot || Boomerang || Sticks || KokiriSword;}}),
                  LocationAccess(DODONGOS_CAVERN_GS_SCARECROW,                       {[]{return CanUse(SCARECROW) || CanUse(LONGSHOT) || (LogicDCScarecrowGS && (IsAdult || CanChildAttack));}}),
                  LocationAccess(DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS, {[]{return IsAdult || Slingshot || Sticks || HasExplosives || KokiriSword;}}),
                  LocationAccess(DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,                   {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_GOSSIP_STONE,                       {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_BEGINNING,  {[]{return true;}}),
                  Entrance(DODONGOS_CAVERN_CLIMB,      {[]{return Here(DODONGOS_CAVERN_LOBBY, []{return IsAdult || ((Sticks || CanUse(DINS_FIRE)) && (Slingshot || Sticks || HasExplosives || KokiriSword));}) && (HasExplosives || GoronBracelet || CanUse(DINS_FIRE) ||(LogicDCStaircase && CanUse(BOW)));}}),
                  Entrance(DODONGOS_CAVERN_FAR_BRIDGE, {[]{return HasAccessTo(DODONGOS_CAVERN_FAR_BRIDGE);}}),
  });

  areaTable[DODONGOS_CAVERN_CLIMB] = Area("Dodongos Cavern Climb", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,     {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,          {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT, {[]{return CanBlastOrSmash;}}),
                  LocationAccess(DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,  {[]{return CanBlastOrSmash;}}),
                }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_LOBBY,      {[]{return true;}}),
                  Entrance(DODONGOS_CAVERN_FAR_BRIDGE, {[]{return (IsChild && (Slingshot || (LogicDCSlingshotSkip && (Sticks || HasExplosives || KokiriSword)))) || (IsAdult && (Bow || HoverBoots || CanUse(LONGSHOT) || LogicDCJump));}}),
  });

  areaTable[DODONGOS_CAVERN_FAR_BRIDGE] = Area("Dodongos Cavern Far Bridge", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_BOMB_BAG_CHEST,         {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,    {[]{return CanBlastOrSmash;}}),
                  LocationAccess(DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS, {[]{return HookshotOrBoomerang;}}),
                }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_BOSS_AREA, {[]{return HasExplosives;}}),
                  Entrance(DODONGOS_CAVERN_LOBBY,     {[]{return true;}}),
  });

  areaTable[DODONGOS_CAVERN_BOSS_AREA] = Area("Dodongos Cavern Boss Area", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot,            {[]{return true;}}),
                  EventAccess(&DodongosCavernClear, {[]{return DodongosCavernClear || ((Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));}}),
                }, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_BOSS_ROOM_CHEST,    {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_KING_DODONGO_HEART, {[]{return (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}}),
                  LocationAccess(KING_DODONGO,                       {[]{return (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}}),
                  LocationAccess(DODONGOS_CAVERN_GS_BACK_ROOM,       {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_LOBBY, {[]{return true;}}),
  });
  }

  if (Dungeon::JabuJabusBelly.IsVanilla()) {
  areaTable[JABU_JABUS_BELLY_BEGINNING] = Area("Jabu Jabus Belly Beginning", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_ENTRYWAY, {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_MAIN,     {[]{return CanUseProjectile;}}),
  });

  areaTable[JABU_JABUS_BELLY_MAIN] = Area("Jabu Jabus Belly Main", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_BOOMERANG_CHEST,         {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,    {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER, {[]{return HookshotOrBoomerang;}}),
                  LocationAccess(JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER, {[]{return HookshotOrBoomerang;}}),
                  LocationAccess(JABU_JABUS_BELLY_DEKU_SCRUB,              {[]{return CanDive || IsChild || LogicJabuScrubJumpDive || CanUse(IRON_BOOTS);}}),
                }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_BEGINNING, {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_DEPTHS,    {[]{return CanUse(BOOMERANG);}}),
                  Entrance(JABU_JABUS_BELLY_BOSS_AREA, {[]{return LogicJabuBossGSAdult && CanUse(HOVER_BOOTS);}}),
  });

  areaTable[JABU_JABUS_BELLY_DEPTHS] = Area("Jabu Jabus Belly Depths", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_MAP_CHEST,     {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_COMPASS_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_MAIN,      {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_BOSS_AREA, {[]{return Sticks || KokiriSword;}}),
  });

  areaTable[JABU_JABUS_BELLY_BOSS_AREA] = Area("Jabu Jabus Belly Boss Area", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot,              {[]{return true;}}),
                  EventAccess(&JabuJabusBellyClear, {[]{return JabuJabusBellyClear || CanUse(BOOMERANG);}}),
                }, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_BARINADE_HEART, {[]{return CanUse(BOOMERANG);}}),
                  LocationAccess(BARINADE,                        {[]{return CanUse(BOOMERANG);}}),
                  LocationAccess(JABU_JABUS_BELLY_GS_NEAR_BOSS,   {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_MAIN, {[]{return true;}}),
  });
  }

  if (Dungeon::ForestTemple.IsVanilla()) {
  areaTable[FOREST_TEMPLE_LOBBY] = Area("Forest Temple Lobby", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_FIRST_ROOM_CHEST,    {[]{return true;}}),
                  LocationAccess(FOREST_TEMPLE_FIRST_STALFOS_CHEST, {[]{return IsAdult || KokiriSword;}}),
                  LocationAccess(FOREST_TEMPLE_GS_FIRST_ROOM,       {[]{return (IsAdult && (Hookshot || Bow || Bombs)) || (IsChild && (Boomerang || Slingshot)) || HasBombchus || CanUse(DINS_FIRE);}}),
                  LocationAccess(FOREST_TEMPLE_GS_LOBBY,            {[]{return HookshotOrBoomerang;}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_ENTRYWAY,        {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_NW_OUTDOORS,     {[]{return CanPlay(SongOfTime) || IsChild;},
                                               /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::NOVICE);}}),
                  Entrance(FOREST_TEMPLE_NE_OUTDOORS,     {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}),
                  Entrance(FOREST_TEMPLE_BLOCK_PUSH_ROOM, {[]{return SmallKeys(ForestTempleKeys, 1);}}),
                  Entrance(FOREST_TEMPLE_BOSS_REGION,     {[]{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;}}),
  });

  areaTable[FOREST_TEMPLE_NW_OUTDOORS] = Area("Forest Temple NW Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks, {[]{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}}),
                  EventAccess(&DekuBabaNuts,   {[]{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(DINS_FIRE));}}),
                }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD, {[]{return CanUse(LONGSHOT) || Here(FOREST_TEMPLE_OUTSIDE_UPPER_LEDGE, []{return CanUse(HOOKSHOT);});}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_NE_OUTDOORS,             {[]{return CanUse(IRON_BOOTS) || GoldScale;}}),
                  Entrance(FOREST_TEMPLE_OUTDOORS_HIGH_BALCONIES, {[]{return Here(FOREST_TEMPLE_NW_OUTDOORS, []{return HasExplosives || CanUse(MEGATON_HAMMER) || CanUse(BOW) ||
                                                                                ((IsAdult || (IsChild && (Sticks || KokiriSword || Slingshot))) && (Nuts || HookshotOrBoomerang || CanShield));});}}),
                  Entrance(FOREST_TEMPLE_OUTSIDE_UPPER_LEDGE,     {[]{return false;},
                                                       /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE);}}),
  });

  areaTable[FOREST_TEMPLE_NE_OUTDOORS] = Area("Forest Temple NE Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks, {[]{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}}),
                  EventAccess(&DekuBabaNuts,   {[]{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(DINS_FIRE));}}),
                }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST, {[]{return CanUse(HOOKSHOT) || HasAccessTo(FOREST_TEMPLE_FALLING_ROOM);}}),
                  LocationAccess(FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,    {[]{return CanUse(HOOKSHOT) ||
                                                                                          (LogicForestOutdoorEastGS && CanUse(BOOMERANG)) ||
                                                                                          Here(FOREST_TEMPLE_FALLING_ROOM, []{return CanUse(BOW) || CanUse(DINS_FIRE) || HasExplosives;});}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_OUTDOORS_HIGH_BALCONIES, {[]{return CanUse(LONGSHOT);}}),
                  Entrance(FOREST_TEMPLE_NW_OUTDOORS,             {[]{return CanUse(IRON_BOOTS) || GoldScale;}}),
                  Entrance(FOREST_TEMPLE_LOBBY,                   {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_OUTDOORS_HIGH_BALCONIES] = Area("Forest Temple Outdoors High Balconies", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_WELL_CHEST, {[]{return true;}}),
                  LocationAccess(FOREST_TEMPLE_MAP_CHEST,  {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_NW_OUTDOORS,  {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_NE_OUTDOORS,  {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_FALLING_ROOM, {[]{return LogicForestDoorFrame && CanUse(HOVER_BOOTS) && CanUse(SCARECROW);}}),
  });

  areaTable[FOREST_TEMPLE_FALLING_ROOM] = Area("Forest Temple Falling Room", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTempleAmyAndMeg, {[]{return ForestTempleAmyAndMeg || CanUse(BOW);}}),
                }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_NE_OUTDOORS, {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_BLOCK_PUSH_ROOM] = Area("Forest Temple Block Push Room", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_EYE_SWITCH_CHEST, {[]{return GoronBracelet && (CanUse(BOW) || CanUse(SLINGSHOT));}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_OUTSIDE_UPPER_LEDGE, {[]{return CanUse(HOVER_BOOTS) || (LogicForestOutsideBackdoor && IsAdult && GoronBracelet);}}),
                  Entrance(FOREST_TEMPLE_BOW_REGION,          {[]{return GoronBracelet && SmallKeys(ForestTempleKeys, 3) && IsAdult;}}),
                  Entrance(FOREST_TEMPLE_STRAIGHTENED_HALL,   {[]{return GoronBracelet && SmallKeys(ForestTempleKeys, 2) && CanUse(BOW) && IsAdult;}}),
  });

  areaTable[FOREST_TEMPLE_STRAIGHTENED_HALL] = Area("Forest Temple Straightened Hall", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_BOSS_KEY_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_OUTSIDE_UPPER_LEDGE, {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_OUTSIDE_UPPER_LEDGE] = Area("Forest Temple Outside Upper Ledge", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_FLOORMASTER_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_NW_OUTDOORS, {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_BOW_REGION] = Area("Forest Temple Bow Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTempleJoAndBeth, {[]{return ForestTempleJoAndBeth || CanUse(BOW);}}),
                }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_BOW_CHEST,      {[]{return true;}}),
                  LocationAccess(FOREST_TEMPLE_RED_POE_CHEST,  {[]{return CanUse(BOW);}}),
                  LocationAccess(FOREST_TEMPLE_BLUE_POE_CHEST, {[]{return CanUse(BOW);}}),
                }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_FALLING_ROOM, {[]{return SmallKeys(ForestTempleKeys, 5) && (Bow || CanUse(DINS_FIRE));}}),
  });

  areaTable[FOREST_TEMPLE_BOSS_REGION] = Area("Forest Temple Boss Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTempleClear, {[]{return ForestTempleClear || (BossKeyForestTemple);}}),
  }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_BASEMENT_CHEST,      {[]{return true;}}),
                  LocationAccess(FOREST_TEMPLE_PHANTOM_GANON_HEART, {[]{return BossKeyForestTemple;}}),
                  LocationAccess(PHANTOM_GANON,                     {[]{return BossKeyForestTemple;}}),
                  LocationAccess(FOREST_TEMPLE_GS_BASEMENT,         {[]{return HookshotOrBoomerang;}}),
  }, {});
  }

  if (Dungeon::FireTemple.IsVanilla()) {
  //Fire Temple logic currently assumes that the lowest locked door is unlocked from the start
  areaTable[FIRE_TEMPLE_LOWER] = Area("Fire Temple Lower", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot,        {[]{return FairyPot || ((CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT)) && (LogicFewerTunicRequirements || CanUse(GORON_TUNIC)));}}),
                  EventAccess(&FireTempleClear, {[]{return FireTempleClear || (CanUse(GORON_TUNIC) && CanUse(MEGATON_HAMMER) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  Here(FIRE_TEMPLE_UPPER, []{return CanPlay(SongOfTime) || HasExplosives;})));}}),
                }, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_NEAR_BOSS_CHEST,    {[]{return LogicFewerTunicRequirements || CanUse(GORON_TUNIC);}}),
                  LocationAccess(FIRE_TEMPLE_FLARE_DANCER_CHEST, {[]{return (SmallKeys(FireTempleKeys, 8) || !IsKeysanity) && CanUse(MEGATON_HAMMER);}}),
                  LocationAccess(FIRE_TEMPLE_BOSS_KEY_CHEST,     {[]{return (SmallKeys(FireTempleKeys, 8) || !IsKeysanity) && CanUse(MEGATON_HAMMER);},
                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}),
                  LocationAccess(FIRE_TEMPLE_VOLVAGIA_HEART,     {[]{return CanUse(GORON_TUNIC) && CanUse(MEGATON_HAMMER) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  Here(FIRE_TEMPLE_UPPER, []{return CanPlay(SongOfTime) || HasExplosives;}));}}),
                  LocationAccess(VOLVAGIA,                       {[]{return CanUse(GORON_TUNIC) && CanUse(MEGATON_HAMMER) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  Here(FIRE_TEMPLE_UPPER, []{return CanPlay(SongOfTime) || HasExplosives;}));}}),
                  LocationAccess(FIRE_TEMPLE_GS_BOSS_KEY_LOOP,   {[]{return (SmallKeys(FireTempleKeys, 8) || !IsKeysanity) && CanUse(MEGATON_HAMMER);}}),
                }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_ENTRYWAY,      {[]{return true;}}),
                  Entrance(FIRE_TEMPLE_BIG_LAVA_ROOM, {[]{return SmallKeys(FireTempleKeys, 2) && (LogicFewerTunicRequirements || CanUse(GORON_TUNIC));}}),
  });

  areaTable[FIRE_TEMPLE_BIG_LAVA_ROOM] = Area("Fire Temple Big Lava Room", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST, {[]{return true;}}),
                  LocationAccess(FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,    {[]{return IsAdult && HasExplosives;}}),
                  LocationAccess(FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,                {[]{return IsAdult && (CanPlay(SongOfTime) || LogicFireSongOfTime);}}),
                }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_LOWER,  {[]{return true;}}),
                  Entrance(FIRE_TEMPLE_MIDDLE, {[]{return CanUse(GORON_TUNIC) && SmallKeys(FireTempleKeys, 4) && (GoronBracelet || LogicFireStrength) && (HasExplosives || Bow || Hookshot);}}),
  });

  areaTable[FIRE_TEMPLE_MIDDLE] = Area("Fire Temple Middle", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,     {[]{return true;}}),
                  LocationAccess(FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,     {[]{return SmallKeys(FireTempleKeys, 6);}}),
                  LocationAccess(FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST, {[]{return true;}}),
                  LocationAccess(FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,  {[]{return SmallKeys(FireTempleKeys, 6) && HasExplosives;}}),
                  LocationAccess(FIRE_TEMPLE_SCARECROW_CHEST,              {[]{return SmallKeys(FireTempleKeys, 6) && (CanUse(SCARECROW) || (LogicFireScarecrow && CanUse(LONGSHOT)));}}),
                  LocationAccess(FIRE_TEMPLE_MAP_CHEST,                    {[]{return SmallKeys(FireTempleKeys, 6) || (SmallKeys(FireTempleKeys, 5) && CanUse(BOW));}}),
                  LocationAccess(FIRE_TEMPLE_COMPASS_CHEST,                {[]{return SmallKeys(FireTempleKeys, 7);}}),
                  LocationAccess(FIRE_TEMPLE_GS_BOULDER_MAZE,              {[]{return SmallKeys(FireTempleKeys, 4) && HasExplosives;}}),
                  LocationAccess(FIRE_TEMPLE_GS_SCARECROW_CLIMB,           {[]{return SmallKeys(FireTempleKeys, 6) && (CanUse(SCARECROW) || (LogicFireScarecrow && CanUse(LONGSHOT)));}}),
                  LocationAccess(FIRE_TEMPLE_GS_SCARECROW_TOP,             {[]{return SmallKeys(FireTempleKeys, 6) && (CanUse(SCARECROW) || (LogicFireScarecrow && CanUse(LONGSHOT)));}}),
                }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_UPPER, {[]{return SmallKeys(FireTempleKeys, 8) || (SmallKeys(FireTempleKeys, 7) && ((CanUse(HOVER_BOOTS) && CanUse(MEGATON_HAMMER)) || LogicFireFlameMaze));}}),
  });

  areaTable[FIRE_TEMPLE_UPPER] = Area("Fire Temple Upper", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_HIGHEST_GORON_CHEST,  {[]{return CanUse(MEGATON_HAMMER) && CanPlay(SongOfTime);}}),
                  LocationAccess(FIRE_TEMPLE_MEGATON_HAMMER_CHEST, {[]{return HasExplosives;}}),
  }, {});
  }

  if (Dungeon::WaterTemple.IsVanilla()) {
  //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
  areaTable[WATER_TEMPLE_LOBBY] = Area("Water Temple Lobby", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ChildWaterTemple, {[]{return IsChild;}}),
                  EventAccess(&RaiseWaterLevel,  {[]{return (IsAdult && ((Hookshot && (LogicWaterTempleUpperBoost && Bombs && CanTakeDamage)) || HoverBoots || Bow)) || (HasFireSourceWithTorch && CanUseProjectile);}}),
                }, {}, {
                  //Exits
                  Entrance(WATER_TEMPLE_ENTRYWAY,            {[]{return true;}}),
                  Entrance(WATER_TEMPLE_HIGHEST_WATER_LEVEL, {[]{return RaiseWaterLevel;}}),
                  Entrance(WATER_TEMPLE_DIVE,                {[]{return (CanUse(ZORA_TUNIC) || LogicFewerTunicRequirements) && ((LogicWaterTempleTorchLongshot && CanUse(LONGSHOT)) || CanUse(IRON_BOOTS));}}),
  });

  areaTable[WATER_TEMPLE_HIGHEST_WATER_LEVEL] = Area("Water Temple Highest Water Level", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot,         {[]{return FairyPot         || CanUse(LONGSHOT);}}),
                  EventAccess(&WaterTempleClear, {[]{return WaterTempleClear || (BossKeyWaterTemple && CanUse(LONGSHOT));}}),
                }, {
                  //Locations
                  LocationAccess(MORPHA,                    {[]{return BossKeyWaterTemple && CanUse(LONGSHOT);}}),
                  LocationAccess(WATER_TEMPLE_MORPHA_HEART, {[]{return BossKeyWaterTemple && CanUse(LONGSHOT);}}),
                }, {
                  //Exits
                  Entrance(WATER_TEMPLE_FALLING_PLATFORM_ROOM, {[]{return SmallKeys(WaterTempleKeys, 4);}}),

  });

  areaTable[WATER_TEMPLE_DIVE] = Area("Water Temple Dive", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_MAP_CHEST,                {[]{return RaiseWaterLevel;}}),
                  LocationAccess(WATER_TEMPLE_COMPASS_CHEST,            {[]{return (CanPlay(ZeldasLullaby) || IronBoots) && CanUse(HOOKSHOT);}}),
                  LocationAccess(WATER_TEMPLE_TORCHES_CHEST,            {[]{return (Bow || CanUse(DINS_FIRE) || (ChildWaterTemple && Sticks && KokiriSword && MagicMeter)) && CanPlay(ZeldasLullaby);}}),
                  LocationAccess(WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST, {[]{return GoronBracelet && CanPlay(ZeldasLullaby) &&
                                                                                    ((Bow && (LogicWaterCentralBow || HoverBoots || CanUse(LONGSHOT))) ||
                                                                                      (LogicWaterCentralBow && ChildWaterTemple && Slingshot && HasAccessTo(WATER_TEMPLE_MIDDLE_WATER_LEVEL)));}}),
                  LocationAccess(WATER_TEMPLE_GS_BEHIND_GATE,           {[]{return (CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS)) &&
                                                                                    (HasExplosives && CanPlay(ZeldasLullaby)) &&
                                                                                    (CanUse(IRON_BOOTS) || CanDive);}}),
                  LocationAccess(WATER_TEMPLE_GS_CENTRAL_PILLAR,        {[]{return CanPlay(ZeldasLullaby) &&
                                                                                      (((CanUse(LONGSHOT) || (LogicWaterCentralGSFW && CanUse(HOOKSHOT) && CanUse(FARORES_WIND))) &&
                                                                                        (SmallKeys(WaterTempleKeys, 5) || CanUse(BOW) || CanUse(DINS_FIRE))) ||
                                                                                      (LogicWaterCentralGSFW && ChildWaterTemple && Boomerang && CanUse(FARORES_WIND) &&
                                                                                        (Sticks || CanUse(DINS_FIRE) ||
                                                                                        (SmallKeys(WaterTempleKeys, 5) && (CanUse(HOVER_BOOTS) || CanUse(BOW))))));}}),
                }, {
                  //Exits
                  Entrance(WATER_TEMPLE_CRACKED_WALL,       {[]{return CanPlay(ZeldasLullaby) && (CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS)) && (LogicWaterCrackedWallNothing || (LogicWaterCrackedWallHovers && CanUse(HOVER_BOOTS)));}}),
                  Entrance(WATER_TEMPLE_MIDDLE_WATER_LEVEL, {[]{return (Bow || CanUse(DINS_FIRE) || (SmallKeys(WaterTempleKeys, 5) && CanUse(HOOKSHOT)) || (ChildWaterTemple && Sticks)) && CanPlay(ZeldasLullaby);}}),
                  Entrance(WATER_TEMPLE_NORTH_BASEMENT,     {[]{return SmallKeys(WaterTempleKeys, 5) && (CanUse(LONGSHOT) || (LogicWaterBossKeyRegion && CanUse(HOVER_BOOTS))) && (CanUse(IRON_BOOTS) || CanPlay(ZeldasLullaby));}}),
                  Entrance(WATER_TEMPLE_DRAGON_STATUE,      {[]{return CanPlay(ZeldasLullaby) && GoronBracelet &&
                                                                                ((IronBoots && CanUse(HOOKSHOT)) ||
                                                                                (LogicWaterDragonAdult && (HasBombchus || CanUse(BOW) || CanUse(HOOKSHOT)) && (CanDive || IronBoots)));}}),
  });

  areaTable[WATER_TEMPLE_NORTH_BASEMENT] = Area("Water Temple North Basement", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse(IRON_BOOTS)) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots));}}),
                }, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_BOSS_KEY_CHEST,         {[]{return SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse(IRON_BOOTS)) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots);}}),
                  LocationAccess(WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST, {[]{return true;}}),
  }, {});

  areaTable[WATER_TEMPLE_CRACKED_WALL] = Area("Water Temple Cracked Wall", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_CRACKED_WALL_CHEST, {[]{return HasExplosives;}}),
  }, {});

  areaTable[WATER_TEMPLE_DRAGON_STATUE] = Area("Water Temple Dragon Statue", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_DRAGON_CHEST, {[]{return true;}}),
  }, {});

  areaTable[WATER_TEMPLE_MIDDLE_WATER_LEVEL] = Area("Water Temple Middle Water Level", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_CENTRAL_PILLAR_CHEST, {[]{return CanUse(ZORA_TUNIC) && CanUse(HOOKSHOT) && CanUse(IRON_BOOTS) && ((SmallKeys(WaterTempleKeys, 5) || CanUse(BOW) || CanUse(DINS_FIRE)));}}),
                }, {
                  //Exits
                  Entrance(WATER_TEMPLE_CRACKED_WALL, {[]{return true;}}),
  });

  areaTable[WATER_TEMPLE_FALLING_PLATFORM_ROOM] = Area("Water Temple Falling Platform Room", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM, {[]{return CanUse(LONGSHOT) || (LogicWaterFallingPlatformGS && CanUse(HOOKSHOT));}}),
                }, {
                  //Exits
                  Entrance(WATER_TEMPLE_DARK_LINK_REGION, {[]{return SmallKeys(WaterTempleKeys, 5) && CanUse(HOOKSHOT);}}),
  });

  areaTable[WATER_TEMPLE_DARK_LINK_REGION] = Area("Water Temple Dark Link Region", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime));}}),
                }, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_LONGSHOT_CHEST, {[]{return SmallKeys(WaterTempleKeys, 5);}}),
                  LocationAccess(WATER_TEMPLE_RIVER_CHEST,    {[]{return SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime) && Bow;}}),
                  LocationAccess(WATER_TEMPLE_GS_RIVER,       {[]{return CanPlay(SongOfTime) && SmallKeys(WaterTempleKeys, 5) && (IronBoots || (LogicWaterRiverGS && CanUse(LONGSHOT) && (Bow || HasBombchus)));}}),
                }, {
                  //Exits
                  Entrance(WATER_TEMPLE_DRAGON_STATUE, {[]{return (CanUse(ZORA_TUNIC) || LogicFewerTunicRequirements) &&
                                                                         CanPlay(SongOfTime) && Bow &&
                                                                         (IronBoots || LogicWaterDragonJumpDive || LogicWaterDragonAdult);}}),
  });
  }

  if (Dungeon::SpiritTemple.IsVanilla()) {
  areaTable[SPIRIT_TEMPLE_LOBBY] = Area("Spirit Temple Lobby", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_ENTRYWAY,    {[]{return true;}}),
                  Entrance(SPIRIT_TEMPLE_CHILD,       {[]{return IsChild;}}),
                  Entrance(SPIRIT_TEMPLE_EARLY_ADULT, {[]{return CanUse(SILVER_GAUNTLETS);}}),
  });

  areaTable[SPIRIT_TEMPLE_CHILD] = Area("Child Spirit Temple", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutCrate, {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,        {[]{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (HasExplosives || ((Nuts || Boomerang) && (Sticks || KokiriSword || Slingshot)));}}),
                  LocationAccess(SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST, {[]{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (HasExplosives || ((Nuts || Boomerang) && (Sticks || KokiriSword || Slingshot))) && (Sticks || CanUse(DINS_FIRE));}}),
                  LocationAccess(SPIRIT_TEMPLE_GS_METAL_FENCE,            {[]{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (HasExplosives || ((Nuts || Boomerang) && (Sticks || KokiriSword || Slingshot)));}}),
                }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_CHILD_CLIMB, {[]{return SmallKeys(SpiritTempleKeys, 1);}}),
  });

  areaTable[SPIRIT_TEMPLE_CHILD_CLIMB] = Area("Child Spirit Temple Climb", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST, {[]{return HasProjectile(HasProjectileAge::Both) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))) && CanUse(SILVER_GAUNTLETS) && HasProjectile(HasProjectileAge::Adult)) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile(HasProjectileAge::Child));}}),
                  LocationAccess(SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,  {[]{return HasProjectile(HasProjectileAge::Both) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))) && CanUse(SILVER_GAUNTLETS) && HasProjectile(HasProjectileAge::Adult)) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile(HasProjectileAge::Child));}}),
                  LocationAccess(SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,    {[]{return HasProjectile(HasProjectileAge::Both) || CanUse(DINS_FIRE) ||
                                                                                      (CanTakeDamage && (Sticks || KokiriSword || HasProjectile(HasProjectileAge::Child))) ||
                                                                                        (IsChild && SmallKeys(SpiritTempleKeys, 5) && HasProjectile(HasProjectileAge::Child)) ||
                                                                                          ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))) && CanUse(SILVER_GAUNTLETS) && (HasProjectile(HasProjectileAge::Adult) || CanTakeDamage));}}),
                }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_CENTRAL_CHAMBER, {[]{return HasExplosives;}}),
  });

  areaTable[SPIRIT_TEMPLE_EARLY_ADULT] = Area("Early Adult Spirit Temple", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_COMPASS_CHEST,            {[]{return CanUse(HOOKSHOT) && CanPlay(ZeldasLullaby);}}),
                  LocationAccess(SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,  {[]{return Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch);}}),
                  LocationAccess(SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,  {[]{return SmallKeys(SpiritTempleKeys, 3);}}),
                  LocationAccess(SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST, {[]{return SmallKeys(SpiritTempleKeys, 3);}}),
                  LocationAccess(SPIRIT_TEMPLE_GS_BOULDER_ROOM,          {[]{return CanPlay(SongOfTime) && (Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch));}}),
                }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_CENTRAL_CHAMBER, {[]{return SmallKeys(SpiritTempleKeys, 1);}}),
  });

  areaTable[SPIRIT_TEMPLE_CENTRAL_CHAMBER] = Area("Spirit Temple Central Chamber", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MAP_CHEST,                    {[]{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))) &&
                                                                                                (CanUse(DINS_FIRE) ||
                                                                                                    (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 5) && HasExplosives &&
                                                                                                CanUse(STICKS)) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 3) &&
                                                                                                (CanUse(FIRE_ARROWS) || (LogicSpiritMapChest && Bow)) &&
                                                                                                CanUse(SILVER_GAUNTLETS));}}),
                  LocationAccess(SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,         {[]{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))) &&
                                                                                                (CanUse(DINS_FIRE) ||
                                                                                                    (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 5) && HasExplosives &&
                                                                                                CanUse(STICKS)) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 3) &&
                                                                                                (CanUse(FIRE_ARROWS) || (LogicSpiritMapChest && Bow)) &&
                                                                                                CanUse(SILVER_GAUNTLETS));}}),
                  LocationAccess(SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,       {[]{return SmallKeys(SpiritTempleKeys, 3) && CanUse(SILVER_GAUNTLETS) && CanPlay(ZeldasLullaby);}}),
                  LocationAccess(SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,  {[]{return SmallKeys(SpiritTempleKeys, 3) && CanUse(SILVER_GAUNTLETS) && CanPlay(ZeldasLullaby) && (Hookshot || HoverBoots);}}),
                  LocationAccess(SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM, {[]{return (HasExplosives && Boomerang && Hookshot) ||
                                                                                            (CanUse(BOOMERANG) && SmallKeys(SpiritTempleKeys, 5) && HasExplosives) ||
                                                                                            (Hookshot && CanUse(SILVER_GAUNTLETS) &&
                                                                                                (SmallKeys(SpiritTempleKeys, 3) ||
                                                                                                    (SmallKeys(SpiritTempleKeys, 2) && Boomerang && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))));}}),
                  LocationAccess(SPIRIT_TEMPLE_GS_LOBBY,                     {[]{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF))) &&
                                                                                                LogicSpiritLobbyGS && Boomerang && (Hookshot || HoverBoots)) ||
                                                                                            (LogicSpiritLobbyGS && SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse(BOOMERANG)) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 3) && CanUse(SILVER_GAUNTLETS) && (Hookshot || HoverBoots));}}),
                }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_OUTDOOR_HANDS,              {[]{return true;}}),
                  Entrance(SPIRIT_TEMPLE_BEYOND_CENTRAL_LOCKED_DOOR, {[]{return SmallKeys(SpiritTempleKeys, 4) && CanUse(SILVER_GAUNTLETS);}}),
                  Entrance(SPIRIT_TEMPLE_CHILD_CLIMB,                {[]{return true;}}),
  });

  areaTable[SPIRIT_TEMPLE_OUTDOOR_HANDS] = Area("Spirit Temple Outdoor Hands", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, {[]{return (SmallKeys(SpiritTempleKeys, 3) && Longshot && HasExplosives) || SmallKeys(SpiritTempleKeys, 5);}}),
                  LocationAccess(SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,    {[]{return SmallKeys(SpiritTempleKeys, 4) && CanUse(SILVER_GAUNTLETS) && HasExplosives;}}),
                }, {
                  //Exits
                  Entrance(DESERT_COLOSSUS, {[]{return (IsChild && SmallKeys(SpiritTempleKeys, 5)) || (CanUse(SILVER_GAUNTLETS) && ((SmallKeys(SpiritTempleKeys, 3) && HasExplosives) || SmallKeys(SpiritTempleKeys, 5)));}}),
  });

  areaTable[SPIRIT_TEMPLE_BEYOND_CENTRAL_LOCKED_DOOR] = Area("Spirit Temple Beyond Central Locked Door", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,         {[]{return MirrorShield && HasExplosives;}}),
                  LocationAccess(SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,  {[]{return (LogicLensSpirit || CanUse(LENS_OF_TRUTH)) && HasExplosives;}}),
                  LocationAccess(SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST, {[]{return (LogicLensSpirit || CanUse(LENS_OF_TRUTH)) && HasExplosives;}}),
                }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_BEYOND_FINAL_LOCKED_DOOR, {[]{return SmallKeys(SpiritTempleKeys, 5) && (LogicSpiritWall || CanUse(LONGSHOT) || HasBombchus || ((Bombs || Nuts || CanUse(DINS_FIRE)) && (Bow || CanUse(HOOKSHOT) || Hammer)));}}),
  });

  areaTable[SPIRIT_TEMPLE_BEYOND_FINAL_LOCKED_DOOR] = Area("Spirit Temple Beyond Final Locked Door", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&SpiritTempleClear, {[]{return SpiritTempleClear || (MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple);}}),
  }, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_BOSS_KEY_CHEST, {[]{return CanPlay(ZeldasLullaby) && ((CanTakeDamage && LogicFlamingChests) || (Bow && Hookshot));}}),
                  LocationAccess(SPIRIT_TEMPLE_TOPMOST_CHEST,  {[]{return MirrorShield;}}),
                  LocationAccess(SPIRIT_TEMPLE_TWINROVA_HEART, {[]{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}}),
                  LocationAccess(TWINROVA,                     {[]{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}}),
  }, {});
  }

  if (Dungeon::ShadowTemple.IsVanilla()) {
  areaTable[SHADOW_TEMPLE_BEGINNING] = Area("Shadow Temple Beginning", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot, {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MAP_CHEST,         {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_HOVER_BOOTS_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_ENTRYWAY,     {[]{return true;}}),
                  Entrance(SHADOW_TEMPLE_FIRST_BEAMOS, {[]{return HoverBoots;},
                                            /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}),
  });

  areaTable[SHADOW_TEMPLE_FIRST_BEAMOS] = Area("Shadow Temple First Beamos", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}), //This fairy pot is only on 3DS
                }, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_COMPASS_CHEST,            {[]{return IsAdult || KokiriSword || Sticks;}}),
                  LocationAccess(SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST, {[]{return CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT);}}),
                  LocationAccess(SHADOW_TEMPLE_GS_NEAR_SHIP,             {[]{return false;},
                                                              /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) && Longshot;}}),
                }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_HUGE_PIT,    {[]{return HasExplosives && IsAdult && SmallKeys_ShadowTemple(ShadowTempleKeys, 1, 2);}}),
                  Entrance(SHADOW_TEMPLE_BEYOND_BOAT, {[]{return false;},
                                           /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) && Longshot && CanPlay(ZeldasLullaby);}}),
  });

  areaTable[SHADOW_TEMPLE_HUGE_PIT] = Area("Shadow Temple Huge Pit", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,   {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST, {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,       {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,       {[]{return LogicShadowUmbrella || GoronBracelet;}}),
                  LocationAccess(SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,      {[]{return LogicShadowUmbrella || GoronBracelet;}}),
                  LocationAccess(SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,           {[]{return SmallKeys_ShadowTemple(ShadowTempleKeys, 2, 3) && (LogicLensShadowBack || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(SHADOW_TEMPLE_FREESTANDING_KEY,                 {[]{return SmallKeys_ShadowTemple(ShadowTempleKeys, 2, 3) && (LogicLensShadowBack || CanUse(LENS_OF_TRUTH)) && Hookshot && (Bombs || GoronBracelet || (LogicShadowFreestandingKey && HasBombchus));}}),
                  LocationAccess(SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,                {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,           {[]{return Hookshot;}}),
                  LocationAccess(SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,              {[]{return SmallKeys_ShadowTemple(ShadowTempleKeys, 2, 3) && (LogicLensShadowBack || CanUse(LENS_OF_TRUTH)) && Hookshot;}}),
                }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_WIND_TUNNEL, {[]{return (LogicLensShadowBack || CanUse(LENS_OF_TRUTH)) && Hookshot && SmallKeys_ShadowTemple(ShadowTempleKeys, 3, 4);}}),
  });

  areaTable[SHADOW_TEMPLE_WIND_TUNNEL] = Area("Shadow Temple Wind Tunnel", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_WIND_HINT_CHEST,         {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,  {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST, {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_GS_NEAR_SHIP,            {[]{return CanUse(LONGSHOT) && SmallKeys_ShadowTemple(ShadowTempleKeys, 4, 5);}}),
                }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_BEYOND_BOAT, {[]{return CanPlay(ZeldasLullaby) && SmallKeys_ShadowTemple(ShadowTempleKeys, 4, 5);}}),
  });

  areaTable[SHADOW_TEMPLE_BEYOND_BOAT] = Area("Shadow Temple Beyond Boat", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ShadowTempleClear, {[]{return ShadowTempleClear || (SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(DISTANT_SCARECROW) || (LogicShadowStatue && HasBombchus)));}}),
  }, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,      {[]{return CanUse(DINS_FIRE);}}),
                  LocationAccess(SHADOW_TEMPLE_BOSS_KEY_CHEST,              {[]{return CanUse(DINS_FIRE);}}),
                  LocationAccess(SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST, {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_BONGO_BONGO_HEART,           {[]{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(DISTANT_SCARECROW) || (LogicShadowStatue && HasBombchus));}}),
                  LocationAccess(BONGO_BONGO,                               {[]{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(DISTANT_SCARECROW) || (LogicShadowStatue && HasBombchus));}}),
                  LocationAccess(SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,         {[]{return true;}}),
  }, {});
  }

  if (Dungeon::BottomOfTheWell.IsVanilla()) {
  areaTable[BOTTOM_OF_THE_WELL_MAIN_AREA] = Area("Bottom of the Well Main Area", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&StickPot, {[]{return true;}}),
                  EventAccess(&NutPot,   {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,   {[]{return LogicLensBotw || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST,  {[]{return HasExplosives;}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST, {[]{return LogicLensBotw || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_COMPASS_CHEST,                {[]{return LogicLensBotw || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,       {[]{return LogicLensBotw || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,     {[]{return (LogicLensBotw || CanUse(LENS_OF_TRUTH)) && HasExplosives;}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_FREESTANDING_KEY,             {[]{return Sticks || CanUse(DINS_FIRE);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,          {[]{return CanPlay(ZeldasLullaby) && (KokiriSword || (Sticks && LogicChildDeadhand));}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,              {[]{return CanPlay(ZeldasLullaby) && (LogicLensBotw || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,       {[]{return CanPlay(ZeldasLullaby);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,        {[]{return CanPlay(ZeldasLullaby);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_MAP_CHEST,                    {[]{return HasExplosives || (((SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(LENS_OF_TRUTH))) || CanUse(DINS_FIRE)) && GoronBracelet);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,             {[]{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,              {[]{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,           {[]{return Boomerang && (LogicLensBotw || CanUse(LENS_OF_TRUTH)) && SmallKeys(BottomOfTheWellKeys, 3);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,           {[]{return Boomerang && (LogicLensBotw || CanUse(LENS_OF_TRUTH)) && SmallKeys(BottomOfTheWellKeys, 3);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,            {[]{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(LENS_OF_TRUTH)) && Boomerang;}}),
                }, {
                  //Exits
                  Entrance(BOTTOM_OF_THE_WELL_ENTRYWAY, {[]{return true;}}),
  });
  }

  if (Dungeon::IceCavern.IsVanilla()) {
  areaTable[ICE_CAVERN_BEGINNING] = Area("Ice Cavern Beginning", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(ICE_CAVERN_ENTRYWAY, {[]{return true;}}),
                  Entrance(ICE_CAVERN_MAIN,     {[]{return Here(ICE_CAVERN_BEGINNING, []{return IsAdult || HasExplosives || CanUse(DINS_FIRE);});}}),
  });

  areaTable[ICE_CAVERN_MAIN] = Area("Ice Cavern", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BlueFireAccess, {[]{return BlueFireAccess || (IsAdult && HasBottle);}}),
                }, {
                  //Locations
                  LocationAccess(ICE_CAVERN_MAP_CHEST,               {[]{return BlueFire && IsAdult;}}),
                  LocationAccess(ICE_CAVERN_COMPASS_CHEST,           {[]{return BlueFire;}}),
                  LocationAccess(ICE_CAVERN_IRON_BOOTS_CHEST,        {[]{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse(DINS_FIRE));}}),
                  LocationAccess(SHEIK_IN_ICE_CAVERN,                {[]{return BlueFire && IsAdult;}}),
                  LocationAccess(ICE_CAVERN_FREESTANDING_POH,        {[]{return BlueFire;}}),
                  LocationAccess(ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM, {[]{return HookshotOrBoomerang;}}),
                  LocationAccess(ICE_CAVERN_GS_HEART_PIECE_ROOM,     {[]{return BlueFire && HookshotOrBoomerang;}}),
                  LocationAccess(ICE_CAVERN_GS_PUSH_BLOCK_ROOM,      {[]{return BlueFire && HookshotOrBoomerang;}}),
  }, {});
  }

  if (Dungeon::GerudoTrainingGrounds.IsVanilla()) {
  areaTable[GERUDO_TRAINING_GROUNDS_LOBBY] = Area("Gerudo Training Grounds Lobby", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST,  {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST, {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_STALFOS_CHEST,     {[]{return IsAdult || KokiriSword;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST,      {[]{return HasExplosives && (IsAdult || KokiriSword);}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_ENTRYWAY,         {[]{return true;}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_ROOM, {[]{return (IsAdult || KokiriSword) && (CanUse(HOOKSHOT) || LogicGtgWithoutHookshot);}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_LAVA_ROOM,        {[]{return Here(GERUDO_TRAINING_GROUNDS_LOBBY, []{return (IsAdult || KokiriSword) && HasExplosives;});}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE,     {[]{return true;}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE] = Area("Gerudo Training Grounds Central Maze", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST,   {[]{return SmallKeys(GerudoTrainingGroundsKeys, 3) && (LogicLensGtg || CanUse(LENS_OF_TRUTH));},
                                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) && (LogicLensGtg || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST,  {[]{return SmallKeys(GerudoTrainingGroundsKeys, 4);},
                                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST, {[]{return SmallKeys(GerudoTrainingGroundsKeys, 6);},
                                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST,  {[]{return SmallKeys(GerudoTrainingGroundsKeys, 7);},
                                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST,  {[]{return SmallKeys(GerudoTrainingGroundsKeys, 9);},
                                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE_RIGHT, {[]{return SmallKeys(GerudoTrainingGroundsKeys, 9);},
                                                            /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE_RIGHT] = Area("Gerudo Training Grounds Central Maze Right", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST, {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST,    {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY,         {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM, {[]{return CanUse(HOOKSHOT);}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_LAVA_ROOM,   {[]{return true;}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_LAVA_ROOM] = Area("Gerudo Training Grounds Lava Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST, {[]{return CanUse(HOOKSHOT) && CanPlay(SongOfTime) && IronBoots && (LogicFewerTunicRequirements || CanUse(ZORA_TUNIC));}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE_RIGHT, {[]{return CanPlay(SongOfTime) || IsChild;}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM,        {[]{return CanUse(LONGSHOT)  || (CanUse(HOVER_BOOTS) && CanUse(HOOKSHOT));}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM] = Area("Gerudo Training Grounds Hammer Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST,  {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST, {[]{return CanUse(MEGATON_HAMMER) || (CanTakeDamage && LogicFlamingChests);}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_EYE_STATUE_LOWER, {[]{return CanUse(MEGATON_HAMMER) && Bow;}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_LAVA_ROOM,        {[]{return true;}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_EYE_STATUE_LOWER] = Area("Gerudo Training Grounds Eye Statue Lower", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST, {[]{return CanUse(BOW);}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM, {[]{return true;}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_EYE_STATUE_UPPER] = Area("Gerudo Training Grounds Eye Statue Upper", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST, {[]{return CanUse(BOW);}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_EYE_STATUE_LOWER, {[]{return true;}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_ROOM] = Area("Gerudo Training Grounds Heavy Block Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST, {[]{return true;}}),
                }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_EYE_STATUE_UPPER, {[]{return (LogicLensGtg || CanUse(LENS_OF_TRUTH)) && (CanUse(HOOKSHOT) || (LogicGtgFakeWall && CanUse(HOVER_BOOTS)));}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_LIKE_LIKE_ROOM,   {[]{return (LogicLensGtg || CanUse(LENS_OF_TRUTH)) && (CanUse(HOOKSHOT) || (LogicGtgFakeWall && CanUse(HOVER_BOOTS))) && CanUse(SILVER_GAUNTLETS);}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_LIKE_LIKE_ROOM] = Area("Gerudo Training Grounds Like Like Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST,  {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST, {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST,  {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST, {[]{return true;}}),
  }, {});
  }

  if (Dungeon::GanonsCastle.IsVanilla()) {
  areaTable[GANONS_CASTLE_LOBBY] = Area("Ganon's Castle Lobby", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GANONS_CASTLE_ENTRYWAY,     {[]{return true;}}),
                  Entrance(GANONS_CASTLE_FOREST_TRIAL, {[]{return true;}}),
                  Entrance(GANONS_CASTLE_FIRE_TRIAL,   {[]{return true;}}),
                  Entrance(GANONS_CASTLE_WATER_TRIAL,  {[]{return true;}}),
                  Entrance(GANONS_CASTLE_SHADOW_TRIAL, {[]{return true;}}),
                  Entrance(GANONS_CASTLE_SPIRIT_TRIAL, {[]{return true;}}),
                  Entrance(GANONS_CASTLE_LIGHT_TRIAL,  {[]{return CanUse(GOLDEN_GAUNTLETS);}}),
                  Entrance(GANONS_CASTLE_TOWER,        {[]{return (ForestTrialClear || Trial::ForestTrial.IsSkipped()) &&
                                                                         (FireTrialClear   || Trial::FireTrial.IsSkipped())   &&
                                                                         (WaterTrialClear  || Trial::WaterTrial.IsSkipped())  &&
                                                                         (ShadowTrialClear || Trial::ShadowTrial.IsSkipped()) &&
                                                                         (SpiritTrialClear || Trial::SpiritTrial.IsSkipped()) &&
                                                                         (LightTrialClear  || Trial::LightTrial.IsSkipped());}}),
                  Entrance(GANONS_CASTLE_DEKU_SCRUBS,  {[]{return LogicLensCastle || CanUse(LENS_OF_TRUTH);}}),
  });

  areaTable[GANONS_CASTLE_DEKU_SCRUBS] = Area("Ganon's Castle Deku Scrubs", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FreeFairies, {[]{return true;}}),
                }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,  {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT, {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_DEKU_SCRUB_RIGHT,        {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_DEKU_SCRUB_LEFT,         {[]{return CanStunDeku;}}),
  }, {});

  areaTable[GANONS_CASTLE_FOREST_TRIAL] = Area("Ganon's Castle Forest Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTrialClear, {[]{return CanUse(LIGHT_ARROWS) && (FireArrows || DinsFire);}}),
                }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_FOREST_TRIAL_CHEST, {[]{return IsAdult || CanChildDamage;}}),
  }, {});

  areaTable[GANONS_CASTLE_FIRE_TRIAL] = Area("Ganon's Castle Fire Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FireTrialClear, {[]{return CanUse(GORON_TUNIC) && CanUse(GOLDEN_GAUNTLETS) && CanUse(LIGHT_ARROWS) && CanUse(LONGSHOT);}}),
  }, {}, {});

  areaTable[GANONS_CASTLE_WATER_TRIAL] = Area("Ganon's Castle Water Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BlueFireAccess,  {[]{return BlueFireAccess || HasBottle;}}),
                  EventAccess(&FairyPot,        {[]{return FairyPot || BlueFire;}}),
                  EventAccess(&WaterTrialClear, {[]{return BlueFire && Hammer && CanUse(LIGHT_ARROWS);}}),
                }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,  {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST, {[]{return true;}}),
  }, {});

  areaTable[GANONS_CASTLE_SHADOW_TRIAL] = Area("Ganon's Castle Shadow Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ShadowTrialClear, {[]{return CanUse(LIGHT_ARROWS) && Hammer && ((FireArrows && (LogicLensCastle || CanUse(LENS_OF_TRUTH))) || (CanUse(LONGSHOT) && (CanUse(HOVER_BOOTS) || (DinsFire && (LogicLensCastle || CanUse(LENS_OF_TRUTH))))));}}),
                }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,            {[]{return CanUse(FIRE_ARROWS) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || CanPlay(SongOfTime) || IsChild;}}),
                  LocationAccess(GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST, {[]{return CanUse(FIRE_ARROWS) || (CanUse(LONGSHOT) && (CanUse(HOVER_BOOTS) || CanUse(DINS_FIRE)));}}),
  }, {});

  areaTable[GANONS_CASTLE_SPIRIT_TRIAL] = Area("Ganon's Castle Spirit Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot,           {[]{return NutPot || ((LogicSpiritTrialHookshot || CanUse(HOOKSHOT)) && HasBombchus && Bow && MirrorShield && IsAdult);}}),
                  EventAccess(&SpiritTrialClear, {[]{return CanUse(LIGHT_ARROWS)  && MirrorShield && HasBombchus && (LogicSpiritTrialHookshot || CanUse(HOOKSHOT));}}),
                }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST, {[]{return LogicSpiritTrialHookshot || CanUse(HOOKSHOT);}}),
                  LocationAccess(GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,      {[]{return (LogicSpiritTrialHookshot || CanUse(HOOKSHOT)) && HasBombchus && (LogicLensCastle || CanUse(LENS_OF_TRUTH));}}),
  }, {});

  areaTable[GANONS_CASTLE_LIGHT_TRIAL] = Area("Ganon's Castle Light Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&LightTrialClear, {[]{return CanUse(LIGHT_ARROWS) && CanUse(HOOKSHOT) && SmallKeys(GanonsCastleKeys, 2) && (LogicLensCastle || CanUse(LENS_OF_TRUTH));}}),
                }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,        {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,       {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,        {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,       {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,      {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,       {[]{return true;}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST, {[]{return LogicLensCastle || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,           {[]{return CanPlay(ZeldasLullaby) && SmallKeys(GanonsCastleKeys, 1);}}),
  }, {});
  }

  areaTable[GANONS_CASTLE_TOWER] = Area("Ganon's Castle Tower", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GANONS_TOWER_BOSS_KEY_CHEST, {[]{return true;}}),
                  LocationAccess(GANONDORF_HINT,              {[]{return BossKeyGanonsCastle;}}),
                  LocationAccess(GANON,                       {[]{return BossKeyGanonsCastle && CanUse(LIGHT_ARROWS);}}),
  }, {});

  /*---------------------------
  |   MASTER QUEST DUNGEONS   |
  ---------------------------*/
  if (Dungeon::DekuTree.IsMQ()) {
  areaTable[DEKU_TREE_MQ_LOBBY] = Area("Deku Tree MQ Lobby", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks, {[]{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}}),
                  EventAccess(&DekuBabaNuts,   {[]{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(DINS_FIRE));}}),
  }, {
                  //Locations
                  LocationAccess(DEKU_TREE_MQ_MAP_CHEST,                 {[]{return true;}}),
                  LocationAccess(DEKU_TREE_MQ_SLINGSHOT_CHEST,           {[]{return IsAdult || CanChildAttack;}}),
                  LocationAccess(DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST, {[]{return HasFireSourceWithTorch || CanUse(BOW);}}),
                  LocationAccess(DEKU_TREE_MQ_BASEMENT_CHEST,            {[]{return HasFireSourceWithTorch || CanUse(BOW);}}),
                  LocationAccess(DEKU_TREE_MQ_GS_LOBBY,                  {[]{return IsAdult || CanChildAttack;}}),
  }, {
                  //Exits
                  Entrance(DEKU_TREE_ENTRYWAY,                     {[]{return true;}}),
                  Entrance(DEKU_TREE_MQ_COMPASS_ROOM,              {[]{return Here(DEKU_TREE_MQ_LOBBY, []{return CanUse(SLINGSHOT) || CanUse(BOW);}) &&
                                                                               Here(DEKU_TREE_MQ_LOBBY, []{return HasFireSourceWithTorch || CanUse(BOW);});}}),
                  Entrance(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, {[]{return Here(DEKU_TREE_MQ_LOBBY, []{return CanUse(SLINGSHOT) || CanUse(BOW);}) &&
                                                                               Here(DEKU_TREE_MQ_LOBBY, []{return HasFireSourceWithTorch;});}}),
                  Entrance(DEKU_TREE_MQ_BASEMENT_LEDGE,            {[]{return LogicDekuB1Skip || Here(DEKU_TREE_MQ_LOBBY, []{return IsAdult;});}}),
  });

  areaTable[DEKU_TREE_MQ_COMPASS_ROOM] = Area("Deku Tree MQ Compass Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_TREE_MQ_COMPASS_CHEST,   {[]{return true;}}),
                  LocationAccess(DEKU_TREE_MQ_GS_COMPASS_ROOM, {[]{return HookshotOrBoomerang &&
                                                                               Here(DEKU_TREE_MQ_COMPASS_ROOM, []{return HasBombchus ||
                                                                               (Bombs && (CanPlay(SongOfTime) || IsAdult)) ||
                                                                               (CanUse(MEGATON_HAMMER) && (CanPlay(SongOfTime) /*|| LogicDekuMQCompassGS*/));});}}),
  }, {
                  //Exits
                  Entrance(DEKU_TREE_MQ_LOBBY, {[]{return true;}}),
  });

  areaTable[DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT] = Area("Deku Tree MQ Basement Water Room Front", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, {[]{return /*LogicDekuMQLog || */ (IsChild && (DekuShield || HylianShield)) ||
                                                                             CanUse(LONGSHOT) || (CanUse(HOOKSHOT) && CanUse(IRON_BOOTS));}}),
                  Entrance(DEKU_TREE_MQ_LOBBY,                    {[]{return true;}}),
  });

  areaTable[DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK] = Area("Deku Tree MQ Basement Water Room Front", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST, {[]{return CanPlay(SongOfTime);}}),
  }, {
                  //Exits
                  Entrance(DEKU_TREE_MQ_BASEMENT_BACK_ROOM,        {[]{return Here(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, []{return CanUse(STICKS) || CanUse(DINS_FIRE) ||
                                                                               Here(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, []{return CanUse(FIRE_ARROWS);});}) &&
                                                                                 Here(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, []{return IsAdult || KokiriSword || CanUseProjectile || (Nuts && Sticks);});}}),
                  Entrance(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, {[]{return true;}}),
  });

  areaTable[DEKU_TREE_MQ_BASEMENT_BACK_ROOM] = Area("Deku Tree MQ Basement Back Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM, {[]{return CanUse(LONGSHOT) || (CanPlay(SongOfTime) && HookshotOrBoomerang);}}),
                  LocationAccess(DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,   {[]{return HasFireSourceWithTorch && HookshotOrBoomerang;}}),
  }, {
                  //Exits
                  Entrance(DEKU_TREE_MQ_BASEMENT_LEDGE,           {[]{return IsChild;}}),
                  Entrance(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, {[]{return CanUse(KOKIRI_SWORD) || CanUseProjectile || (Nuts && CanUse(STICKS));}}),
  });

  areaTable[DEKU_TREE_MQ_BASEMENT_LEDGE] = Area("Deku Tree MQ Basement Ledge", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuTreeClear, {[]{return DekuTreeClear || (Here(DEKU_TREE_MQ_BASEMENT_LEDGE, []{return HasFireSourceWithTorch;}) &&
                                                                           Here(DEKU_TREE_MQ_BASEMENT_LEDGE, []{return HasShield;})  &&
                                                                           (IsAdult || KokiriSword || Sticks) && (Nuts || CanUse(SLINGSHOT) || CanUse(BOW) || HookshotOrBoomerang));}}),
  }, {
                  //Locations
                  LocationAccess(DEKU_TREE_MQ_DEKU_SCRUB,     {[]{return CanStunDeku;}}),
                  LocationAccess(DEKU_TREE_QUEEN_GOHMA_HEART, {[]{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks) && (Nuts || CanUse(SLINGSHOT) || CanUse(BOW) || HookshotOrBoomerang);}}),
                  LocationAccess(QUEEN_GOHMA,                 {[]{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks) && (Nuts || CanUse(SLINGSHOT) || CanUse(BOW) || HookshotOrBoomerang);}}),
  }, {
                  //Exits
                  Entrance(DEKU_TREE_MQ_BASEMENT_BACK_ROOM, {[]{return IsChild;}}),
                  Entrance(DEKU_TREE_MQ_LOBBY,              {[]{return true;}}),
  });
  }

  if (Dungeon::DodongosCavern.IsMQ()) {
  areaTable[DODONGOS_CAVERN_MQ_BEGINNING] = Area("Dodongos Cavern MQ Beginning", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_ENTRYWAY, {[]{return true;}}),
                  Entrance(DODONGOS_CAVERN_MQ_LOBBY, {[]{return Here(DODONGOS_CAVERN_MQ_BEGINNING, []{return CanBlastOrSmash || GoronBracelet;});}}),
  });

  areaTable[DODONGOS_CAVERN_MQ_LOBBY] = Area("Dodongos Cavern MQ Lobby", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks,   {[]{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}}),
                  EventAccess(&GossipStoneFairy, {[]{return GossipStoneFairy || CanSummonGossipFairy;}}),
  }, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_MQ_MAP_CHEST,                  {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_COMPASS_CHEST,              {[]{return IsAdult || CanChildAttack || Nuts;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,          {[]{return CanUse(STICKS) || HasFireSource;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,    {[]{return CanBlastOrSmash || CanUse(STICKS) || CanUse(DINS_FIRE) || (IsAdult && (LogicDCJump || HoverBoots || Hookshot));}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM, {[]{return CanPlay(SongOfTime) && (CanChildAttack || IsAdult);}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,             {[]{return CanUse(STICKS) || HasFireSource;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,           {[]{return CanBlastOrSmash;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,      {[]{return CanStunDeku;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,     {[]{return CanStunDeku;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,       {[]{return CanStunDeku;}}),
                  LocationAccess(DODONGOS_CAVERN_GOSSIP_STONE,                  {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE,  {[]{return Here(DODONGOS_CAVERN_MQ_LOBBY, []{return CanBlastOrSmash || ((CanUse(STICKS) || CanUse(DINS_FIRE)) && CanTakeDamage);});}}),
                  Entrance(DODONGOS_CAVERN_MQ_BOMB_BAG_AREA,     {[]{return IsAdult || (Here(DODONGOS_CAVERN_MQ_LOBBY, []{return IsAdult;}) && HasExplosives);}}),
                    //Trick: IsAdult || HasExplosives || (LogicDCMQChildBombs && (KokiriSword || Sticks) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
                  Entrance(DODONGOS_CAVERN_MQ_BOSS_AREA,         {[]{return HasExplosives;}}),
                    //Trick: HasExplosives || (LogicDCMQEyes && GoronBracelet && (IsAdult || LogicDCMQChildBack) && (CanUse(STICKS) || CanUse(DINS_FIRE) || (IsAdult && (LogicDCJump || Hammer || HoverBoots || Hookshot))))
  });

  areaTable[DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE] = Area("Dodongos Cavern MQ Lower Right Side", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS, {[]{return CanStunDeku;}}),
  }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_MQ_BOMB_BAG_AREA, {[]{return (Here(DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE, []{return CanUse(BOW);}) || GoronBracelet ||
                                                                                CanUse(DINS_FIRE) || HasExplosives) &&
                                                                                CanUse(SLINGSHOT);}}),
  });

  areaTable[DODONGOS_CAVERN_MQ_BOMB_BAG_AREA] = Area("Dodongos Cavern MQ Bomb Bag Area", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST, {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,  {[]{return (Here(DODONGOS_CAVERN_MQ_BOMB_BAG_AREA, []{return CanUse(BOW);}) ||  GoronBracelet || CanUse(DINS_FIRE) || HasExplosives) && (CanUse(HOOKSHOT) || CanUse(BOOMERANG));}}),
  }, {
                  //Exits
                  Entrance(DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE, {[]{return true;}}),
  });

  areaTable[DODONGOS_CAVERN_MQ_BOSS_AREA] = Area("Dodongos Cavern MQ BossArea", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot,            {[]{return true;}}),
                  EventAccess(&DodongosCavernClear, {[]{return DodongosCavernClear || (CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));}}),
  }, {
                  //Locations
                  LocationAccess(DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST, {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_BOSS_ROOM_CHEST,      {[]{return true;}}),
                  LocationAccess(DODONGOS_CAVERN_KING_DODONGO_HEART,   {[]{return CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}}),
                  LocationAccess(KING_DODONGO,                         {[]{return CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}}),
                  LocationAccess(DODONGOS_CAVERN_MQ_GS_BACK_AREA,      {[]{return true;}}),
  }, {});
  }

  if (Dungeon::JabuJabusBelly.IsMQ()) {
  areaTable[JABU_JABUS_BELLY_MQ_BEGINNING] = Area("Jabu Jabus Belly MQ Beginning", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_MQ_MAP_CHEST,             {[]{return CanBlastOrSmash;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST, {[]{return CanUse(SLINGSHOT);}}),
  }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_ENTRYWAY, {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_MQ_MAIN,  {[]{return Here(JABU_JABUS_BELLY_MQ_BEGINNING, []{return IsChild && CanUse(SLINGSHOT);});}}),
  });

  areaTable[JABU_JABUS_BELLY_MQ_MAIN] = Area("Jabu Jabus Belly MQ Main", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,      {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,      {[]{return CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT) || ChildCanAccess(JABU_JABUS_BELLY_MQ_BOSS_AREA);}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_COMPASS_CHEST,                {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,    {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,   {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,              {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,      {[]{return CanPlay(SongOfTime);}}),
                    //Trick: CanPlay(SongOfTime) || (LogicJabuMQSoTGS && CanUse(BOOMERANG))
  }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_MQ_BEGINNING, {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_MQ_DEPTHS,    {[]{return HasExplosives && CanUse(BOOMERANG);}}),
  });

  areaTable[JABU_JABUS_BELLY_MQ_DEPTHS] = Area("Jabu Jabus Belly MQ Depths", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST, {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,          {[]{return Sticks || CanUse(DINS_FIRE);}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,    {[]{return (LogicLensJabuMQ || CanUse(LENS_OF_TRUTH)) || Here(JABU_JABUS_BELLY_MQ_MAIN, []{return CanUse(HOVER_BOOTS) && CanUse(HOOKSHOT);});}}),
  }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_MQ_MAIN,      {[]{return true;}}),
                  Entrance(JABU_JABUS_BELLY_MQ_BOSS_AREA, {[]{return Sticks || (CanUse(DINS_FIRE) && KokiriSword);}}),
  });

  areaTable[JABU_JABUS_BELLY_MQ_BOSS_AREA] = Area("Jabu Jabus Belly MQ Boss Area", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot,            {[]{return true;}}),
                  EventAccess(&JabuJabusBellyClear, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(JABU_JABUS_BELLY_MQ_COW,             {[]{return CanPlay(EponasSong);}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST, {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_BARINADE_HEART,     {[]{return true;}}),
                  LocationAccess(BARINADE,                            {[]{return true;}}),
                  LocationAccess(JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,    {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(JABU_JABUS_BELLY_MQ_MAIN, {[]{return true;}}),
  });
  }

  if (Dungeon::ForestTemple.IsMQ()) {
  areaTable[FOREST_TEMPLE_MQ_LOBBY] = Area("Forest Temple MQ Lobby", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST, {[]{return IsAdult || Bombs || CanUse(STICKS) || Nuts || CanUse(BOOMERANG) || CanUse(DINS_FIRE) || KokiriSword || CanUse(SLINGSHOT);}}),
                  LocationAccess(FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY, {[]{return CanUse(HOOKSHOT) || CanUse(BOOMERANG);}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_ENTRYWAY,        {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_MQ_CENTRAL_AREA, {[]{return SmallKeys(ForestTempleKeys, 1) && (IsAdult || CanChildAttack || Nuts);}}),
  });

  areaTable[FOREST_TEMPLE_MQ_CENTRAL_AREA] = Area("Forest Temple MQ Central Area", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_WOLFOS_CHEST,       {[]{return (CanPlay(SongOfTime) || IsChild) && (IsAdult || CanUse(DINS_FIRE) || CanUse(STICKS) || CanUse(SLINGSHOT) || KokiriSword);}}),
                  LocationAccess(FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM, {[]{return IsAdult || KokiriSword;}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_NW_OUTDOORS,        {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}),
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS,        {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}), //This is as far as child can get
                  Entrance(FOREST_TEMPLE_MQ_AFTER_BLOCK_PUZZLE, {[]{return IsAdult && GoronBracelet;}}),
                    //Trick: IsAdult && (GoronBracelet || (LogicForestMQBlockPuzzle && HasBombchus && CanUse(HOOKSHOT)))
                  Entrance(FOREST_TEMPLE_MQ_OUTDOOR_LEDGE,      {[]{return false;}}),
                    //Trick: (LogicForestMQHallwaySwitchJumpslash && CanUse(HOVER_BOOTS)) || (LogicForestMQHallwaySwitchHookshot && CanUse(HOOKSHOT))
                  Entrance(FOREST_TEMPLE_MQ_BOSS_REGION,        {[]{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;}}),
  });

  areaTable[FOREST_TEMPLE_MQ_AFTER_BLOCK_PUZZLE] = Area("Forest Temple MQ After Block Puzzle", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_BOSS_KEY_CHEST, {[]{return SmallKeys(ForestTempleKeys, 3);}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_BOW_REGION,    {[]{return SmallKeys(ForestTempleKeys, 4);}}),
                  Entrance(FOREST_TEMPLE_MQ_OUTDOOR_LEDGE, {[]{return SmallKeys(ForestTempleKeys, 3);}}),
                    //Trick: SmallKeys(ForestTempleKeys, 3) || (LogicForestMQHallwaySwitchJumpslash && (CanUse(HOOKSHOT) || LogicForestOutsideBackdoor))
                  Entrance(FOREST_TEMPLE_MQ_NW_OUTDOORS,   {[]{return SmallKeys(ForestTempleKeys, 2);}}),
  });

  areaTable[FOREST_TEMPLE_MQ_OUTDOOR_LEDGE] = Area("Forest Temple MQ Outdoor Ledge", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_REDEAD_CHEST, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_NW_OUTDOORS, {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_MQ_NW_OUTDOORS] = Area("Forest Temple MQ NW Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS,         {[]{return CanUse(IRON_BOOTS) || CanUse(LONGSHOT) || ProgressiveScale >= 2;}}),
                    //Trick: CanUse(IRON_BOOTS) || CanUse(LONGSHOT) || ProgressiveScale >= 2 || (LogicForestMQWellSwim && CanUse(HOOKSHOT))
                  Entrance(FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES, {[]{return CanUse(FIRE_ARROWS);}}),
  });

  areaTable[FOREST_TEMPLE_MQ_NE_OUTDOORS] = Area("Forest Temple MQ NE Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&DekuBabaSticks, {[]{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}}),
                  EventAccess(&DekuBabaNuts,   {[]{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(DINS_FIRE));}}),
  }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_WELL_CHEST,                 {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}),
                  LocationAccess(FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD, {[]{return CanUse(HOOKSHOT) || CanUse(BOOMERANG) || (CanUse(FIRE_ARROWS) && (CanPlay(SongOfTime) || (CanUse(HOVER_BOOTS) && LogicForestDoorFrame)));}}),
                  LocationAccess(FOREST_TEMPLE_MQ_GS_WELL,                    {[]{return (CanUse(IRON_BOOTS) && CanUse(HOOKSHOT)) || CanUse(BOW) || CanUse(SLINGSHOT);}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES, {[]{return CanUse(HOOKSHOT) && (CanUse(LONGSHOT) || CanUse(HOVER_BOOTS) || CanPlay(SongOfTime));}}),
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE,   {[]{return CanUse(LONGSHOT);}}),
  });

  areaTable[FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES] = Area("Forest Temple MQ Outdoors Top Ledges", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS,       {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE, {[]{return false;}}),
                    //Trick: LogicForestOutdoorsLedge && CanUse(HOVER_BOOTS)
  });

  areaTable[FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE] = Area("Forest Temple MQ NE Outdoors Ledge", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS,  {[]{return true;}}),
                  Entrance(FOREST_TEMPLE_MQ_FALLING_ROOM, {[]{return CanPlay(SongOfTime);}}),
  });

  areaTable[FOREST_TEMPLE_MQ_BOW_REGION] = Area("Forest Temple MQ Bow Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTempleJoAndBeth, {[]{return ForestTempleJoAndBeth || CanUse(BOW);}}),
  }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_BOW_CHEST,     {[]{return true;}}),
                  LocationAccess(FOREST_TEMPLE_MQ_MAP_CHEST,     {[]{return CanUse(BOW);}}),
                  LocationAccess(FOREST_TEMPLE_MQ_COMPASS_CHEST, {[]{return CanUse(BOW);}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_FALLING_ROOM, {[]{return SmallKeys(ForestTempleKeys, 5) && (CanUse(BOW) || CanUse(DINS_FIRE));}}),
  });

  areaTable[FOREST_TEMPLE_MQ_FALLING_ROOM] = Area("Forest Temple MQ Falling Room", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTempleAmyAndMeg, {[]{return ForestTempleAmyAndMeg || (CanUse(BOW) && SmallKeys(ForestTempleKeys, 6));}}),
  }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE, {[]{return true;}}),
  });

  areaTable[FOREST_TEMPLE_MQ_BOSS_REGION] = Area("Forest Temple MQ Boss Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTempleClear, {[]{return ForestTempleClear || BossKeyForestTemple;}}),
  }, {
                  //Locations
                  LocationAccess(FOREST_TEMPLE_MQ_BASEMENT_CHEST,   {[]{return true;}}),
                  LocationAccess(FOREST_TEMPLE_PHANTOM_GANON_HEART, {[]{return BossKeyForestTemple;}}),
                  LocationAccess(PHANTOM_GANON,                     {[]{return BossKeyForestTemple;}}),
  }, {});
  }

  if (Dungeon::FireTemple.IsMQ()) {
  areaTable[FIRE_TEMPLE_MQ_LOWER] = Area("Fire Temple MQ Lower", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST, {[]{return IsAdult || KokiriSword || Sticks || Slingshot || Bombs || CanUse(DINS_FIRE);}}),
                  LocationAccess(FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,     {[]{return (LogicFewerTunicRequirements || CanUse(GORON_TUNIC)) 
                                                                             && (CanUse(HOVER_BOOTS) || CanUse(HOOKSHOT))
                                                                             && (CanUse(FIRE_ARROWS) || (CanUse(DINS_FIRE) &&
                                                                                                            ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE))
                                                                                                           || CanUse(GORON_TUNIC)
                                                                                                           || CanUse(BOW)
                                                                                                           || CanUse(LONGSHOT))));}}),
                    //Trick: (LogicFewerTunicRequirements || CanUse(GORON_TUNIC)) && (((CanUse(HOVER_BOOTS) || (LogicFireMQNearBoss && CanUse(BOW))) && HasFireSource) || (CanUse(HOOKSHOT) && CanUse(FIRE_ARROWS) || (CanUse(DINS_FIRE) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE)) || CanUse(GORON_TUNIC) || CanUse(BOW) || CanUse(LONGSHOT)))))
  }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_ENTRYWAY,             {[]{return true;}}),
                  Entrance(FIRE_TEMPLE_MQ_BOSS_ROOM,         {[]{return CanUse(GORON_TUNIC) && CanUse(MEGATON_HAMMER) && BossKeyFireTemple && ((HasFireSource && (LogicFireBossDoorJump || HoverBoots)) || HasAccessTo(FIRE_TEMPLE_MQ_UPPER));}}),
                  Entrance(FIRE_TEMPLE_MQ_LOWER_LOCKED_DOOR, {[]{return SmallKeys(FireTempleKeys, 5) && (IsAdult || KokiriSword);}}),
                  Entrance(FIRE_TEMPLE_MQ_BIG_LAVA_ROOM,     {[]{return (LogicFewerTunicRequirements || CanUse(GORON_TUNIC)) && CanUse(MEGATON_HAMMER);}}),
  });

  areaTable[FIRE_TEMPLE_MQ_LOWER_LOCKED_DOOR] = Area("Fire Temple MQ Lower Locked Door", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST, {[]{return IsAdult && (HasExplosives || Hammer || Hookshot);}}),
                  LocationAccess(FIRE_TEMPLE_MQ_MAP_CHEST,            {[]{return CanUse(MEGATON_HAMMER);}}),
  }, {});

  areaTable[FIRE_TEMPLE_MQ_BIG_LAVA_ROOM] = Area("Fire Temple MQ Big Lava Room", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return FairyPot || (HasFireSource && Bow && (CanUse(HOOKSHOT) || LogicFireSongOfTime));}}),
                    //Trick: HasFireSource && (Bow || LogicFireMQBKChest) && (CanUse(HOOKSHOT) || LogicFireSongOfTime)
  }, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,                   {[]{return HasFireSource && Bow && CanUse(HOOKSHOT);}}),
                    //Trick: HasFireSource && (Bow || LogicFireMQBKChest) && CanUse(HOOKSHOT)
                  LocationAccess(FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, {[]{return HasFireSource && HasExplosives && CanUse(HOOKSHOT);}}),
                    //Trick: HasFireSource && HasExplosives && (CanUse(HOOKSHOT) || LogicFireMQBlockedChest)
                  LocationAccess(FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,       {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_MQ_LOWER_MAZE, {[]{return CanUse(GORON_TUNIC) && SmallKeys(FireTempleKeys, 2) && HasFireSource;}}),
                    //Trick: CanUse(GORON_TUNIC) && SmallKeys(FireTempleKeys, 2) && (HasFireSource || (LogicFireMQClimb && HoverBoots))
  });

  areaTable[FIRE_TEMPLE_MQ_LOWER_MAZE] = Area("Fire Temple MQ Lower Maze", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,     {[]{return true;}}),
                  LocationAccess(FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST, {[]{return HasExplosives && HasAccessTo(FIRE_TEMPLE_MQ_UPPER_MAZE);}}),
                    //Trick: HasExplosives && (LogicFireMQMazeSideRoom || FIRE_TEMPLE_MQ_UPPER_MAZE.Adult())
   }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_MQ_UPPER_MAZE, {[]{return HasExplosives && CanUse(HOOKSHOT);}}),
                    //Trick: (HasExplosives && CanUse(HOOKSHOT)) || (LogicFireMQMazeHovers && CanUse(HOVER_BOOTS)) || LogicFireMQMazeJump
  });

  areaTable[FIRE_TEMPLE_MQ_UPPER_MAZE] = Area("Fire Temple MQ Upper Maze", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventAccess(&WallFairy, {[]{return WallFairy || ((CanPlay(SongOfTime) && CanUse(HOOKSHOT) && HasExplosives) || CanUse(LONGSHOT));}}),
                  EventAccess(&FairyPot,  {[]{return SmallKeys(FireTempleKeys, 3);}}),
  }, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST, {[]{return true;}}),
                  LocationAccess(FIRE_TEMPLE_MQ_COMPASS_CHEST,             {[]{return HasExplosives;}}),
                  LocationAccess(FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,          {[]{return (CanPlay(SongOfTime) && CanUse(HOOKSHOT) && HasExplosives) || CanUse(LONGSHOT);}}),
  }, {
                  //Exits
                  Entrance(FIRE_TEMPLE_MQ_UPPER, {[]{return SmallKeys(FireTempleKeys, 3) && ((CanUse(BOW) && CanUse(HOOKSHOT)) || CanUse(FIRE_ARROWS));}}),
  });

  areaTable[FIRE_TEMPLE_MQ_UPPER] = Area("Fire Temple MQ Upper", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_MQ_FREESTANDING_KEY,            {[]{return CanUse(HOOKSHOT);}}),
                    //Trick: CanUse(HOOKSHOT) || LogicFireMQFlameMaze
                  LocationAccess(FIRE_TEMPLE_MQ_CHEST_ON_FIRE,               {[]{return CanUse(HOOKSHOT) && SmallKeys(FireTempleKeys, 4);}}),
                    //Trick: (CanUse(HOOKSHOT) || LogicFireMQFlameMaze) && SmallKeys(FireTempleKeys, 4)
                  LocationAccess(FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM, {[]{return CanPlay(SongOfTime) || HoverBoots;}}),
                    //Trick: CanPlay(SongOfTime) || HoverBoots || LogicFireMQFlameMaze
                  LocationAccess(FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,    {[]{return HasExplosives;}}),
                  LocationAccess(FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,     {[]{return CanUse(HOOKSHOT) && SmallKeys(FireTempleKeys, 5);}}),
                    //Trick: (CanUse(HOOKSHOT) && SmallKeys(FireTempleKeys, 5)) || (LogicFireMQAboveMazeGS && CanUse(LONGSHOT))
  }, {});

  areaTable[FIRE_TEMPLE_MQ_BOSS_ROOM] = Area("Fire Temple MQ Boss Room", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FireTempleClear, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(FIRE_TEMPLE_VOLVAGIA_HEART, {[]{return true;}}),
                  LocationAccess(VOLVAGIA,                   {[]{return true;}}),
  }, {});
  }

  if (Dungeon::WaterTemple.IsMQ()) {
  areaTable[WATER_TEMPLE_MQ_LOBBY] = Area("Water Temple MQ Lobby", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&WaterTempleClear, {[]{return BossKeyWaterTemple && CanUse(LONGSHOT);}}),
  }, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_MORPHA_HEART, {[]{return BossKeyWaterTemple && CanUse(LONGSHOT);}}),
                  LocationAccess(MORPHA,                    {[]{return BossKeyWaterTemple && CanUse(LONGSHOT);}}),
  }, {
                  //Exits
                  Entrance(WATER_TEMPLE_ENTRYWAY,            {[]{return true;}}),
                  Entrance(WATER_TEMPLE_MQ_DIVE,             {[]{return (CanUse(ZORA_TUNIC) || LogicFewerTunicRequirements) && CanUse(IRON_BOOTS);}}),
                  Entrance(WATER_TEMPLE_MQ_DARK_LINK_REGION, {[]{return SmallKeys(WaterTempleKeys, 1) && CanUse(LONGSHOT);}}),
  });

  areaTable[WATER_TEMPLE_MQ_DIVE] = Area("Water Temple MQ Dive", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_MQ_MAP_CHEST,            {[]{return HasFireSource && CanUse(HOOKSHOT);}}),
                  LocationAccess(WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST, {[]{return CanUse(ZORA_TUNIC) && CanUse(HOOKSHOT) && (CanUse(DINS_FIRE) && CanPlay(SongOfTime));}}),
                    //Trick: CanUse(ZORA_TUNIC) && CanUse(HOOKSHOT) && ((LogicWaterMQCentralPillar && CanUse(FIRE_ARROWS)) || (CanUse(DINS_FIRE) && CanPlay(SongOfTime)))
  }, {
                  //Exits
                  Entrance(WATER_TEMPLE_MQ_LOWERED_WATER_LEVELS, {[]{return CanPlay(ZeldasLullaby);}}),
  });

  areaTable[WATER_TEMPLE_MQ_LOWERED_WATER_LEVELS] = Area("Water Temple MQ Lowered Water Levels", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_MQ_COMPASS_CHEST,                {[]{return CanUse(BOW) || CanUse(DINS_FIRE) || Here(WATER_TEMPLE_MQ_LOBBY, []{return CanUse(STICKS) && HasExplosives;});}}),
                  LocationAccess(WATER_TEMPLE_MQ_LONGSHOT_CHEST,               {[]{return CanUse(HOOKSHOT);}}),
                  LocationAccess(WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,          {[]{return CanUse(DINS_FIRE);}}),
                  LocationAccess(WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH, {[]{return CanUse(LONGSHOT);}}),
  }, {});

  areaTable[WATER_TEMPLE_MQ_DARK_LINK_REGION] = Area("Water Temple MQ Dark Link Region", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}),
                  EventAccess(&NutPot,   {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_MQ_BOSS_KEY_CHEST, {[]{return (CanUse(ZORA_TUNIC) || LogicFewerTunicRequirements) && CanUse(DINS_FIRE) && (LogicWaterDragonJumpDive || CanDive || CanUse(IRON_BOOTS));}}),
                  LocationAccess(WATER_TEMPLE_MQ_GS_RIVER,       {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(WATER_TEMPLE_MQ_BASEMENT_GATED_AREAS, {[]{return (CanUse(ZORA_TUNIC) || LogicFewerTunicRequirements) && CanUse(DINS_FIRE) && CanUse(IRON_BOOTS);}}),
  });

  areaTable[WATER_TEMPLE_MQ_BASEMENT_GATED_AREAS] = Area("Water Temple MQ Basement Gated Areas", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(WATER_TEMPLE_MQ_FREESTANDING_KEY,         {[]{return HoverBoots || CanUse(SCARECROW) || LogicWaterNorthBasementLedgeJump;}}),
                  LocationAccess(WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,     {[]{return CanUse(FIRE_ARROWS) && (HoverBoots || CanUse(SCARECROW));}}),
                  LocationAccess(WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA, {[]{return SmallKeys(WaterTempleKeys, 2) && (HoverBoots || CanUse(SCARECROW) || LogicWaterNorthBasementLedgeJump);}}),
                    //Trick: LogicWaterMQLockedGS || (SmallKeys(WaterTempleKeys, 2) && (HoverBoots || CanUse(SCARECROW) || LogicWaterNorthBasementLedgeJump))
  }, {});
  }

  if (Dungeon::SpiritTemple.IsMQ()) {
  areaTable[SPIRIT_TEMPLE_MQ_LOBBY] = Area("Spirit Temple MQ Lobby", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST, {[]{return true;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,  {[]{return Here(SPIRIT_TEMPLE_MQ_LOBBY, []{return CanBlastOrSmash;}) && (CanUse(SLINGSHOT) || CanUse(BOW));}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST, {[]{return HasBombchus || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || CanUse(BOOMERANG);}}),
  }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_ENTRYWAY, {[]{return true;}}),
                  Entrance(SPIRIT_TEMPLE_MQ_CHILD, {[]{return IsChild;}}),
                  Entrance(SPIRIT_TEMPLE_MQ_ADULT, {[]{return HasBombchus && CanUse(LONGSHOT) && CanUse(SILVER_GAUNTLETS);}}),
  });

  areaTable[SPIRIT_TEMPLE_MQ_CHILD] = Area("Spirit Temple MQ Child", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return FairyPot || (KokiriSword && HasBombchus && Slingshot);}}),
  }, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,  {[]{return Here(SPIRIT_TEMPLE_MQ_ADULT, []{return SmallKeys(SpiritTempleKeys, 7) && Hammer;});}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,       {[]{return KokiriSword && HasBombchus && Slingshot && CanUse(DINS_FIRE);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_MAP_CHEST,                  {[]{return KokiriSword || Bombs;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST, {[]{return HasBombchus && SmallKeys(SpiritTempleKeys, 7) && Slingshot && (CanUse(DINS_FIRE) || (Here(SPIRIT_TEMPLE_MQ_ADULT, []{return CanUse(FIRE_ARROWS);})));}}),
                    //Trick: HasBombchus && SmallKeys(SpiritTempleKeys, 7) && Slingshot && (CanUse(DINS_FIRE) || (SPIRIT_TEMPLE_MQ_ADULT.Adult() && (CanUse(FIRE_ARROWS) || (LogicSpiritMQFrozenEye && CanUse(BOW) && CanPlay(SongOfTime)))))
  }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_MQ_SHARED, {[]{return HasBombchus && SmallKeys(SpiritTempleKeys, 2);}}),
  });

  areaTable[SPIRIT_TEMPLE_MQ_ADULT] = Area("Spirit Temple MQ Adult", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,     {[]{return SmallKeys(SpiritTempleKeys, 7);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,   {[]{return CanPlay(ZeldasLullaby);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST, {[]{return (LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,           {[]{return SmallKeys(SpiritTempleKeys, 5);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,          {[]{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,              {[]{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime) && MirrorShield;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,   {[]{return SmallKeys(SpiritTempleKeys, 7);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,  {[]{return SmallKeys(SpiritTempleKeys, 7);}}),
  }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_MQ_LOWER_ADULT,        {[]{return MirrorShield && CanUse(FIRE_ARROWS);}}),
                    //Trick: MirrorShield && (CanUse(FIRE_ARROWS) || (LogicSpiritMQLowerAdult && CanUse(DINS_FIRE) && Bow))
                  Entrance(SPIRIT_TEMPLE_MQ_SHARED,             {[]{return true;}}),
                  Entrance(SPIRIT_TEMPLE_MQ_BOSS_AREA,          {[]{return SmallKeys(SpiritTempleKeys, 6) && CanPlay(ZeldasLullaby) && Hammer;}}),
                  Entrance(SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND, {[]{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH));}}),
  });

  areaTable[SPIRIT_TEMPLE_MQ_SHARED] = Area("Spirit Temple MQ Shared", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST, {[]{return SmallKeys(SpiritTempleKeys, 6);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_COMPASS_CHEST,           {[]{return (CanUse(SLINGSHOT) && SmallKeys(SpiritTempleKeys, 7)) || CanUse(BOW) || (Bow && Slingshot);}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,    {[]{return CanPlay(SongOfTime) || IsAdult;}}),
                    //Trick: CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult
                  LocationAccess(SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,       {[]{return IsAdult;}}),
                    //Trick: (LogicSpiritMQSunBlockGS && Boomerange && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT)) || IsAdult
   }, {
                  //Exits
                  Entrance(SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND, {[]{return (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH)));}}),
                    //Trick: (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH)))
                  Entrance(DESERT_COLOSSUS,                        {[]{return (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH)) && IsAdult);}}),
                    //Trick: (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH)) && IsAdult)
  });

  areaTable[SPIRIT_TEMPLE_MQ_LOWER_ADULT] = Area("Spirit Temple MQ Lower Adult", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,          {[]{return true;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,        {[]{return SmallKeys(SpiritTempleKeys, 7) && Hammer && Ocarina && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST, {[]{return Hammer;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,             {[]{return true;}}),
                  LocationAccess(SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,           {[]{return SmallKeys(SpiritTempleKeys, 7) && Hammer && Ocarina && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}}),
  }, {});

  areaTable[SPIRIT_TEMPLE_MQ_BOSS_AREA] = Area("Spirit Temple MQ Boss Area", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&SpiritTempleClear, {[]{return SpiritTempleClear || (MirrorShield && BossKeySpiritTemple);}}),
  }, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST, {[]{return LogicLensSpiritMQ || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(SPIRIT_TEMPLE_TWINROVA_HEART,                   {[]{return MirrorShield && BossKeySpiritTemple;}}),
                  LocationAccess(TWINROVA,                                       {[]{return MirrorShield && BossKeySpiritTemple;}}),
  }, {});

  areaTable[SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND] = Area("Spirit Temple MQ Mirror Shield Hand", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST, {[]{return true;}}),
  }, {});

  areaTable[SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND] = Area("Spirit Temple MQ Silver Gauntlets Hand", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, {[]{return true;}}),
  }, {});
  }

  if (Dungeon::ShadowTemple.IsMQ()) {
  areaTable[SHADOW_TEMPLE_MQ_BEGINNING] = Area("Shadow Temple MQ Beginning", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_ENTRYWAY,          {[]{return true;}}),
                  Entrance(SHADOW_TEMPLE_MQ_FIRST_BEAMOS,   {[]{return CanUse(FIRE_ARROWS) || CanUse(HOVER_BOOTS);}}),
                    //Trick: CanUse(FIRE_ARROWS) || HoverBoots || (LogicShadowMQGap && CanUse(LONGSHOT))
                  Entrance(SHADOW_TEMPLE_MQ_DEAD_HAND_AREA, {[]{return HasExplosives && SmallKeys(ShadowTempleKeys, 6);}}),
  });

  areaTable[SHADOW_TEMPLE_MQ_DEAD_HAND_AREA] = Area("Shadow Temple MQ Dead Hand Area", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MQ_COMPASS_CHEST,     {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST, {[]{return CanPlay(SongOfTime) && CanUse(BOW);}}),
  }, {});

  areaTable[SHADOW_TEMPLE_MQ_FIRST_BEAMOS] = Area("Shadow Temple MQ First Beamos", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MQ_MAP_CHEST,                 {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,        {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST, {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT, {[]{return HasExplosives && SmallKeys(ShadowTempleKeys, 2);}}),
  });

  areaTable[SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT] = Area("Shadow Temple MQ Upper Huge Pit", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,   {[]{return CanPlay(SongOfTime);}}),
                    //Trick: CanPlay(SongOfTime) || (LogicShadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
                  LocationAccess(SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST, {[]{return CanPlay(SongOfTime);}}),
                    //Trick: CanPlay(SongOfTime) || (LogicShadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
  }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT, {[]{return HasFireSource;}}),
                    //Trick: HasFireSource || LogicShadowMQHugePit
  });

  areaTable[SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT] = Area("Shadow Temple MQ Lower Huge Pit", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,  {[]{return CanUse(LONGSHOT);}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,  {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,  {[]{return (LogicShadowUmbrella && HoverBoots) || GoronBracelet;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST, {[]{return (LogicShadowUmbrella && HoverBoots) || GoronBracelet;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,      {[]{return HoverBoots && SmallKeys(ShadowTempleKeys, 3) && (LogicLensShadowMQBack || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,          {[]{return HoverBoots && SmallKeys(ShadowTempleKeys, 3) && Hookshot && (LogicLensShadowMQBack || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,      {[]{return Hookshot;}}),
  }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_MQ_WIND_TUNNEL, {[]{return HoverBoots && (LogicLensShadowMQBack || CanUse(LENS_OF_TRUTH)) && Hookshot && SmallKeys(ShadowTempleKeys, 4);}}),
  });

  areaTable[SHADOW_TEMPLE_MQ_WIND_TUNNEL] = Area("Shadow Temple MQ Wind Tunnel", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&NutPot, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,         {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,  {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST, {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,       {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_GS_AFTER_WIND,           {[]{return true;}}),
  }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_MQ_BEYOND_BOAT, {[]{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 5);}}),
  });

  areaTable[SHADOW_TEMPLE_MQ_BEYOND_BOAT] = Area("Shadow Temple MQ Beyond Boat", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ShadowTempleClear, {[]{return ShadowTempleClear || ((Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple);}}),
  }, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_BONGO_BONGO_HEART, {[]{return (Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple;}}),
                  LocationAccess(BONGO_BONGO,                     {[]{return (Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,  {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,   {[]{return Bow || (LogicShadowStatue && HasBombchus);}}),
  }, {
                  //Exits
                  Entrance(SHADOW_TEMPLE_MQ_INVISIBLE_MAZE, {[]{return Bow && CanPlay(SongOfTime) && CanUse(LONGSHOT);}}),
  });

  areaTable[SHADOW_TEMPLE_MQ_INVISIBLE_MAZE] = Area("Shadow Temple MQ Invisible Maze", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST, {[]{return CanUse(DINS_FIRE) && SmallKeys(ShadowTempleKeys, 6);}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,         {[]{return CanUse(DINS_FIRE) && SmallKeys(ShadowTempleKeys, 6);}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,      {[]{return true;}}),
                  LocationAccess(SHADOW_TEMPLE_MQ_FREESTANDING_KEY,       {[]{return true;}}),
  }, {});
  }

  if (Dungeon::BottomOfTheWell.IsMQ()) {
  areaTable[BOTTOM_OF_THE_WELL_MQ_PERIMETER] = Area("Bottom of the Well MQ Perimeter", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventAccess(&WallFairy, {[]{return WallFairy || Slingshot;}}),
  }, {
                  //Locations
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,              {[]{return KokiriSword || (Sticks && LogicChildDeadhand);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY, {[]{return HasExplosives;}}),
                    //Trick: HasExplosives || (LogicBotWMQDeadHandKey && Boomerang)
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,                {[]{return CanChildAttack;}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,             {[]{return CanChildAttack && SmallKeys(BottomOfTheWellKeys, 2);}}),
  }, {
                  //Exits
                  Entrance(BOTTOM_OF_THE_WELL_ENTRYWAY,  {[]{return true;}}),
                  Entrance(BOTTOM_OF_THE_WELL_MQ_MIDDLE, {[]{return CanPlay(ZeldasLullaby);}}),
                    //Trick: CanPlay(ZeldasLullaby) || (LogicBotWMQPits && HasExplosives)
  });

  areaTable[BOTTOM_OF_THE_WELL_MQ_MIDDLE] = Area("Bottom of the Well MQ Middle", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,                        {[]{return true;}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,              {[]{return HasExplosives && SmallKeys(BottomOfTheWellKeys, 2);}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY, {[]{return true;}}),
                  LocationAccess(BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,               {[]{return CanChildAttack && HasExplosives;}}),
                    //Trick: CanChildAttack && (LogicBotWMQPits || HasExplosives)
  }, {
                  //Exits
                  Entrance(BOTTOM_OF_THE_WELL_MQ_PERIMETER, {[]{return true;}}),
  });
  }

  if (Dungeon::IceCavern.IsMQ()) {
  areaTable[ICE_CAVERN_MQ_BEGINNING] = Area("Ice Cavern MQ Beginning", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FairyPot, {[]{return true;}}),
  }, {}, {
                  //Exits
                  Entrance(ICE_CAVERN_ENTRYWAY,             {[]{return true;}}),
                  Entrance(ICE_CAVERN_MQ_MAP_ROOM,          {[]{return IsAdult || CanUse(DINS_FIRE) || (HasExplosives && (CanUse(STICKS) || CanUse(SLINGSHOT) || KokiriSword));}}),
                  Entrance(ICE_CAVERN_MQ_COMPASS_ROOM,      {[]{return IsAdult && BlueFire;}}),
                  Entrance(ICE_CAVERN_MQ_IRON_BOOTS_REGION, {[]{return BlueFire;}}),
  });

  areaTable[ICE_CAVERN_MQ_MAP_ROOM] = Area("Ice Cavern MQ Map Room", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BlueFireAccess,  {[]{return BlueFireAccess || HasBottle;}}),
  }, {
                  //Locations
                  LocationAccess(ICE_CAVERN_MQ_MAP_CHEST, {[]{return BlueFire && (IsAdult || CanUse(STICKS) || KokiriSword || CanUseProjectile);}}),
  }, {});

  areaTable[ICE_CAVERN_MQ_IRON_BOOTS_REGION] = Area("Ice Cavern MQ Iron Boots Region", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(ICE_CAVERN_MQ_IRON_BOOTS_CHEST, {[]{return IsAdult;}}),
                  LocationAccess(SHEIK_IN_ICE_CAVERN,            {[]{return IsAdult;}}),
                  LocationAccess(ICE_CAVERN_MQ_GS_ICE_BLOCK,     {[]{return IsAdult || CanUseProjectile;}}),
                  LocationAccess(ICE_CAVERN_MQ_GS_SCARECROW,     {[]{return CanUse(SCARECROW) || (CanUse(HOVER_BOOTS) && CanUse(LONGSHOT));}}),
                    //Tricks: CanUse(SCARECROW) || (HoverBoots && CanUse(LONGSHOT)) || (LogicIceMQScarecrow && IsAdult)
  }, {});

  areaTable[ICE_CAVERN_MQ_COMPASS_ROOM] = Area("Ice Cavern MQ Compass Room", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(ICE_CAVERN_MQ_COMPASS_CHEST,    {[]{return true;}}),
                  LocationAccess(ICE_CAVERN_MQ_FREESTANDING_POH, {[]{return HasExplosives;}}),
                  LocationAccess(ICE_CAVERN_MQ_GS_RED_ICE,       {[]{return CanPlay(SongOfTime);}}),
                    //Trick: CanPlay(SongOfTime) || LogicIceMQRedIceGS
  }, {});
  }

  if (Dungeon::GerudoTrainingGrounds.IsMQ()) {
  areaTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY] = Area("Gerudo Training Grounds MQ Lobby", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST,       {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST,      {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST,   {[]{return LogicLensGtgMQ || CanUse(LENS_OF_TRUTH);}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST,  {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST, {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST,  {[]{return SmallKeys(GerudoTrainingGroundsKeys, 1);}}),
  }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_ENTRYWAY,      {[]{return true;}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_LEFT_SIDE,  {[]{return Here(GERUDO_TRAINING_GROUNDS_MQ_LOBBY, []{return HasFireSource;});}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_RIGHT_SIDE, {[]{return Here(GERUDO_TRAINING_GROUNDS_MQ_LOBBY, []{return CanUse(BOW) || CanUse(SLINGSHOT);});}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_MQ_RIGHT_SIDE] = Area("Gerudo Training Grounds MQ Right Side", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventAccess(&WallFairy, {[]{return WallFairy || CanUse(BOW);}}),
  }, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST, {[]{return IsAdult;}}),
  }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER, {[]{return (Bow || CanUse(LONGSHOT)) && CanUse(HOVER_BOOTS);}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER] = Area("Gerudo Training Grounds MQ Underwater", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST, {[]{return HasFireSource && CanUse(IRON_BOOTS) && (LogicFewerTunicRequirements || CanUse(ZORA_TUNIC)) && CanTakeDamage;}}),
  }, {});

  areaTable[GERUDO_TRAINING_GROUNDS_MQ_LEFT_SIDE] = Area("Gerudo Training Grounds MQ Left Side", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST, {[]{return IsAdult || KokiriSword || HasExplosives;}}),
  }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_STALFOS_ROOM, {[]{return CanUse(LONGSHOT);}}),
                    //Trick: CanUse(LONGSHOT) || LogicGtgMQWithoutHookshot || (LogicGtgMQWithHookshot && CanUse(HOOKSHOT))
  });

  areaTable[GERUDO_TRAINING_GROUNDS_MQ_STALFOS_ROOM] = Area("Gerudo Training Grounds MQ Stalfos Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&BlueFireAccess,  {[]{return BlueFireAccess || HasBottle;}}),
  }, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST, {[]{return IsAdult;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST,        {[]{return CanUse(SILVER_GAUNTLETS);}}),
  }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_BACK_AREAS, {[]{return IsAdult && (LogicLensGtgMQ || CanUse(LENS_OF_TRUTH)) && BlueFire && CanPlay(SongOfTime);}}),
                    //Trick: IsAdult && (LogicLensGtgMQ || CanUse(LENS_OF_TRUTH)) && BlueFire && (CanPlay(SongOfTime) || (LogicGtgFakeWall && CanUse(HOVER_BOOTS)))
  });

  areaTable[GERUDO_TRAINING_GROUNDS_MQ_BACK_AREAS] = Area("Gerudo Training Grounds MQ Back Areas", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST,          {[]{return Bow;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST, {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST,        {[]{return CanUse(HOOKSHOT) || Bow || HasExplosives;}}),
  }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_CENTRAL_MAZE_RIGHT, {[]{return Hammer;}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_RIGHT_SIDE,         {[]{return CanUse(LONGSHOT);}}),
  });

  areaTable[GERUDO_TRAINING_GROUNDS_MQ_CENTRAL_MAZE_RIGHT] = Area("Gerudo Training Grounds MQ Central Maze Right", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST, {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST,    {[]{return true;}}),
                  LocationAccess(GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST,         {[]{return SmallKeys(GerudoTrainingGroundsKeys, 3);}}),
  }, {
                  //Exits
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER,  {[]{return CanUse(LONGSHOT) || (CanUse(HOOKSHOT) && Bow);}}),
                  Entrance(GERUDO_TRAINING_GROUNDS_MQ_RIGHT_SIDE,  {[]{return CanUse(HOOKSHOT);}}),
  });
  }

  if (Dungeon::GanonsCastle.IsMQ()) {
  areaTable[GANONS_CASTLE_MQ_LOBBY] = Area("Ganon's Castle MQ Lobby", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  Entrance(GANONS_CASTLE_ENTRYWAY,        {[]{return (IsAdult || (HasExplosives || ((Nuts || Boomerang) && (Sticks || KokiriSword))));}}),
                  Entrance(GANONS_CASTLE_MQ_FOREST_TRIAL, {[]{return true;}}),
                  Entrance(GANONS_CASTLE_MQ_FIRE_TRIAL,   {[]{return true;}}),
                  Entrance(GANONS_CASTLE_MQ_WATER_TRIAL,  {[]{return true;}}),
                  Entrance(GANONS_CASTLE_MQ_SHADOW_TRIAL, {[]{return true;}}),
                  Entrance(GANONS_CASTLE_MQ_SPIRIT_TRIAL, {[]{return true;}}),
                  Entrance(GANONS_CASTLE_MQ_LIGHT_TRIAL,  {[]{return CanUse(GOLDEN_GAUNTLETS);}}),
                  Entrance(GANONS_CASTLE_TOWER,           {[]{return (ForestTrialClear || Trial::ForestTrial.IsSkipped()) &&
                                                                            (FireTrialClear   || Trial::FireTrial.IsSkipped())   &&
                                                                            (WaterTrialClear  || Trial::WaterTrial.IsSkipped())  &&
                                                                            (ShadowTrialClear || Trial::ShadowTrial.IsSkipped()) &&
                                                                            (SpiritTrialClear || Trial::SpiritTrial.IsSkipped()) &&
                                                                            (LightTrialClear  || Trial::LightTrial.IsSkipped());}}),
                  Entrance(GANONS_CASTLE_MQ_DEKU_SCRUBS,  {[]{return LogicLensCastleMQ || CanUse(LENS_OF_TRUTH);}}),
  });

  areaTable[GANONS_CASTLE_MQ_DEKU_SCRUBS] = Area("Ganon's Castle MQ Deku Scrubs", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FreeFairies, {[]{return true;}}),
  }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,  {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,       {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT, {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,         {[]{return CanStunDeku;}}),
                  LocationAccess(GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,        {[]{return CanStunDeku;}}),
  }, {});

  areaTable[GANONS_CASTLE_MQ_FOREST_TRIAL] = Area("Ganon's Castle MQ Forest Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ForestTrialClear, {[]{return CanUse(LIGHT_ARROWS) && CanPlay(SongOfTime);}}),
  }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,        {[]{return CanUse(BOW) || CanUse(SLINGSHOT);}}),
                  LocationAccess(GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST, {[]{return HasFireSource;}}),
                  LocationAccess(GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,        {[]{return HookshotOrBoomerang;}}),
  }, {});

  areaTable[GANONS_CASTLE_MQ_FIRE_TRIAL] = Area("Ganon's Castle MQ Fire Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&FireTrialClear, {[]{return CanUse(GORON_TUNIC) && CanUse(GOLDEN_GAUNTLETS) && CanUse(LIGHT_ARROWS) && (CanUse(LONGSHOT) || CanUse(HOVER_BOOTS));}}),
                    //Trick: CanUse(GORON_TUNIC) && CanUse(GOLDEN_GAUNTLETS) && CanUse(LIGHT_ARROWS) && (CanUse(LONGSHOT) || HoverBoots || (LogicFireTrialMQ && CanUse(HOOKSHOT)))
  }, {}, {});

  areaTable[GANONS_CASTLE_MQ_WATER_TRIAL] = Area("Ganon's Castle MQ Water Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&WaterTrialClear, {[]{return BlueFire && CanUse(LIGHT_ARROWS) && SmallKeys(GanonsCastleKeys, 3);}}),
                  EventAccess(&BlueFireAccess,  {[]{return BlueFireAccess || HasBottle;}}),
  }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_MQ_WATER_TRIAL_CHEST, {[]{return BlueFire && (IsAdult || CanUse(STICKS) || KokiriSword || CanUseProjectile);}}),
  }, {});

  areaTable[GANONS_CASTLE_MQ_SHADOW_TRIAL] = Area("Ganon's Castle MQ Shadow Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&ShadowTrialClear, {[]{return CanUse(LIGHT_ARROWS) && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && (CanUse(HOVER_BOOTS) || (CanUse(HOOKSHOT) && HasFireSource));}}),
                    //Trick: CanUse(LIGHT_ARROWS) && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && (HoverBoots || (Hookshot && (HasFireSource || LogicShadowTrialMQ)))
  }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST, {[]{return (Bow && (CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS))) || (CanUse(HOVER_BOOTS) && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && (HasExplosives || GoronBracelet || CanUse(DINS_FIRE)));}}),
                  LocationAccess(GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,  {[]{return Bow && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && (CanUse(HOVER_BOOTS) || (CanUse(HOOKSHOT) && HasFireSource));}}),
                    //Trick: Bow && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && (HoverBoots || (Hookshot && (HasFireSource || LogicShadowTrialMQ)))
  }, {});

  areaTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL] = Area("Ganon's Castle MQ Spirit Castle", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&SpiritTrialClear, {[]{return CanUse(LIGHT_ARROWS) && Hammer && HasBombchus && FireArrows && MirrorShield;}}),
                  EventAccess(&NutPot,           {[]{return NutPot || (Hammer && HasBombchus && CanUse(FIRE_ARROWS) && MirrorShield);}}),
  }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,             {[]{return IsAdult && Bow && Hammer;}}),
                  LocationAccess(GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,         {[]{return IsAdult && Bow && Hammer && HasBombchus && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH));}}),
                  LocationAccess(GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,    {[]{return IsAdult && Hammer && HasBombchus && CanUse(FIRE_ARROWS) && CanUse(MIRROR_SHIELD);}}),
                  LocationAccess(GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,     {[]{return IsAdult && Hammer && HasBombchus && CanUse(FIRE_ARROWS) && CanUse(MIRROR_SHIELD);}}),
                  LocationAccess(GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST,  {[]{return IsAdult && Hammer && HasBombchus && CanUse(FIRE_ARROWS) && CanUse(MIRROR_SHIELD);}}),
                  LocationAccess(GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,    {[]{return IsAdult && Hammer && HasBombchus && CanUse(FIRE_ARROWS) && CanUse(MIRROR_SHIELD);}}),
  }, {});

  areaTable[GANONS_CASTLE_MQ_LIGHT_TRIAL] = Area("Ganon's Castle MQ Light Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventAccess(&LightTrialClear, {[]{return CanUse(LIGHT_ARROWS) && SmallKeys(GanonsCastleKeys, 3) && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && CanUse(HOOKSHOT);}}),
                    //Trick: CanUse(LIGHT_ARROWS) && SmallKeys(GanonsCastleKeys, 3) && (LogicLensCastleMQ || CanUse(LENS_OF_TRUTH)) && (Hookshot || LogicLightTrialMQ)
  }, {
                  //Locations
                  LocationAccess(GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST, {[]{return CanPlay(ZeldasLullaby);}}),
  }, {});
  }

  //Set parent regions
  for (AreaKey i = ROOT; i <= GANONS_CASTLE; i++) {
    for (LocationAccess& locPair : areaTable[i].locations) {
      LocationKey location = locPair.GetLocation();
      Location(location)->SetParentRegion(i);
    }
    for (Entrance& exit : areaTable[i].exits) {
      exit.SetParentRegion(i);
      exit.SetName();
      exit.GetConnectedRegion()->entrances.push_front(&exit);
    }
  }
  /*
  //Events
}, {
  //Locations
}, {
  //Exits
*/
}

namespace Areas {

  static std::array<const AreaKey, 304> allAreas = {
    ROOT,
    ROOT_EXITS,

    KOKIRI_FOREST,
    KF_LINKS_HOUSE,
    KF_MIDOS_HOUSE,
    KF_SARIAS_HOUSE,
    KF_HOUSE_OF_TWINS,
    KF_KNOW_IT_ALL_HOUSE,
    KF_KOKIRI_SHOP,
    KF_STORMS_GROTTO,
    KF_OUTSIDE_DEKU_TREE,
    DEKU_TREE_ENTRYWAY,

    THE_LOST_WOODS,
    LW_BRIDGE_FROM_FOREST,
    LW_BRIDGE,
    LW_FOREST_EXIT,
    LW_BEYOND_MIDO,
    LW_NEAR_SHORTCUTS_GROTTO,
    DEKU_THEATER,
    LW_SCRUBS_GROTTO,
    SFM_ENTRYWAY,
    SACRED_FOREST_MEADOW,
    SFM_WOLFOS_GROTTO,
    SFM_FAIRY_GROTTO,
    SFM_STORMS_GROTTO,
    FOREST_TEMPLE_ENTRYWAY,

    KAKARIKO_VILLAGE,
    KAK_CARPENTER_BOSS_HOUSE,
    KAK_HOUSE_OF_SKULLTULA,
    KAK_IMPAS_HOUSE,
    KAK_IMPAS_LEDGE,
    KAK_IMPAS_HOUSE_BACK,
    KAK_IMPAS_HOUSE_NEAR_COW,
    KAK_WINDMILL,
    KAK_BAZAAR,
    KAK_SHOOTING_GALLERY,
    KAK_POTION_SHOP_FRONT,
    KAK_POTION_SHOP_BACK,
    KAK_ROOFTOP,
    KAK_BEHIND_GATE,
    KAK_BACKYARD,
    KAK_ODD_POULTICE_BUILDING,
    KAK_REDEAD_GROTTO,
    KAK_OPEN_GROTTO,
    BOTTOM_OF_THE_WELL_ENTRYWAY,

    THE_GRAVEYARD,
    GRAVEYARD_DAMPES_GRAVE,
    GRAVEYARD_DAMPES_HOUSE,
    GRAVEYARD_SHIELD_GRAVE,
    GRAVEYARD_COMPOSERS_GRAVE,
    GRAVEYARD_HEART_PIECE_GRAVE,
    GRAVEYARD_WARP_PAD_REGION,
    SHADOW_TEMPLE_ENTRYWAY,

    DEATH_MOUNTAIN_TRAIL,
    DEATH_MOUNTAIN_SUMMIT,
    DMT_OWL_FLIGHT,
    DMT_GREAT_FAIRY_FOUNTAIN,
    DMT_COW_GROTTO,
    DMT_STORMS_GROTTO,
    DODONGOS_CAVERN_ENTRYWAY,

    DMC_UPPER_LOCAL,
    DMC_CENTRAL_LOCAL,
    DMC_LOWER_LOCAL,
    DMC_LOWER_NEARBY,
    DMC_UPPER_NEARBY,
    DMC_CENTRAL_NEARBY,
    DMC_LADDER_AREA_NEARBY,
    DMC_UPPER_GROTTO,
    DMC_HAMMER_GROTTO,
    DMC_GREAT_FAIRY_FOUNTAIN,
    FIRE_TEMPLE_ENTRYWAY,

    GORON_CITY,
    GC_WOODS_WARP,
    GC_DARUNIAS_CHAMBER,
    GC_GROTTO_PLATFORM,
    GC_SHOP,
    GC_GROTTO,

    ZR_FRONT,
    ZORAS_RIVER,
    ZR_BEHIND_WATERFALL,
    ZR_OPEN_GROTTO,
    ZR_FAIRY_GROTTO,
    ZR_STORMS_GROTTO,
    ZORAS_DOMAIN,
    ZD_BEHIND_KING_ZORA,
    ZD_SHOP,
    ZD_STORMS_GROTTO,
    ZORAS_FOUNTAIN,
    ZF_GREAT_FAIRY_FOUNTAIN,
    JABU_JABUS_BELLY_ENTRYWAY,
    ICE_CAVERN_ENTRYWAY,

    HYRULE_FIELD,
    HF_SOUTHEAST_GROTTO,
    HF_OPEN_GROTTO,
    HF_INSIDE_FENCE_GROTTO,
    HF_COW_GROTTO,
    HF_NEAR_MARKET_GROTTO,
    HF_FAIRY_GROTTO,
    HF_NEAR_KAK_GROTTO,
    HF_TEKTITE_GROTTO,

    LON_LON_RANCH,
    LLR_TALONS_HOUSE,
    LLR_STABLES,
    LLR_TOWER,
    LLR_GROTTO,

    LAKE_HYLIA,
    LH_OWL_FLIGHT,
    LH_LAB,
    LH_FISHING_ISLAND,
    LH_FISHING_HOLE,
    LH_GROTTO,
    WATER_TEMPLE_ENTRYWAY,

    GERUDO_VALLEY,
    GV_UPPER_STREAM,
    GV_LOWER_STREAM,
    GV_GROTTO_LEDGE,
    GV_CRATE_LEDGE,
    GV_OCTOROK_GROTTO,
    GV_FORTRESS_SIDE,
    GV_CARPENTER_TENT,
    GV_STORMS_GROTTO,
    GERUDO_FORTRESS,
    GF_OUTSIDE_GATE,
    GF_STORMS_GROTTO,
    GERUDO_TRAINING_GROUNDS_ENTRYWAY,

    WASTELAND_NEAR_FORTRESS,
    HAUNTED_WASTELAND,
    WASTELAND_NEAR_COLOSSUS,
    DESERT_COLOSSUS,
    COLOSSUS_GREAT_FAIRY_FOUNTAIN,
    COLOSSUS_GROTTO,
    SPIRIT_TEMPLE_ENTRYWAY,

    MARKET_ENTRANCE,
    THE_MARKET,
    MARKET_GUARD_HOUSE,
    MARKET_BAZAAR,
    MARKET_MASK_SHOP,
    MARKET_SHOOTING_GALLERY,
    MARKET_BOMBCHU_BOWLING,
    MARKET_TREASURE_CHEST_GAME,
    MARKET_POTION_SHOP,
    MARKET_BACK_ALLEY,
    MARKET_BOMBCHU_SHOP,
    MARKET_DOG_LADY_HOUSE,
    MARKET_MAN_IN_GREEN_HOUSE,
    TOT_ENTRANCE,
    TEMPLE_OF_TIME,
    TOT_BEYOND_DOOR_OF_TIME,

    CASTLE_GROUNDS,
    HYRULE_CASTLE_GROUNDS,
    HC_GARDEN,
    HC_GREAT_FAIRY_FOUNTAIN,
    HC_STORMS_GROTTO,
    GANONS_CASTLE_GROUNDS,
    OGC_GREAT_FAIRY_FOUNTAIN,
    GANONS_CASTLE_ENTRYWAY,

    DEKU_TREE_LOBBY,
    DEKU_TREE_SLINGSHOT_ROOM,
    DEKU_TREE_BASEMENT_BACK_ROOM,
    DEKU_TREE_BOSS_ROOM,
    DODONGOS_CAVERN_BEGINNING,
    DODONGOS_CAVERN_LOBBY,
    DODONGOS_CAVERN_CLIMB,
    DODONGOS_CAVERN_FAR_BRIDGE,
    DODONGOS_CAVERN_BOSS_AREA,
    JABU_JABUS_BELLY_BEGINNING,
    JABU_JABUS_BELLY_MAIN,
    JABU_JABUS_BELLY_DEPTHS,
    JABU_JABUS_BELLY_BOSS_AREA,
    FOREST_TEMPLE_LOBBY,
    FOREST_TEMPLE_NW_OUTDOORS,
    FOREST_TEMPLE_NE_OUTDOORS,
    FOREST_TEMPLE_OUTDOORS_HIGH_BALCONIES,
    FOREST_TEMPLE_FALLING_ROOM,
    FOREST_TEMPLE_BLOCK_PUSH_ROOM,
    FOREST_TEMPLE_STRAIGHTENED_HALL,
    FOREST_TEMPLE_OUTSIDE_UPPER_LEDGE,
    FOREST_TEMPLE_BOW_REGION,
    FOREST_TEMPLE_BOSS_REGION,
    FIRE_TEMPLE_LOWER,
    FIRE_TEMPLE_BIG_LAVA_ROOM,
    FIRE_TEMPLE_MIDDLE,
    FIRE_TEMPLE_UPPER,
    WATER_TEMPLE_LOBBY,
    WATER_TEMPLE_HIGHEST_WATER_LEVEL,
    WATER_TEMPLE_DIVE,
    WATER_TEMPLE_CRACKED_WALL,
    WATER_TEMPLE_NORTH_BASEMENT,
    WATER_TEMPLE_DRAGON_STATUE,
    WATER_TEMPLE_MIDDLE_WATER_LEVEL,
    WATER_TEMPLE_FALLING_PLATFORM_ROOM,
    WATER_TEMPLE_DARK_LINK_REGION,
    SPIRIT_TEMPLE_LOBBY,
    SPIRIT_TEMPLE_CHILD,
    SPIRIT_TEMPLE_CHILD_CLIMB,
    SPIRIT_TEMPLE_EARLY_ADULT,
    SPIRIT_TEMPLE_CENTRAL_CHAMBER,
    SPIRIT_TEMPLE_OUTDOOR_HANDS,
    SPIRIT_TEMPLE_BEYOND_CENTRAL_LOCKED_DOOR,
    SPIRIT_TEMPLE_BEYOND_FINAL_LOCKED_DOOR,
    SHADOW_TEMPLE_BEGINNING,
    SHADOW_TEMPLE_FIRST_BEAMOS,
    SHADOW_TEMPLE_HUGE_PIT,
    SHADOW_TEMPLE_WIND_TUNNEL,
    SHADOW_TEMPLE_BEYOND_BOAT,
    BOTTOM_OF_THE_WELL,
    BOTTOM_OF_THE_WELL_MAIN_AREA,
    ICE_CAVERN_BEGINNING,
    ICE_CAVERN_MAIN,
    GERUDO_TRAINING_GROUNDS_LOBBY,
    GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE,
    GERUDO_TRAINING_GROUNDS_CENTRAL_MAZE_RIGHT,
    GERUDO_TRAINING_GROUNDS_LAVA_ROOM,
    GERUDO_TRAINING_GROUNDS_HAMMER_ROOM,
    GERUDO_TRAINING_GROUNDS_EYE_STATUE_LOWER,
    GERUDO_TRAINING_GROUNDS_EYE_STATUE_UPPER,
    GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_ROOM,
    GERUDO_TRAINING_GROUNDS_LIKE_LIKE_ROOM,
    GANONS_CASTLE_LOBBY,
    GANONS_CASTLE_DEKU_SCRUBS,
    GANONS_CASTLE_FOREST_TRIAL,
    GANONS_CASTLE_FIRE_TRIAL,
    GANONS_CASTLE_WATER_TRIAL,
    GANONS_CASTLE_SHADOW_TRIAL,
    GANONS_CASTLE_SPIRIT_TRIAL,
    GANONS_CASTLE_LIGHT_TRIAL,
    GANONS_CASTLE_TOWER,
    DEKU_TREE_MQ_LOBBY,
    DEKU_TREE_MQ_COMPASS_ROOM,
    DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT,
    DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK,
    DEKU_TREE_MQ_BASEMENT_BACK_ROOM,
    DEKU_TREE_MQ_BASEMENT_LEDGE,
    DODONGOS_CAVERN_MQ_BEGINNING,
    DODONGOS_CAVERN_MQ_LOBBY,
    DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE,
    DODONGOS_CAVERN_MQ_BOMB_BAG_AREA,
    DODONGOS_CAVERN_MQ_BOSS_AREA,
    JABU_JABUS_BELLY_MQ_BEGINNING,
    JABU_JABUS_BELLY_MQ_MAIN,
    JABU_JABUS_BELLY_MQ_DEPTHS,
    JABU_JABUS_BELLY_MQ_BOSS_AREA,
    FOREST_TEMPLE_MQ_LOBBY,
    FOREST_TEMPLE_MQ_CENTRAL_AREA,
    FOREST_TEMPLE_MQ_AFTER_BLOCK_PUZZLE,
    FOREST_TEMPLE_MQ_OUTDOOR_LEDGE,
    FOREST_TEMPLE_MQ_NW_OUTDOORS,
    FOREST_TEMPLE_MQ_NE_OUTDOORS,
    FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES,
    FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE,
    FOREST_TEMPLE_MQ_BOW_REGION,
    FOREST_TEMPLE_MQ_FALLING_ROOM,
    FOREST_TEMPLE_MQ_BOSS_REGION,
    FIRE_TEMPLE_MQ_LOWER,
    FIRE_TEMPLE_MQ_LOWER_LOCKED_DOOR,
    FIRE_TEMPLE_MQ_BIG_LAVA_ROOM,
    FIRE_TEMPLE_MQ_LOWER_MAZE,
    FIRE_TEMPLE_MQ_UPPER_MAZE,
    FIRE_TEMPLE_MQ_UPPER,
    FIRE_TEMPLE_MQ_BOSS_ROOM,
    WATER_TEMPLE_MQ_LOBBY,
    WATER_TEMPLE_MQ_DIVE,
    WATER_TEMPLE_MQ_LOWERED_WATER_LEVELS,
    WATER_TEMPLE_MQ_DARK_LINK_REGION,
    WATER_TEMPLE_MQ_BASEMENT_GATED_AREAS,
    SPIRIT_TEMPLE_MQ_LOBBY,
    SPIRIT_TEMPLE_MQ_CHILD,
    SPIRIT_TEMPLE_MQ_ADULT,
    SPIRIT_TEMPLE_MQ_SHARED,
    SPIRIT_TEMPLE_MQ_LOWER_ADULT,
    SPIRIT_TEMPLE_MQ_BOSS_AREA,
    SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND,
    SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND,
    SHADOW_TEMPLE_MQ_ENTRYWAY,
    SHADOW_TEMPLE_MQ_BEGINNING,
    SHADOW_TEMPLE_MQ_DEAD_HAND_AREA,
    SHADOW_TEMPLE_MQ_FIRST_BEAMOS,
    SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT,
    SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT,
    SHADOW_TEMPLE_MQ_WIND_TUNNEL,
    SHADOW_TEMPLE_MQ_BEYOND_BOAT,
    SHADOW_TEMPLE_MQ_INVISIBLE_MAZE,
    BOTTOM_OF_THE_WELL_MQ,
    BOTTOM_OF_THE_WELL_MQ_PERIMETER,
    BOTTOM_OF_THE_WELL_MQ_MIDDLE,
    ICE_CAVERN_MQ_BEGINNING,
    ICE_CAVERN_MQ_MAP_ROOM,
    ICE_CAVERN_MQ_IRON_BOOTS_REGION,
    ICE_CAVERN_MQ_COMPASS_ROOM,
    GERUDO_TRAINING_GROUNDS_MQ_LOBBY,
    GERUDO_TRAINING_GROUNDS_MQ_RIGHT_SIDE,
    GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER,
    GERUDO_TRAINING_GROUNDS_MQ_LEFT_SIDE,
    GERUDO_TRAINING_GROUNDS_MQ_STALFOS_ROOM,
    GERUDO_TRAINING_GROUNDS_MQ_BACK_AREAS,
    GERUDO_TRAINING_GROUNDS_MQ_CENTRAL_MAZE_RIGHT,
    GANONS_CASTLE_MQ_LOBBY,
    GANONS_CASTLE_MQ_DEKU_SCRUBS,
    GANONS_CASTLE_MQ_FOREST_TRIAL,
    GANONS_CASTLE_MQ_FIRE_TRIAL,
    GANONS_CASTLE_MQ_WATER_TRIAL,
    GANONS_CASTLE_MQ_SHADOW_TRIAL,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL,
    GANONS_CASTLE_MQ_LIGHT_TRIAL,
  };

  void AccessReset() {
    for (const AreaKey area : allAreas) {
      AreaTable(area)->ResetVariables();
    }

    if(Settings::HasNightStart) {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          AreaTable(ROOT)->childNight = true;
        } else {
          AreaTable(ROOT)->adultNight = true;
        }
      } else {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          AreaTable(ROOT)->childDay = true;
        } else {
          AreaTable(ROOT)->adultDay = true;
        }
    }
  }

  //Reset exits and clear items from locations
  void ResetAllLocations() {
    for (const AreaKey area : allAreas) {
      AreaTable(area)->ResetVariables();
      //Erase item from every location in this exit
      for (LocationAccess& locPair : AreaTable(area)->locations) {
          LocationKey location = locPair.GetLocation();
          Location(location)->ResetVariables();
      }
    }

    if(Settings::HasNightStart) {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          AreaTable(ROOT)->childNight = true;
        } else {
          AreaTable(ROOT)->adultNight = true;
        }
      } else {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          AreaTable(ROOT)->childDay = true;
        } else {
          AreaTable(ROOT)->adultDay = true;
        }
    }
  }

  bool HasTimePassAccess(u8 age) {
    for (const AreaKey areaKey : allAreas) {
      auto area = AreaTable(areaKey);
      if (area->timePass && ((age == AGE_CHILD && area->Child()) || (age == AGE_ADULT && area->Adult()))) {
        return true;
      }
    }
    return false;
  }

  // Will dump a file which can be turned into a visual graph using graphviz
  // https://graphviz.org/download/
  // Use command: dot -Tsvg <filename> -o world.svg
  // Then open in a browser and CTRL + F to find the area of interest
  void DumpWorldGraph(std::string str) {
    std::ofstream worldGraph;
    worldGraph.open (str + ".dot");
    worldGraph << "digraph {\n\tcenter=true;\n";

    for (const AreaKey areaKey : allAreas) {
      auto area = AreaTable(areaKey);
      for (auto exit : area->exits) {
        if (exit.GetConnectedRegion()->regionName != "Invalid Area") {
          std::string parent = exit.GetParentRegion()->regionName;
          if (area->childDay) {
            parent += " CD";
          }
          if (area->childNight) {
            parent += " CN";
          }
          if (area->adultDay) {
            parent += " AD";
          }
          if (area->adultNight) {
            parent += " AN";
          }
          Area* connected = exit.GetConnectedRegion();
          auto connectedStr = connected->regionName;
          if (connected->childDay) {
            connectedStr += " CD";
          }
          if (connected->childNight) {
            connectedStr += " CN";
          }
          if (connected->adultDay) {
            connectedStr += " AD";
          }
          if (connected->adultNight) {
            connectedStr += " AN";
          }
          worldGraph << "\t\"" + parent + "\"[shape=\"plain\"];\n";
          worldGraph << "\t\"" + connectedStr + "\"[shape=\"plain\"];\n";
          worldGraph << "\t\"" + parent + "\" -> \"" + connectedStr + "\"\n";
        }
      }
    }
    worldGraph << "}";
    worldGraph.close();
  }

} //namespace Areas

Area* AreaTable(const AreaKey areaKey) {
  if (areaKey > KEY_ENUM_MAX) {
    printf("\x1b[1;1HERROR: AREAKEY TOO BIG");
  }
  return &(areaTable[areaKey]);
}

//Retrieve all the shuffable entrances of a specific type
std::vector<Entrance*> GetShuffleableEntrances(EntranceType type, bool onlyPrimary /*= true*/) {
  std::vector<Entrance*> entrancesToShuffle = {};
  for (AreaKey area: Areas::allAreas) {
    for (auto& exit: AreaTable(area)->exits) {
      if ((exit.GetType() == type || type == EntranceType::All) && (exit.IsPrimary() || !onlyPrimary) && exit.GetType() != EntranceType::None) {
        entrancesToShuffle.push_back(&exit);
      }
    }
  }
  return entrancesToShuffle;
}
