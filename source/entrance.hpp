#pragma once

#include "keys.hpp"
#include "location_access.hpp"
#include "debug.hpp"

enum class EntranceType {
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
    None,
};

class Entrance {
public:

    Entrance();
    Entrance(EntranceType type_, AreaKey parentRegion_, AreaKey connectedRegion_, s16 index_, s16 blueWarp_);
    ~Entrance();

    std::string GetName() {
        return AreaTable(parentRegion)->regionName + " -> " + AreaTable(connectedRegion)->regionName;
    }

    AreaKey GetParentRegion() const {
        return parentRegion;
    }

    AreaKey GetConnectedRegion() const {
        return connectedRegion;
    }

    s16 GetIndex() const {
        return index;
    }

    EntranceType GetType() const {
        return type;
    }

    void SetAsPrimary() {
        primary = true;
        AreaTable(parentRegion)->SetAsPrimary(connectedRegion);
    }

    bool IsPrimary() const {
        return primary;
    }

    void SetAsShuffled() {
        shuffled = true;
    }

    void SetTarget(Entrance* newTarget) {
        target = newTarget;
    }

    Entrance* GetTarget() const {
      if (target == nullptr) {
        CitraPrint("Target is nullptr");
      }
      return target;
    }

    void SetReverse(Entrance* newReverse) {
        reverse = newReverse;
    }

    Entrance* GetReverse() const {
        return reverse;
    }

    void SetReplacement(Entrance* newReplacement) {
        replaces = newReplacement;
    }

    AreaKey Disconnect() {
        AreaTable(parentRegion)->DisconnectExit(connectedRegion);
        AreaTable(connectedRegion)->DisconnectExit(parentRegion);
        AreaKey previouslyConnected = connectedRegion;
        connectedRegion = NONE;
        return previouslyConnected;
    }

    void BindTwoWay(Entrance otherEntrance) {
        otherEntrance.SetReverse(this);
        reverse = &otherEntrance;
    }

    Entrance* GetNewTarget() {
        auto targetEntrance = Entrance{type, ROOT, connectedRegion, index, blueWarp};
        targetEntrance.SetReplacement(this);
        AreaTable(ROOT)->AddExit(connectedRegion, []{return true;});
        return &targetEntrance;
    }

    Entrance AssumeReachable() {
        if (assumed == nullptr) {
            assumed = GetNewTarget();
            this->Disconnect();
        }
        return *assumed;
    }

    static auto Dungeon(AreaKey parentRegion_, AreaKey connectedRegion_, s16 index_, s16 blueWarp_ = 0x0000) {
        return Entrance{EntranceType::Dungeon, parentRegion_, connectedRegion_, index_, blueWarp_};
    }

    static auto Overworld(AreaKey parentRegion_, AreaKey connectedRegion_, s16 index_) {
        return Entrance{EntranceType::Overworld, parentRegion_, connectedRegion_, index_, 0x0000};
    }

    bool operator==(const Entrance& right) {
        return this->parentRegion == right.GetParentRegion() && this->connectedRegion == right.GetConnectedRegion() && this->index == right.GetIndex();
    }

    bool operator!=(const Entrance& right) {
        return !operator==(right);
    }

private:
    EntranceType type;
    AreaKey parentRegion;
    AreaKey connectedRegion;
    Entrance* target   = nullptr;
    Entrance* reverse  = nullptr;
    Entrance* assumed  = nullptr;
    Entrance* replaces = nullptr;
    s16 index;
    s16 blueWarp;
    bool primary = false;
    bool shuffled = false;
};

void ShuffleAllEntrances();
