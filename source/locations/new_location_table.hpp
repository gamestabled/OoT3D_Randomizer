#pragma once

#include "new_item_location.hpp"

class NewLocationTable {
public:
    NewLocationTable();

    void reset();

    NewItemLocation none;

    /* Kokiri Forest */
    NewItemLocation KF_kokiriSwordChest;
    NewItemLocation KF_midosTopLeftChest;
    NewItemLocation KF_midosTopRightChest;
    NewItemLocation KF_midosBottomLeftChest;
    NewItemLocation KF_midosBottomRightChest;
    NewItemLocation KF_stormsGrottoChest;

};
