#include <filesystem>

#include "sequence_data.hpp"
#include "ctr_binary_data.hpp"
#include "random.hpp"

namespace fs = std::filesystem;

static const std::string bcseqExtension = ".bcseq";
static const std::string cmetaExtension = ".cmeta";

// Sequence Data

SequenceData::SequenceData()
    : dataType(DataType_Raw), rawBytesPtr(nullptr), banks({ 0, 0, 0, 0 }), chFlags(0), volume(0) {
}

SequenceData::SequenceData(std::vector<u8>* rawBytesPtr_, std::array<u32, 4> banks_, u16 chFlags_, u8 volume_)
    : dataType(DataType_Raw), rawBytesPtr(rawBytesPtr_), banks(banks_), chFlags(chFlags_), volume(volume_) {
}

SequenceData::SequenceData(std::string filePath_, std::array<u32, 4> banks_, u16 chFlags_, u8 volume_)
    : dataType(DataType_Path), filePath(filePath_), banks(banks_), chFlags(chFlags_), volume(volume_) {
}

SequenceData::~SequenceData() = default;

std::vector<u8> SequenceData::GetData(FS_Archive archive_) {
    // Pointer to original file
    if (dataType == DataType_Raw && rawBytesPtr != nullptr) {
        return *rawBytesPtr;
    }
    // External sequence, or empty data
    else {
        if (dataType == DataType_Path && rawBytes.empty()) {
            BinaryDataReader br(archive_, filePath);
            rawBytes = br.ReadAll();
            br.Close();
        }
        return rawBytes;
    }
}

std::array<u32, 4> SequenceData::GetBanks() {
    return banks;
}

u16 SequenceData::GetChFlags() {
    return chFlags;
}

u8 SequenceData::GetVolume() {
    return volume;
}

// MusicCategoryNode

MusicCategoryNode::MusicCategoryNode(std::string Name_, std::vector<MusicCategoryNode*> children_)
    : Name(Name_), children(children_) {
    for (auto& child : children) {
        child->SetParent(this);
    }
}

MusicCategoryNode::~MusicCategoryNode() = default;

std::string MusicCategoryNode::GetFullPath() {
    if (fullPath.empty()) {
        std::string finalPath = Name + '/';
        if (parent != nullptr) {
            finalPath.insert(0, parent->GetFullPath());
        } else {
            finalPath.insert(0, CustomMusicRootPath);
        }
        fullPath = finalPath;
    }
    return fullPath;
}

std::vector<std::string> MusicCategoryNode::GetDirectories() {
    std::vector<std::string> dirs;
    dirs.push_back(GetFullPath());
    for (auto child : children) {
        auto childDirs = child->GetDirectories();
        dirs.insert(dirs.end(), childDirs.begin(), childDirs.end());
    }
    return dirs;
}

void MusicCategoryNode::SetParent(MusicCategoryNode* parent_) {
    parent = parent_;
}

bool MusicCategoryNode::HasAncestor(MusicCategoryNode* parent_) {
    MusicCategoryNode* curParent = parent;

    while (curParent != nullptr) {
        if (curParent == parent_) {
            return true;
        } else {
            curParent = curParent->parent;
        }
    }

    return false;
}

void MusicCategoryNode::AddNewSeqData(SequenceData seqData) {
    seqDatas.push_back(seqData);
}

void MusicCategoryNode::AddExternalSeqDatas(FS_Archive sdmcArchive) {
    for (const auto& bcseq : fs::directory_iterator(GetFullPath())) {
        if (bcseq.is_regular_file() && bcseq.path().extension().string() == bcseqExtension) {
            std::array<u32, 4> banks = { 7, 7, 7, 7 }; // Set banks to Orchestra by default
            u16 chFlags              = -1;             // Enable all channel flags by default
            u8 volume                = 127;            // 100% by default

            // Check for cmeta file
            auto fileName = bcseq.path().stem().string();
            for (const auto& cmeta : fs::directory_iterator(GetFullPath())) {
                if (cmeta.is_regular_file() && cmeta.path().stem().string() == fileName &&
                    cmeta.path().extension().string() == cmetaExtension) {

                    BinaryDataReader br(sdmcArchive, cmeta.path().string());
                    // Bank
                    for (size_t bnkIdx = 0; bnkIdx < 4; bnkIdx++) {
                        if (br.GetFileSize() >= bnkIdx + 1) {
                            banks[bnkIdx] = br.ReadByte();
                        } else {
                            break;
                        }
                    }
                    // Channel Flags
                    if (br.GetFileSize() >= 6) {
                        chFlags = br.ReadU16();
                    }
                    // Volume
                    if (br.GetFileSize() >= 7) {
                        volume = br.ReadByte();
                    }
                    br.Close();
                    break;
                }
            }

            seqDatas.push_back(SequenceData(bcseq.path().string(), banks, chFlags, volume));
        }
    }
    for (auto child : children) {
        child->AddExternalSeqDatas(sdmcArchive);
    }
}

std::vector<std::pair<MusicCategoryNode*, SequenceData*>> MusicCategoryNode::GetSeqDatas() {
    std::vector<std::pair<MusicCategoryNode*, SequenceData*>> allSoundFiles;
    for (auto& soundFile : seqDatas) {
        allSoundFiles.push_back(std::make_pair(this, &soundFile));
    }
    if (parent != nullptr) {
        auto seqDatas = parent->GetSeqDatas();
        allSoundFiles.insert(allSoundFiles.end(), seqDatas.begin(), seqDatas.end());
    }
    return allSoundFiles;
}

SequenceData MusicCategoryNode::GetAndRemoveRandomSeqData() {
    auto allSoundFiles = GetSeqDatas();

    // All out, do nothing
    if (allSoundFiles.empty()) {
        return SequenceData();
    }

    auto idx = Random(0, allSoundFiles.size(), true);

    auto owner      = allSoundFiles.at(idx).first;
    auto seqDataPtr = allSoundFiles.at(idx).second;
    auto seqData    = *seqDataPtr;

    owner->RemoveSeqData(seqDataPtr);

    return seqData;
}

void MusicCategoryNode::RemoveSeqData(SequenceData* seqDataPtr) {
    for (size_t i = 0; i < seqDatas.size(); i++) {
        if (&seqDatas.at(i) == seqDataPtr) {
            seqDatas.erase(seqDatas.begin() + i);
            return;
        }
    }
}

void MusicCategoryNode::ClearSeqDatas() {
    seqDatas.clear();
    for (auto child : children) {
        child->ClearSeqDatas();
    }
}

std::vector<MusicCategoryLeaf*> MusicCategoryNode::GetAllLeaves() {
    std::vector<MusicCategoryLeaf*> leaves;
    for (auto child : children) {
        // Assume child is leaf if it has no children
        if (child->children.empty()) {
            leaves.push_back(dynamic_cast<MusicCategoryLeaf*>(child));
        } else {
            auto newLeaves = child->GetAllLeaves();
            leaves.insert(leaves.begin(), newLeaves.begin(), newLeaves.end());
        }
    }
    return leaves;
}

void MusicCategoryNode::ForDynamicCast() {
}

// MusicCategoryLeaf

MusicCategoryLeaf::MusicCategoryLeaf(std::string Name_, u16 fileRep_)
    : MusicCategoryNode(Name_, {}), FileRep(fileRep_) {
}

MusicCategoryLeaf::~MusicCategoryLeaf() = default;
