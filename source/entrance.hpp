#pragma once

#include "keys.hpp"
#include "location_access.hpp"
#include "debug.hpp"

#include <string>
#include <list>

#include "../code/src/entrance.h"

extern std::list<EntranceOverride> entranceOverrides;

enum class EntranceType {
    None,
    Dungeon,
    Interior,
    SpecialInterior,
    Grotto,
    Grave,
    Overworld,
    OwlDrop,
    Spawn,
    WarpSong,
    Extra,
    All,
};

class Entrance {
public:

    Entrance(AreaKey connectedRegion_, ConditionFn conditionsMet_)
        : connectedRegion(connectedRegion_), conditionsMet(conditionsMet_) {}

    std::string to_string() const {
        return AreaTable(parentRegion)->regionName + " -> " + AreaTable(connectedRegion)->regionName;
    }

    void SetName() {
        name = AreaTable(parentRegion)->regionName + " -> " + AreaTable(connectedRegion)->regionName;
    }

    std::string GetName() const {
        return name;
    }

    bool ConditionsMet(bool allAgeTimes = false) const {

        Area* parent = AreaTable(parentRegion);
        bool conditionsMet = false;

        if (allAgeTimes && !parent->AllAccess()) {
            return false;
        }

        //check all possible day/night condition combinations
        if ((parent->childDay   && CheckConditionAtAgeTime(Logic::IsChild, Logic::AtDay))   ||
            (parent->childNight && CheckConditionAtAgeTime(Logic::IsChild, Logic::AtNight)) ||
            (parent->adultDay   && CheckConditionAtAgeTime(Logic::IsAdult, Logic::AtDay))   ||
            (parent->adultNight && CheckConditionAtAgeTime(Logic::IsAdult, Logic::AtNight))) {
              conditionsMet = true;
        }

        return conditionsMet && connected;
    }

    AreaKey GetAreaKey() const {
        return connectedRegion;
    }

    //set the logic to be a specific age and time of day and see if the condition still holds
    bool CheckConditionAtAgeTime(bool& age, bool& time) const {
        bool prevIsChild = Logic::IsChild;
        bool prevIsAdult = Logic::IsAdult;
        bool prevAtDay   = Logic::AtDay;
        bool prevAtNight = Logic::AtNight;

        Logic::IsChild = false;
        Logic::IsAdult = false;
        Logic::AtDay   = false;
        Logic::AtNight = false;

        time = true;
        age = true;

        Logic::UpdateHelpers();
        bool checkCondition = conditionsMet();

        Logic::IsChild = prevIsChild;
        Logic::IsAdult = prevIsAdult;
        Logic::AtDay   = prevAtDay;
        Logic::AtNight = prevAtNight;

        return checkCondition;
    }

    //Yes this is the exact same function as above, trust me on this
    AreaKey GetConnectedRegionKey() const {
        return connectedRegion;
    }

    Area* GetConnectedRegion() const {
        return AreaTable(connectedRegion);
    }

    void SetParentRegion(AreaKey newParent) {
        parentRegion = newParent;
    }

    AreaKey GetParentRegionKey() const {
        return parentRegion;
    }

    Area* GetParentRegion() const {
        return AreaTable(parentRegion);
    }

    void SetNewEntrance(AreaKey newRegion) {
        connectedRegion = newRegion;
    }

    void SetAsShuffled() {
        shuffled = true;
    }

    void SetAsPrimary() {
        primary = true;
    }

    bool IsPrimary() const {
        return primary;
    }

    s16 GetIndex() const {
        return index;
    }

    void SetIndex(s16 newIndex) {
        index = newIndex;
    }

    s16 GetBlueWarp() const {
        return blueWarp;
    }

    void SetBlueWarp(s16 newBlueWarp) {
        blueWarp = newBlueWarp;
    }

    Entrance* GetAssumed() const {
        return assumed;
    }

    void SetReplacement(Entrance* newReplacement) {
        replacement = newReplacement;
    }

    Entrance* GetReplacement() const {
        return replacement;
    }

    EntranceType GetType() const {
        return type;
    }

    void SetType(EntranceType newType) {
        type = newType;
    }

    Entrance* GetReverse() const {
        return reverse;
    }

    void Connect(AreaKey newConnectedRegion) {
        connectedRegion = newConnectedRegion;
    }

    AreaKey Disconnect() {
        AreaKey previouslyConnected = connectedRegion;
        connectedRegion = NONE;
        return previouslyConnected;
    }

    void BindTwoWay(Entrance* otherEntrance) {
        reverse = otherEntrance;
        otherEntrance->reverse = this;
    }

    Entrance* GetNewTarget() {
        AreaTable(ROOT)->AddExit(ROOT, connectedRegion, []{return true;});
        Entrance* targetEntrance = AreaTable(ROOT)->GetExit(connectedRegion);
        targetEntrance->SetReplacement(this);
        return targetEntrance;
    }

    Entrance* AssumeReachable() {
        if (assumed == nullptr) {
            assumed = GetNewTarget();
            Disconnect();
        }
        return assumed;
    }

    void TempDisconnect() {
        connected = false;
    }

    void Reconnect() {
        connected = true;
    }

private:
    AreaKey parentRegion;
    AreaKey connectedRegion;
    ConditionFn conditionsMet;

    //Entrance Randomizer stuff
    EntranceType type = EntranceType::None;
    Entrance* target = nullptr;
    Entrance* reverse = nullptr;
    Entrance* assumed = nullptr;
    Entrance* replacement = nullptr;
    s16 index = 0xFFFF;
    s16 blueWarp = 0;
    bool shuffled = false;
    bool primary = false;
    bool connected = true;
    std::string name = "";
};

void ShuffleAllEntrances();
void CreateEntranceOverrides();
