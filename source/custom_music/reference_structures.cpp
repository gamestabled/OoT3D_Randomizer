#include "reference_structures.hpp"

// Code ported from Gota7's Citric Composer

ReferenceInfo::ReferenceInfo(BinaryDataReader& br) {
    referenceType = br.ReadU16();
    br.position += 2; // Padding
    offset = br.ReadS32();
}

ReferenceInfo::~ReferenceInfo() = default;

SizedReferenceInfo::SizedReferenceInfo(BinaryDataReader& br) {
    referenceType = br.ReadU16();
    br.position += 2; // Padding
    offset = br.ReadS32();
    size   = br.ReadU32();
}

SizedReferenceInfo::~SizedReferenceInfo() = default;

ReferenceTableInfo::ReferenceTableInfo(BinaryDataReader& br) {
    tablePos = br.position;
    count    = br.ReadU32();
    for (size_t i = 0; i < count; i++) {
        referenceTypes.push_back(br.ReadU16());
        br.position += 2; // Padding
        offsets.push_back(br.ReadS32());
    }
}

ReferenceTableInfo::~ReferenceTableInfo() = default;

SizedReferenceTableInfo::SizedReferenceTableInfo(BinaryDataReader& br) {
    tablePos = br.position;
    count    = br.ReadU32();
    for (size_t i = 0; i < count; i++) {
        referenceTypes.push_back(br.ReadU16());
        br.position += 2; // Padding
        offsets.push_back(br.ReadS32());
        sizes.push_back(br.ReadU32());
    }
}

SizedReferenceTableInfo::~SizedReferenceTableInfo() = default;
