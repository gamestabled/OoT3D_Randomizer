#pragma once

#include "new_item.hpp"

class NewItemTable {
public:
    NewItemTable();

    void reset();

    inline static NewItem none; //TODO give this default values

    /* Kokiri Forest */
    NewItem kokiriSword;
    // NewItem masterSword;
    NewItem giantsKnife;
    NewItem biggoronSword;
    NewItem dekuShield;
    NewItem hylianShield;
    NewItem mirrorShield;
    //TODO ...
};
