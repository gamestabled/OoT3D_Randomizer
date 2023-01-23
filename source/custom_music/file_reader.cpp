#include "file_reader.hpp"
#include "ctr_binary_data.hpp"

// Code ported from Gota7's Citric Composer

FileReader::FileReader(BinaryDataReader& br) {
    fileStartPos = br.position;

    br.position += 4; // Magic
    br.position += 2; // Byte Order
    u16 headerSize = br.ReadU16();
    br.position += 4; // Version
    br.position += 4; // File Size
    u16 numBlocks = br.ReadU16();
    br.position += 2; // Padding

    for (size_t i = 0; i < numBlocks; i++) {
        br.position += 4;
        blockOffsets.push_back(br.ReadU32());
        br.position += 4;
    }

    br.position = fileStartPos + headerSize;
}

FileReader::~FileReader() = default;

void FileReader::OpenBlock(BinaryDataReader& br, u32 blockNum) {
    br.position = fileStartPos + blockOffsets[blockNum];
    blockPos    = br.position;
    br.ReadU32(); // Magic
    blockSize    = br.ReadU32();
    structurePos = br.position;
}

void FileReader::StartStructure(BinaryDataReader& br) {
    structurePositions.push_back(structurePos);
    structurePos = br.position;
}

void FileReader::EndStructure() {
    structurePos = structurePositions.back();
    structurePositions.pop_back();
}

void FileReader::OpenReference(BinaryDataReader& br, std::string name) {
    references[name] = new ReferenceInfo(br);
}

void FileReader::JumpToReference(BinaryDataReader& br, std::string name) {
    br.position = structurePos + references[name]->offset;
}

void FileReader::CloseReference(std::string name) {
    references.erase(name);
}

void FileReader::OpenReferenceTable(BinaryDataReader& br, std::string name) {
    referenceTables[name] = new ReferenceTableInfo(br);
}

u32 FileReader::ReferenceTableCount(std::string name) {
    return referenceTables[name]->count;
}

void FileReader::ReferenceTableJumpToReference(BinaryDataReader& br, u32 index, std::string name) {
    br.position = structurePos + referenceTables[name]->offsets[index];
}

void FileReader::CloseReferenceTable(std::string name) {
    referenceTables.erase(name);
}
