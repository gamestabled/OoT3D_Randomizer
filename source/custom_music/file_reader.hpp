#pragma once

#include <3ds.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "reference_structures.hpp"

// Code ported from Gota7's Citric Composer

class FileReader {
  public:
    FileReader(BinaryDataReader& br);
    ~FileReader();

    void OpenBlock(BinaryDataReader& br, u32 blockNum);

    void StartStructure(BinaryDataReader& br);
    void EndStructure();

    void OpenReference(BinaryDataReader& br, std::string name);
    void JumpToReference(BinaryDataReader& br, std::string name);
    void CloseReference(std::string name);

    void OpenReferenceTable(BinaryDataReader& br, std::string name);
    u32 ReferenceTableCount(std::string name);
    void ReferenceTableJumpToReference(BinaryDataReader& br, u32 index, std::string name);
    void CloseReferenceTable(std::string name);

  private:
    std::vector<u32> blockOffsets;
    u32 fileStartPos;
    u32 fileSize;
    u32 blockPos;
    u32 blockSize;
    u32 structurePos;
    std::vector<u32> structurePositions;

    std::unordered_map<std::string, ReferenceInfo*> references;
    std::unordered_map<std::string, SizedReferenceInfo*> sizedReferences;
    std::unordered_map<std::string, ReferenceTableInfo*> referenceTables;
    std::unordered_map<std::string, SizedReferenceTableInfo*> sizedReferenceTables;
};
