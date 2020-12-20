#pragma once
#include <string_view>
#include <vector>
#include "item_location.hpp"

bool SpoilerLog_Write();

void PlacementLog_Msg(std::string_view msg);
bool PlacementLog_Write();
