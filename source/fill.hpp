#pragma once

#include <vector>

#include <3ds.h>

enum class SearchMode {
    ReachabilitySearch,
    GeneratePlaythrough,
    CheckBeatable,
};

int Fill();

std::vector<u32> GetAccessibleLocations(const std::vector<u32>& allowedLocations,
                                                  SearchMode mode = SearchMode::ReachabilitySearch);
