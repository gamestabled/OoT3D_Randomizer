#pragma once

#include <string>
#include <vector>
#include "locations/new_item_location.hpp"

#include "../code/include/z3D/z3D.h"

class NewItem;

class NewPlaythrough {
public:
    NewPlaythrough(u32 seed);
    static void repeat(int count = 1);

    void fill();
    void placeItemInLocation(NewItemLocation* location, NewItem* item, bool applyEffectImmediately = false, bool setHidden = false);

    std::vector<NewItemLocation*> allLocations;
    std::vector<NewItemLocation*> playthroughLocations;
    std::vector<NewItemLocation*> wothLocations;
    // AreaTable areaTable;

    std::vector<NewItem*> itemPool;
    std::vector<GetItemID> iceTrapModels;
    
    bool placementFailure = false;
    bool showItemProgress = false;
    bool beatable = false;
    int itemsPlaced = 0;
private:
    void generateHash();
    void generateLocationPool();
    NewItem* getJunkItem();
    void addItemToMainPool(NewItem* item, size_t count = 1);
    void generateItemPool();
    void addLocation(NewItemLocation* loc, std::vector<NewItemLocation*>& dest);
    void addLocation(NewItemLocation* loc);

    template <typename Container>
    void addLocations(const Container& locations, std::vector<NewItemLocation*>& destination);
    template <typename Container>

    void addLocations(const Container& locations);
    std::vector<NewItemLocation*> getAllEmptyLocations();

    std::vector<NewItemLocation*> getAccessibleLocations(const std::vector<NewItemLocation*>& allowedLocations /*mode? */);
    void assumedFill(const std::vector<NewItem*>& items, const std::vector<NewItemLocation*>& allowedLocations, bool setLocationsAsHintable = false);
    void fastFill(std::vector<NewItem*> items, std::vector<NewItemLocation*> locations, bool endOnItemsEmpty = false);

};
