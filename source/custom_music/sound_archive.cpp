#include "sound_archive.hpp"
#include "ctr_binary_data.hpp"
#include "reference_structures.hpp"
#include "file_reader.hpp"
#include "common_structures.hpp"
#include <cstring>

SoundArchive::SoundArchive(FS_Archive archive_, const std::string& filePath_) {
    BinaryDataReader br(archive_, filePath_);

    if (!br.SuccessfullyInitialized()) {
        return;
    }

    // HEADER
    sarHeader.magic      = br.ReadChars(4);
    sarHeader.byteOrder  = br.ReadU16();
    sarHeader.headerSize = br.ReadU16();
    sarHeader.version    = br.ReadU32();
    sarHeader.fileSize   = br.ReadU32();

    sarHeader.numBlocks = br.ReadU16();
    br.position += 2; // Padding
    for (size_t i = 0; i < sarHeader.numBlocks; i++) {
        sarHeader.blockOffsets.push_back(SizedReferenceInfo(br));
    }

    // HEADER + BLOCKS
    br.position = 0;
    mainHeader  = br.ReadBytes(64);

    br.position = sarHeader.blockOffsets[STRING_BLOCK].offset;
    stringBlock = br.ReadBytes(sarHeader.blockOffsets[STRING_BLOCK].size);

    br.position = sarHeader.blockOffsets[INFO_BLOCK].offset;
    infoBlock   = br.ReadBytes(sarHeader.blockOffsets[INFO_BLOCK].size);

    br.position = sarHeader.blockOffsets[FILE_BLOCK].offset;
    // The file block will be created from a vector of raw bytes.

    // Stuff for multiple banks per sequence
    u32 extraBankBytes = 0;
    std::vector<u32> mainInfoReferenceOffsets;
    u32 soundRefTableOffset = 0;

    static const auto SEQ_FIRST_SONG = 1413;
    static const auto SEQ_LAST_SONG  = 1497;

    static const auto DUMMY_SEQ_SARIA = 1483;

    // Get file reference offsets and sequence info offsets
    {
        br.position = 0;
        FileReader fileReader(br);
        fileReader.OpenBlock(br, 1);

        const auto addMainRefOffset = [&] {
            mainInfoReferenceOffsets.push_back(br.position + 4 - sarHeader.blockOffsets[INFO_BLOCK].offset);
        };

        fileReader.OpenReference(br, "SoundRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "SoundGroupRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "BankRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "WaveArchiveRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "GroupRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "PlayerRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "FileRefTableRef");
        addMainRefOffset();
        fileReader.OpenReference(br, "ProjectInfo");

        // File Reference Offsets
        fileReader.JumpToReference(br, "FileRefTableRef");
        fileReader.StartStructure(br);
        fileReader.OpenReferenceTable(br, "SoundGroupRefTable");
        for (size_t i = 0; i < fileReader.ReferenceTableCount("SoundGroupRefTable"); i++) {
            fileReader.ReferenceTableJumpToReference(br, i, "SoundGroupRefTable");
            fileReader.StartStructure(br);
            fileReader.OpenReference(br, "FileRef");
            fileReader.JumpToReference(br, "FileRef");
            fileReader.StartStructure(br);

            fileRefGlobalOffsets.push_back(br.position);
            fileRefs.push_back(SizedReferenceInfo(br));

            fileReader.EndStructure();
            fileReader.CloseReference("FileRef");
            fileReader.EndStructure();
        }
        fileReader.CloseReferenceTable("SoundGroupRefTable");
        fileReader.EndStructure();

        // Sequence Info Offsets
        fileReader.JumpToReference(br, "SoundRefTableRef");
        fileReader.StartStructure(br);
        soundRefTableOffset = br.position - sarHeader.blockOffsets[INFO_BLOCK].offset;
        fileReader.OpenReferenceTable(br, "SoundRefTable");

        // Read the info of the music sequences
        for (size_t seqIdx = SEQ_FIRST_SONG; seqIdx <= SEQ_LAST_SONG; seqIdx++) {
            fileReader.ReferenceTableJumpToReference(br, seqIdx, "SoundRefTable");
            fileReader.StartStructure(br);

            br.position += 4; // File ID
            br.position += 4; // ID
            // Skip the dummy sequence
            if (seqIdx != DUMMY_SEQ_SARIA) {
                volumeGlobalOffsets.push_back(br.position);
                originalVolumes.push_back(br.ReadByte());
            } else {
                br.position += 1; // Volume
            }
            br.position += 1; // Remote Filter
            br.position += 2; // Padding

            fileReader.OpenReference(br, "DetSoundRef");
            {
                fileReader.JumpToReference(br, "DetSoundRef");
                fileReader.StartStructure(br);
                fileReader.OpenReference(br, "BnkTableRef");

                // Skip the dummy sequence
                if (seqIdx != DUMMY_SEQ_SARIA) {
                    chFlagsGlobalOffsets.push_back(br.position);
                    originalChFlags.push_back(br.ReadU16());
                }

                fileReader.JumpToReference(br, "BnkTableRef");

                // Skip the dummy sequence
                if (seqIdx != DUMMY_SEQ_SARIA) {
                    seqBnkGlobalOffsets.push_back(br.position);
                    br.position += 4;
                    originalBanks.push_back(br.ReadU32() & 0xFF'FF'FF);

                    extraBankBytes += 12;
                }

                fileReader.EndStructure();
            }

            fileReader.EndStructure();
        }

        fileReader.CloseReferenceTable("SoundRefTable");
        fileReader.EndStructure();
    }

    // Store the files themselves
    for (size_t i = 0; i < fileRefs.size(); i++) {
        br.position = sarHeader.blockOffsets[FILE_BLOCK].offset + fileRefs[i].offset + 8;
        rawFiles.push_back(br.ReadBytes(fileRefs[i].size));
    }

    br.Close();
    init = true;

    newFiles = rawFiles;

    originalVolumes.insert(originalVolumes.begin(), 9, -1);
    originalChFlags.insert(originalChFlags.begin(), 9, -1);
    originalBanks.insert(originalBanks.begin(), 9, -1);

    newVolumes = originalVolumes;
    newChFlags = originalChFlags;

    newBanks.clear();
    for (size_t i = 0; i < originalBanks.size(); i++) {
        u32 origBnk = originalBanks.at(i);
        newBanks.push_back({ origBnk, origBnk, origBnk, origBnk });
    }

    // Below is a hacky solution to allow sequences to use multiple banks

    const auto increaseOffset = [&](u32 offsetPos, u32 addedOffset) {
        u32 origOffset = 0;
        memcpy(&origOffset, &infoBlock.at(offsetPos), 4);

        u32 newOffset = origOffset + addedOffset;
        memcpy(&infoBlock.at(offsetPos), &newOffset, 4);
    };

    for (size_t i = 0; i < mainInfoReferenceOffsets.size(); i++) {
        increaseOffset(mainInfoReferenceOffsets.at(i), extraBankBytes);
    }

    // Update SoundRefTable
    {
        u32 offsetToAdd = 0;
        for (size_t i = SEQ_FIRST_SONG; i <= 1523; i++) {
            u32 srftOffs = soundRefTableOffset;
            srftOffs += 4;     // Count
            srftOffs += i * 8; // Previous references
            srftOffs += 4;     // Current reference type + padding

            increaseOffset(srftOffs, offsetToAdd);

            if (i != DUMMY_SEQ_SARIA && i <= SEQ_LAST_SONG) {
                offsetToAdd += 12;
            }
        }
    }

    sarHeader.blockOffsets[INFO_BLOCK].size += extraBankBytes;
    sarHeader.blockOffsets[FILE_BLOCK].offset += extraBankBytes;

    for (s32 i = seqBnkGlobalOffsets.size() - 1; i >= 0; i--) {
        u32 seqBnkLocalOffset = seqBnkGlobalOffsets[i] - sarHeader.blockOffsets[INFO_BLOCK].offset;
        infoBlock.insert(infoBlock.begin() + (seqBnkLocalOffset + 8), 12, 0);
    }

    const auto addIncrementalOffset = [](std::vector<u32>& globalOffsets) {
        u32 offsetToAdd = 0;
        for (auto& offset : globalOffsets) {
            offset += offsetToAdd;
            offsetToAdd += 12;
        }
    };

    addIncrementalOffset(volumeGlobalOffsets);
    addIncrementalOffset(chFlagsGlobalOffsets);
    addIncrementalOffset(seqBnkGlobalOffsets);

    for (auto& abc : fileRefGlobalOffsets) {
        abc += extraBankBytes;
    }
}

