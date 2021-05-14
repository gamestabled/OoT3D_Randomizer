#pragma once

#include <vector>

extern int Fill();

class ItemLocation;
enum SearchMode {REACHABILITY_SEARCH, GENERATE_PLAYTHROUGH, CHECK_BEATABLE};
extern std::vector<ItemLocation*> GetAccessibleLocations(std::vector<ItemLocation*> allowedLocations, SearchMode mode = REACHABILITY_SEARCH);
