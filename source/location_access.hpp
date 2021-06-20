#pragma once

#include <string>
#include <vector>
#include <list>

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
    //previous pointers.

    bool dayChild = false;
    bool nightChild = false;
    bool dayAdult = false;
    bool nightAdult = false;
    bool addedToPool = false;

    void UpdateEvents();

    void AddExit(AreaKey parentKey, AreaKey newExitKey, ConditionFn condition);

    void RemoveExit(Entrance* exitToRemove);

    void DisconnectExit(AreaKey exitToDisconnect);

    void SetAsPrimary(AreaKey exitToBePrimary);

    Entrance* GetExit(AreaKey exit);

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
std::vector<Entrance*> GetShuffleableEntrances(EntranceType type, bool onlyPrimary = true);
