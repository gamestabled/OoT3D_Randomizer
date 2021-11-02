#include "new_location_table.hpp"

// TODO, hints, vanilla placement, etc.

NewLocationTable::NewLocationTable() :
    none(std::move(NewItemLocation::Base(0xFF, 0xFF, "Invalid Location"))),

    KF_kokiriSwordChest(std::move(NewItemLocation::Base(0x55, 0x00, "KF Kokiri Sword Chest"))),
    KF_midosTopLeftChest(std::move(NewItemLocation::Chest(0x28, 0x00, "KF Mido Top Left Chest"))),
    KF_midosTopRightChest(std::move(NewItemLocation::Chest(0x28, 0x01, "KF Mido Top Right Chest"))),
    KF_midosBottomLeftChest(std::move(NewItemLocation::Chest(0x28, 0x02, "KF Mido Bottom Left Chest"))),
    KF_midosBottomRightChest(std::move(NewItemLocation::Chest(0x28, 0x03, "KF Mido Bottom Right Chest"))),

    KF_stormsGrottoChest(std::move(NewItemLocation::Chest(0x3E, 0x0C, "KF Storms Grotto Chest")))
{
}

void NewLocationTable::reset() {
}
