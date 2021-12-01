#pragma once

#include <3ds.h>

#include "keys.hpp"

#include <vector>
#include <string>

enum class SearchMode {
    ReachabilitySearch,
    GeneratePlaythrough,
    CheckBeatable,
    AllLocationsReachable,
    BothAgesNoItems,
    PoeCollectorAccess,
};

void VanillaFill();
int Fill();

std::vector<LocationKey> GetAccessibleLocations(const std::vector<LocationKey>& allowedLocations, SearchMode mode = SearchMode::ReachabilitySearch, std::string ignore = "");
