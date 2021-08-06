#pragma once

#include <string>
#include <vector>
#include <list>

#include "logic.hpp"
#include "hint_list.hpp"
#include "keys.hpp"

typedef bool (*ConditionFn)();

class EventAccess {
public:


    explicit EventAccess(bool* event_, std::vector<ConditionFn> conditions_met_)
        : event(event_) {
        conditions_met.resize(2);
        for (size_t i = 0; i < conditions_met_.size(); i++) {
            conditions_met[i] = conditions_met_[i];
        }
    }

    bool ConditionsMet() const {
        if (Settings::Logic.Is(LOGIC_NONE) || Settings::Logic.Is(LOGIC_VANILLA)) {
            return true;
        }
        for (size_t i = 0; i <= Settings::Logic.Value<u8>(); i++) {
            if (conditions_met[i] == NULL) {
                continue;
            }
            if (conditions_met[i]()) {
                return true;
            }
        }
        return false;
    }

    bool CheckConditionAtAgeTime(bool& age, bool& time) {

        Logic::IsChild = false;
        Logic::IsAdult = false;
        Logic::AtDay   = false;
        Logic::AtNight = false;

        time = true;
        age = true;

        Logic::UpdateHelpers();
        return ConditionsMet();
    }

    void EventOccurred() {
        *event = true;
    }

    bool GetEvent() const {
        return *event;
    }

private:
    bool* event;
    std::vector<ConditionFn> conditions_met;
};

//this class is meant to hold an item location with a boolean function to determine its accessibility from a specific area
class LocationAccess {
public:

    explicit LocationAccess(LocationKey location_, std::vector<ConditionFn> conditions_met_)
        : location(location_) {
        conditions_met.resize(2);
        for (size_t i = 0; i < conditions_met_.size(); i++) {
            conditions_met[i] = conditions_met_[i];
        }
    }

    bool GetConditionsMet() const {
        if (Settings::Logic.Is(LOGIC_NONE) || Settings::Logic.Is(LOGIC_VANILLA)) {
            return true;
        }
        for (size_t i = 0; i <= Settings::Logic.Value<u8>(); i++) {
            if (conditions_met[i] == NULL) {
                continue;
            }
            if (conditions_met[i]()) {
                return true;
            }
        }
        return false;
    }

    bool CheckConditionAtAgeTime(bool& age, bool& time) const;

    bool ConditionsMet() const;

    LocationKey GetLocation() const {
        return location;
    }

private:
    LocationKey location;
    std::vector<ConditionFn> conditions_met;

    //Makes sure shop locations are buyable
    bool CanBuy() const;
};

class Entrance;
enum class EntranceType;

class Area {
public:
    Area();
    Area(std::string regionName_, std::string scene_, HintKey hintKey_,
         bool timePass_,
         std::vector<EventAccess> events_,
         std::vector<LocationAccess> locations_,
         std::list<Entrance> exits_);
    ~Area();

    std::string regionName;
    std::string scene;
    HintKey     hintKey;
    bool        timePass;
    std::vector<EventAccess> events;
    std::vector<LocationAccess> locations;
    std::list<Entrance> exits;
    //^ The above exits are now stored in a list instead of a vector because
    //the entrance randomization algorithm plays around with pointers to these
    //entrances a lot. By putting the entrances in a list, we don't have to
    //worry about a vector potentially reallocating itself and invalidating all our
    //entrance pointers.

    bool childDay = false;
    bool childNight = false;
    bool adultDay = false;
    bool adultNight = false;
    bool addedToPool = false;

    bool UpdateEvents();

    void AddExit(AreaKey parentKey, AreaKey newExitKey, ConditionFn condition);

    void RemoveExit(Entrance* exitToRemove);

    void DisconnectExit(AreaKey exitToDisconnect);

    void SetAsPrimary(AreaKey exitToBePrimary);

    Entrance* GetExit(AreaKey exit);

    bool Child() const {
        return childDay || childNight;
    }

    bool Adult() const {
        return adultDay || adultNight;
    }

    bool BothAgesCheck() const {
        return Child() && Adult();
    }

    bool HasAccess() const {
        return Child() || Adult();
    }

    bool AllAccess() const {
        return childDay && childNight && adultDay && adultNight;
    }

    //Check to see if an exit can be access as both ages at both times of day
    bool CheckAllAccess(AreaKey exitKey);

    const HintText& GetHint() const {
        return Hint(hintKey);
    }

    //Here checks conditional access based on whether or not both ages have
    //access to this area. For example: if there are rocks that block a path
    //which both child and adult can access, adult having hammer can give
    //both child and adult access to the path.
    bool HereCheck(ConditionFn condition) {

        //store current age variables
        bool pastAdult = Logic::IsAdult;
        bool pastChild = Logic::IsChild;

        //set age access as this areas ages
        Logic::IsChild = Child();
        Logic::IsAdult = Adult();

        //update helpers and check condition
        Logic::UpdateHelpers();
        bool hereVal = condition();

        //set back age variables
        Logic::IsChild = pastChild;
        Logic::IsAdult = pastAdult;
        Logic::UpdateHelpers();

        return hereVal;
    }

    bool CanPlantBeanCheck() const;
    bool AllAccountedFor() const;

    void ResetVariables();

    void printAgeTimeAccess() const {
        auto message = "Child Day:   " + std::to_string(childDay)   + "\t"
                       "Child Night: " + std::to_string(childNight) + "\t"
                       "Adult Day:   " + std::to_string(adultDay)   + "\t"
                       "Adult Night: " + std::to_string(adultNight);
        CitraPrint(message);
    }
};

namespace Areas {

    extern void AccessReset();
    extern void ResetAllLocations();
    extern bool HasTimePassAccess(u8 age);
} //namespace Exits

void  AreaTable_Init();
Area* AreaTable(const AreaKey areaKey);
std::vector<Entrance*> GetShuffleableEntrances(EntranceType type, bool onlyPrimary = true);
