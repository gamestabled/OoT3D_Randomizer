#pragma once

#include <vector>

class ItemLocation;

enum class SearchMode {
    ReachabilitySearch,
    GeneratePlaythrough,
    CheckBeatable,
};

int Fill();

std::vector<ItemLocation*> GetAccessibleLocations(const std::vector<ItemLocation*>& allowedLocations,
                                                  SearchMode mode = SearchMode::ReachabilitySearch);
