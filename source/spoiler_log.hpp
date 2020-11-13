#pragma once
#include "item_location.hpp"

extern void SpoilerLog_SaveLocation(const char *loc, const char *item);
extern bool SpoilerLog_Write();
extern void PlacementLog_Msg(const char *msg);
extern bool PlacementLog_Write();
