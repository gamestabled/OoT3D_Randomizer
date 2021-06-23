#include "spoiler_data.h"

SpoilerData gSpoilerData = { 0 };

char* SpoilerData_GetItemLocationString(u16 itemIndex) {
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].LocationOffset];
}

char* SpoilerData_GetItemNameString(u16 itemIndex) {
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].ItemOffset];
}
