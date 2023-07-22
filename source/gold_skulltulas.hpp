#pragma once

#include <3ds.h>
#include <vector>
#include <string_view>
#include <map>

#include "location_access.hpp"
#include "../code/src/actors/skulltula.h"

namespace GoldSkulltulas {

// typedefs for readability
typedef s16 GsScene;
typedef s8 Room;
typedef ConditionFn SettingRequirements;

class GsLocData {
  public:
    /// For original location
    GsLocData(AreaKey areaKey_, GsScene scene_, Room room_, std::vector<ConditionFn> logic_);
    /// For new location with same scene and room
    GsLocData(AreaKey areaKey_, std::string_view description_, GsTimeCondition timeCondition_,
              SettingRequirements settingRequirements_, PosRot posRot_, std::vector<ConditionFn> logic_);
    /// For new location with new scene or room
    GsLocData(AreaKey areaKey_, std::string_view description_, GsScene scene_, Room room_,
              GsTimeCondition timeCondition_, SettingRequirements settingRequirements_, PosRot posRot_,
              std::vector<ConditionFn> logic_);
    ~GsLocData();

    /// The area the GS will be placed in the area table.
    const AreaKey areaKey;
    /// A summary of where the GS is in the area.
    const std::string_view description;
    /// The scene index the GS will appear in.
    /// When -1, original scene is used.
    const GsScene scene;
    /// The room number the GS will appear in.
    /// When -1, original scene is used.
    const Room room;
    /// The time of day the GS appears at. Can be either at night, or always.
    const GsTimeCondition timeCondition;
    /// The required settings for this location to be used.
    /// When no function is specified, assume no requirements.
    const SettingRequirements settingRequirements;
    /// The new world position and rotation the GS will spawn at.
    const PosRot posRot;
    /// The logic for this new location.
    /// When no functions are specified, the original is used.
    const std::vector<ConditionFn> logic;
};

class GoldSkulltulaData {
  public:
    GoldSkulltulaData(LocationKey locationKey_, u8 arrayIndex_, u8 bitFlag_, GsAgeCondition ageCondition_,
                      ConditionFn relevancyCheck_, GsLocData baseData_, std::vector<GsLocData> newDatas_);
    ~GoldSkulltulaData();

    /// If relevant, assign location and add to area table.
    void SetLocation();
    /// Returns true if this GS has been added to the area table.
    const bool IsRelevant();
    /// Returns the assigned location.
    const GsLocData* GetAssignedLocation();

  private:
    /// Location key this GS represents.
    const LocationKey locationKey;
    /// Array index of gsFlags in gSaveContext
    const u8 arrayIndex;
    /// Bit flag of gsFlags in gSaveContext
    const u8 bitFlag;
    /// What age the GS appears in. (Both for dungeons)
    const GsAgeCondition ageCondition;
    /// If it should be added to logic and override array in patch.
    /// Assumed true when unset.
    const ConditionFn relevancyCheck;
    /// Area key and logic for original position.
    const GsLocData originalLocation;
    /// List of new locations.
    const std::vector<GsLocData> newLocations;

    /// The assigned location this Gold Skulltula has.
    /// A null pointer is treated as the original location.
    const GsLocData* assignedLocation = nullptr;
};

} // namespace GoldSkulltulas

extern std::map<LocationKey, GoldSkulltulas::GoldSkulltulaData*> gsTable;

/// Adds all Gold Skulltulas to the area table.
void Gs_AssignLocations();
/// Checks if the Gold Skulltula has a new location.
/// Contains a safety check to make sure the location key is correct.
bool Gs_IsMoved(LocationKey locationKey);
/// Returns a pointer to the override vector.
const std::vector<GsLocOverride>* Gs_GetOverrideData();

// Overworld
void GsTable_Init_LostWoods();
void GsTable_Init_Kakariko();
void GsTable_Init_DeathMountain();
void GsTable_Init_ZorasDomain();
void GsTable_Init_HyruleField();
void GsTable_Init_GerudoValley();
void GsTable_Init_CastleTown();
// Dungeons
void GsTable_Init_DekuTree();
void GsTable_Init_ForestTemple();
