#pragma once

#include <3ds.h>
#include <vector>

#include "ctr_binary_data.hpp"

// Code ported from Gota7's Citric Composer

class ReferenceInfo {
  public:
    ReferenceInfo(BinaryDataReader& br);
    ~ReferenceInfo();

    u16 referenceType;
    s32 offset;
};

class SizedReferenceInfo {
  public:
    SizedReferenceInfo(BinaryDataReader& br);
    ~SizedReferenceInfo();

    u16 referenceType;
    s32 offset;
    u32 size;
};

class ReferenceTableInfo {
  public:
    ReferenceTableInfo(BinaryDataReader& br);
    ~ReferenceTableInfo();

    std::vector<u16> referenceTypes;
    std::vector<s32> offsets;
    u32 count;
    u32 tablePos;
};

class SizedReferenceTableInfo {
  public:
    SizedReferenceTableInfo(BinaryDataReader& br);
    ~SizedReferenceTableInfo();

    std::vector<u16> referenceTypes;
    std::vector<s32> offsets;
    std::vector<u32> sizes;
    u32 count;
    u32 tablePos;
};
