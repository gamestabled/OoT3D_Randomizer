#pragma once

#include <string>
#include <vector>

#include "logic.hpp"
#include "hint_list.hpp"
#include "keys.hpp"

using ConditionFn = bool (*)();

class EventAccess {
public:


    explicit EventAccess(bool* event_, ConditionFn conditions_met_)
        : event(event_),
          conditions_met(conditions_met_) {}

    bool ConditionsMet() const {
        return conditions_met();
    }

    void EventOccurred() {
        *event = true;
    }

    bool GetEvent() const {
        return *event;
    }

private:
    bool* event;
    ConditionFn conditions_met;
};

//this class is meant to hold an item location with a boolean function to determine its accessibility from a specific area
class LocationAccess {
public:

    explicit LocationAccess(LocationKey location_, ConditionFn conditions_met_)
         : location(location_),
           conditions_met(conditions_met_) {}

    bool ConditionsMet() const {
        return conditions_met() && CanBuy();
    }

    LocationKey GetLocation() const {
        return location;
    }

    bool IsLocationUsed() const;

private:
    LocationKey location;
    ConditionFn conditions_met;

    //Makes sure shop locations are buyable
    bool CanBuy() const;
};

class Exit {
public:

    enum class Time {
      Day,
      Night,
      Both,
    };

    Exit(AreaKey exit_, ConditionFn conditions_met_, Time time_of_day_ = Time::Both)
        : exit(exit_), conditions_met(conditions_met_), time_of_day(time_of_day_), originalExit(exit_) {}

    bool IsBoth() const {
        return time_of_day == Exit::Time::Both;
    }

    bool IsDay() const {
        return time_of_day == Exit::Time::Day;
    }

    bool IsNight() const {
        return time_of_day == Exit::Time::Night;
    }

    Time TimeOfDay() const {
        return time_of_day;
    }

    void SetOriginalIndex(s16 index_) {
        originalIndex = index_;
    }

    bool ConditionsMet() const {
        return conditions_met() && connected;
    }

    AreaKey GetAreaKey() const {
        return exit;
    }

    void SetNewExit(AreaKey newExit) {
        exit = newExit;
    }

    void Disconnect() {
        connected = false;
    }

    void SetAsPrimary() {
        primary = true;
    }

    void RevertToOriginalExit() {
        exit = originalExit;
    }

    static Exit Both(AreaKey exit, ConditionFn condition) {
        return Exit{exit, condition, Time::Both};
    }

    static Exit Day(AreaKey exit, ConditionFn condition) {
        return Exit{exit, condition, Time::Day};
    }

    static Exit Night(AreaKey exit, ConditionFn condition) {
        return Exit{exit, condition, Time::Night};
    }

private:
    AreaKey exit;
    ConditionFn conditions_met;
    Time time_of_day;

    //Entrance Randomizer stuff
    s16 originalIndex = 0xFFFF;
    s16 replacedIndex = 0xFFFF;
    bool shuffled = false;
    bool primary = false;
    bool connected = true;
    AreaKey originalExit;
};

class Area {
public:
    Area();
    Area(std::string regionName_, std::string scene_, HintKey hintKey_,
         bool timePass_,
         std::vector<EventAccess> events_,
         std::vector<LocationAccess> locations_,
         std::vector<Exit> exits_);
    ~Area();

    std::string regionName;
    std::string scene;
    HintKey     hintKey;
    bool        timePass;
    std::vector<EventAccess> events;
    std::vector<LocationAccess> locations;
    std::vector<Exit> exits;

    bool dayChild = false;
    bool nightChild = false;
    bool dayAdult = false;
    bool nightAdult = false;
    bool addedToPool = false;

    void UpdateEvents();

    void AddExit(AreaKey newExit, ConditionFn condition, Exit::Time timeOfDay = Exit::Time::Both);

    void RemoveExit(AreaKey exitToRemove);

    void DisconnectExit(AreaKey exitToDisconnect);

    void SetAsPrimary(AreaKey exitToBePrimary);

    void SetOriginalExitIndex(AreaKey exitToSetIndex, s16 originalIndex_);

    bool Child() const {
      return dayChild || nightChild;
    }

    bool Adult() const {
      return dayAdult || nightAdult;
    }

    bool BothAgesCheck() const {
      return Child() && Adult();
    }

    bool HasAccess() const {
      return Child() || Adult();
    }

    bool AllAccess() const {
      return dayChild && nightChild && dayAdult && nightAdult;
    }

    const HintText& GetHint() const {
      return Hint(hintKey);
    }

    //Here checks conditional access based on whether or not both ages have
    //access to this exit. For example: if there are rocks that block a path
    //which both child and adult can access, adult having hammer can give
    //both child and adult access to the path.
    bool HereCheck(ConditionFn condition) {

      //store current age variables
      bool pastAdult = Logic::IsAdult;
      bool pastChild = Logic::IsChild;

      //set age access as this exits ages
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

    void ResetVariables() {
      dayChild = false;
      nightChild = false;
      dayAdult = false;
      nightAdult = false;
      addedToPool = false;
    }
};

namespace Areas {

  extern void  AccessReset();
  extern void  ResetAllLocations();
} //namespace Exits

void  AreaTable_Init();
Area* AreaTable(const AreaKey areaKey);
