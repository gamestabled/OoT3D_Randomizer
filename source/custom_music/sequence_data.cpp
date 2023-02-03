#include <filesystem>

#include "sequence_data.hpp"
#include "ctr_binary_data.hpp"
#include "random.hpp"

namespace fs = std::filesystem;

static const std::string bcseqExtension = ".bcseq";
static const std::string cmetaExtension = ".cmeta";

// Sequence Data

SequenceData::SequenceData() : dataType(DataType_Raw), rawBytesPtr(nullptr), bankNum(0), chFlags(0) {
}

SequenceData::SequenceData(std::vector<u8>* rawBytesPtr_, u32 bankNum_, u16 chFlags_)
    : dataType(DataType_Raw), rawBytesPtr(rawBytesPtr_), bankNum(bankNum_), chFlags(chFlags_) {
}

SequenceData::SequenceData(std::string filePath_, u32 bankNum_, u16 chFlags_)
    : dataType(DataType_Path), filePath(filePath_), bankNum(bankNum_), chFlags(chFlags_) {
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

u16 SequenceData::GetChFlags() {
    return chFlags;
}

u32 SequenceData::GetBank() {
    return bankNum;
}

// MusicCategoryNode

MusicCategoryNode::MusicCategoryNode(std::string Name_, std::vector<MusicCategoryNode*> children_)
    : Name(Name_), children(children_) {
    for (auto& child : children) {
        child->SetParent(this);
    }
}

MusicCategoryNode::~MusicCategoryNode() = default;

void MusicCategoryNode::CreateDirectories(FS_Archive sdmcArchive) {
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, GetFullPath().c_str()), FS_ATTRIBUTE_DIRECTORY);
    for (auto& child : children) {
        child->CreateDirectories(sdmcArchive);
    }
}

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
            u8 bank     = 7;  // Set bank to Orchestra by default
            u16 chFlags = -1; // Enable all channel flags by default

            // Check for cmeta file
            auto fileName = bcseq.path().stem().string();
            for (const auto& cmeta : fs::directory_iterator(GetFullPath())) {
                if (cmeta.is_regular_file() && cmeta.path().stem().string() == fileName &&
                    cmeta.path().extension().string() == cmetaExtension) {

                    BinaryDataReader br(sdmcArchive, cmeta.path().string());
                    // Bank
                    if (br.GetFileSize() >= 1) {
                        bank = br.ReadByte();
                        br.position += 3; // Only one bank can be set for now, jump over the extra bytes

                        // Channel Flags
                        if (br.GetFileSize() >= 6) {
                            chFlags = br.ReadU16();
                        }
                    }
                    br.Close();
                    break;
                }
            }

            seqDatas.push_back(SequenceData(bcseq.path().string(), bank, chFlags));
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
