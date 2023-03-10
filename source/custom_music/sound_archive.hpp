#pragma once

#include <3ds.h>
#include <string>
#include <vector>
#include <array>

#include "reference_structures.hpp"
#include "sequence_data.hpp"

#define STRING_BLOCK 0
#define INFO_BLOCK 1
#define FILE_BLOCK 2

class SoundArchive {
  public:
    SoundArchive(FS_Archive archive_, const std::string& filePath_);
    ~SoundArchive();

    /// Returns true if the original archive was properly open and read.
    bool SuccessfullyInitialized();

    /// Returns a pointer to the original file.
    std::vector<u8>* GetRawFilePtr(u16 index);
    /// Returns the volume of the original sequence at the given file index.
    u16 GetOriginalVolume(u16 index);
    /// Returns the channel flags of the original sequence at the given file index.
    u16 GetOriginalChFlags(u16 index);
    /// Returns the bank index of the original sequence at the given file index.
    u32 GetOriginalBank(u16 index);
    /// Replaces a sequence in the files-to-write vector.
    void ReplaceSeq(FS_Archive archive_, u16 fileIndex, SequenceData& seqData);

    /// Writes the new archive to the given directory.
    void Write(FS_Archive archive_, const std::string& filePath_);

  private:
    bool init = false;

    struct SarHeader {
        std::vector<char> magic;
        u16 byteOrder;
        u16 headerSize;
        u32 version;
        u32 fileSize;
        u16 numBlocks;
        std::vector<SizedReferenceInfo> blockOffsets;
    } sarHeader;

    std::vector<u8> mainHeader;
    std::vector<u8> stringBlock;
    std::vector<u8> infoBlock;
    // std::vector<u8> fileBlock;

    std::vector<SizedReferenceInfo> fileRefs;
    std::vector<u8> originalVolumes;
    std::vector<u16> originalChFlags;
    std::vector<u32> originalBanks;
    std::vector<std::vector<u8>> rawFiles;

    std::vector<u32> fileRefGlobalOffsets;
    std::vector<u32> volumeGlobalOffsets;
    std::vector<u32> chFlagsGlobalOffsets;
    std::vector<u32> seqBnkGlobalOffsets;

    std::vector<u8> newVolumes;
    std::vector<u16> newChFlags;
    std::vector<std::array<u32, 4>> newBanks;
    std::vector<std::vector<u8>> newFiles;
};
