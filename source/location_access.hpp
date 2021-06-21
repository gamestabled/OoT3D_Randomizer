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

    bool CheckConditionAtAgeTime(bool& age, bool& time) {
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
      bool checkCondition = conditions_met();

      Logic::IsChild = prevIsChild;
      Logic::IsAdult = prevIsAdult;
      Logic::AtDay   = prevAtDay;
      Logic::AtNight = prevAtNight;

      return checkCondition;
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

    bool CheckConditionAtAgeTime(bool& age, bool& time) const;

    bool ConditionsMet() const;

    LocationKey GetLocation() const {
        return location;
    }

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
    //entrance pointers.

    bool childDay = false;
    bool childNight = false;
    bool adultDay = false;
    bool adultNight = false;
    bool addedToPool = false;

    //These variables are used to keep track of an areas final reachable state
    //within the world graph. By default everything is true, because this state
    //is used to determine if we don't need to check an area anymore in the
    //search algorithm. In the worst case, all of these will be true.
    bool finalChildDay = true;
    bool finalChildNight = true;
    bool finalAdultDay = true;
    bool finalAdultNight = true;

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

    void SaveFinalState() {
      // finalChildDay   = childDay;
      // finalChildNight = childNight;
      // finalAdultDay   = adultDay;
      // finalAdultNight = adultNight;
    }

    bool ReachedFinalState() const {
      return childDay   == finalChildDay   &&
             childNight == finalChildNight &&
             adultDay   == finalAdultDay   &&
             adultNight == finalAdultNight;
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
      childDay = false;
      childNight = false;
      adultDay = false;
      adultNight = false;
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
void SaveAreaStates();
