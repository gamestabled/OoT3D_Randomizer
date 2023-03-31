#include "gold_skulltulas.hpp"
#include "random.hpp"

#include <unordered_map>

using namespace GoldSkulltulas;

GsLocData::GsLocData(AreaKey areaKey_, GsScene scene_, Room room_, std::vector<ConditionFn> logic_)
    : areaKey(areaKey_), description(""), scene(scene_), room(room_), timeCondition(), settingRequirements(nullptr),
      posRot(), logic(logic_) {
}

GsLocData::GsLocData(AreaKey areaKey_, std::string_view description_, GsTimeCondition timeCondition_,
                     SettingRequirements settingRequirements_, PosRot posRot_, std::vector<ConditionFn> logic_)
    : areaKey(areaKey_), description(description_), scene(-1), room(-1), timeCondition(timeCondition_),
      settingRequirements(settingRequirements_), posRot(posRot_), logic(logic_) {
}

GsLocData::GsLocData(AreaKey areaKey_, std::string_view description_, GsScene scene_, Room room_,
                     GsTimeCondition timeCondition_, SettingRequirements settingRequirements_, PosRot posRot_,
                     std::vector<ConditionFn> logic_)
    : areaKey(areaKey_), description(description_), scene(scene_), room(room_), timeCondition(timeCondition_),
      settingRequirements(settingRequirements_), posRot(posRot_), logic(logic_) {
}

GsLocData::~GsLocData() = default;

static std::vector<GsLocOverride> gsOverrideData;

GoldSkulltulaData::GoldSkulltulaData(LocationKey locationKey_, u8 arrayIndex_, u8 bitFlag_,
                                     GsAgeCondition ageCondition_, ConditionFn relevancyCheck_, GsLocData baseData_,
                                     std::vector<GsLocData> newDatas_)
    : locationKey(locationKey_), arrayIndex(arrayIndex_), bitFlag(bitFlag_), ageCondition(ageCondition_),
      relevancyCheck(relevancyCheck_), originalLocation(baseData_), newLocations(newDatas_) {
}

GoldSkulltulaData::~GoldSkulltulaData() = default;

void GoldSkulltulaData::SetLocation() {
    assignedLocation = nullptr;

    if (!IsRelevant()) {
        return;
    }

    if (!Settings::RandomGsLocations) {
        AreaTable(originalLocation.areaKey)->AddLocation(LocationAccess(locationKey, originalLocation.logic));
        return;
    }

    std::vector<const GsLocData*> availableNewLocations;
    availableNewLocations.reserve(newLocations.size() + 1);
    if (!Settings::GsLocGuaranteeNew) {
        // Treat nullptr as original location
        availableNewLocations.push_back(nullptr);
    }
    for (auto& newData : newLocations) {
        if (newData.settingRequirements == nullptr || newData.settingRequirements() || Settings::Logic.Is(LOGIC_NONE)) {
            availableNewLocations.push_back(&newData);
        }
    }

    if (!availableNewLocations.empty()) {
        assignedLocation = RandomElement(availableNewLocations);
    }

    if (availableNewLocations.empty() || assignedLocation == nullptr) {
        AreaTable(originalLocation.areaKey)->AddLocation(LocationAccess(locationKey, originalLocation.logic));
        return;
    }

    auto logic = assignedLocation->logic;
    if (logic.empty()) {
        logic = originalLocation.logic;
    }
    auto scene = assignedLocation->scene;
    if (scene == -1) {
        scene = originalLocation.scene;
    }
    auto room = assignedLocation->room;
    if (room == -1) {
        room = originalLocation.room;
    }

    AreaTable(assignedLocation->areaKey)->AddLocation(LocationAccess(locationKey, logic));
    gsOverrideData.push_back(
        { arrayIndex, bitFlag, scene, room, ageCondition, assignedLocation->timeCondition, assignedLocation->posRot });
}

const bool GoldSkulltulas::GoldSkulltulaData::IsRelevant() {
    return relevancyCheck == nullptr || relevancyCheck();
}

const GsLocData* GoldSkulltulas::GoldSkulltulaData::GetAssignedLocation() {
    return assignedLocation;
}

std::map<LocationKey, GoldSkulltulaData*> gsTable;

void Gs_AssignLocations() {
    static bool gsInit = false;
    if (gsInit == false) {
        // Overworld
        GsTable_Init_LostWoods();
        GsTable_Init_Kakariko();
        GsTable_Init_DeathMountain();
        GsTable_Init_ZorasDomain();
        GsTable_Init_HyruleField();
        GsTable_Init_GerudoValley();
        GsTable_Init_CastleTown();
        // Dungeons
        GsTable_Init_DekuTree();
        GsTable_Init_ForestTemple();
        gsInit = true;
    }

    gsOverrideData.clear();
    for (auto gsData : gsTable) {
        gsData.second->SetLocation();
    }
}

bool Gs_IsMoved(LocationKey locationKey) {
    return gsTable.find(locationKey) != gsTable.end() && gsTable[locationKey]->GetAssignedLocation() != nullptr;
}

const std::vector<GsLocOverride>* Gs_GetOverrideData() {
    return &gsOverrideData;
}