SoundArchive::~SoundArchive() = default;

bool SoundArchive::SuccessfullyInitialized() {
    return init;
}

std::vector<u8>* SoundArchive::GetRawFilePtr(u16 index) {
    return &rawFiles.at(index);
}

u16 SoundArchive::GetOriginalVolume(u16 index) {
    return originalVolumes.at(index);
}

u16 SoundArchive::GetOriginalChFlags(u16 index) {
    return originalChFlags.at(index);
}

u32 SoundArchive::GetOriginalBank(u16 index) {
    return originalBanks.at(index);
}

void SoundArchive::ReplaceSeq(FS_Archive archive_, u16 fileIndex, SequenceData& seqData) {
    if (seqData.GetData(archive_).empty()) {
        // Empty received, no change
        return;
    }
    newFiles.at(fileIndex) = seqData.GetData(archive_);
    for (size_t bnkIdx = 0; bnkIdx < 4; bnkIdx++) {
        newBanks.at(fileIndex) = seqData.GetBanks();
    }
    newChFlags.at(fileIndex) = seqData.GetChFlags();
    newVolumes.at(fileIndex) = seqData.GetVolume();
}

void SoundArchive::Write(FS_Archive archive_, const std::string& filePath_) {
    BinaryDataWriter bw(archive_, filePath_);

    if (!bw.SuccessfullyInitialized()) {
        return;
    }

    const auto bwAlign = [&](u32 alignment) {
        while (bw.position % alignment != 0) {
            bw.Write((u8)0);
        }
    };

    bw.position = 0;
    bw.Write(mainHeader);

    bw.position = sarHeader.blockOffsets[STRING_BLOCK].offset;
    bw.Write(stringBlock);

    bw.position = sarHeader.blockOffsets[INFO_BLOCK].offset;
    bw.Write(infoBlock);

    // File Block
    bw.position = sarHeader.blockOffsets[FILE_BLOCK].offset;
    bw.Write(std::vector<char>{ 'F', 'I', 'L', 'E' });
    bw.position += 4;
    u32 offsetStartPos = bw.position;
    bw.position += 24;

    u32 fileBlockSize = 24; // Alignment + Files...
    u32 lastPos       = bw.position;
    for (size_t i = 0; i < rawFiles.size(); i++) {
        // Write new ref
        u32 tmpPos  = bw.position;
        bw.position = fileRefGlobalOffsets.at(i) + 4;
        bw.Write((s32)(tmpPos - offsetStartPos)); // Offset
        bw.Write((u32)newFiles.at(i).size());     // Size
        bw.position = tmpPos;

        // Write file
        bw.Write(newFiles.at(i));
        bwAlign(0x20);

        // Calculate new size
        fileBlockSize += bw.position - lastPos;
        lastPos = bw.position;

        // Set new info for sequences
        if (i >= 9 && i <= 92) {
            tmpPos = bw.position;
            // Volume
            bw.position = volumeGlobalOffsets.at(i - 9);
            bw.Write((u8)newVolumes.at(i));
            // Channel Flags
            bw.position = chFlagsGlobalOffsets.at(i - 9);
            bw.Write((u16)newChFlags.at(i));
            // Bank
            bw.position = seqBnkGlobalOffsets.at(i - 9);
            bw.Write((u32)4);
            for (size_t bnkIdx = 0; bnkIdx < 4; bnkIdx++) {
                bw.Write((u32)((3 << 24) | (newBanks.at(i)[bnkIdx] & 0xFF'FF'FF)));
            }
            bw.position = tmpPos;
        }
    }
    // Write size of file block
    bw.position = sarHeader.blockOffsets[FILE_BLOCK].offset + 4;
    bw.Write(fileBlockSize);

    // Write new header values
    bw.position = 0x28;
    bw.Write(sarHeader.blockOffsets[INFO_BLOCK].size);
    bw.position = 0x30;
    bw.Write(sarHeader.blockOffsets[FILE_BLOCK].offset);
    bw.position = 0x34;
    bw.Write(fileBlockSize);
    bw.position = 0xC;
    bw.Write(sarHeader.blockOffsets[FILE_BLOCK].offset + fileBlockSize);

    bw.Close();
}
