#pragma once

#include <3ds.h>
#include <vector>
#include <string>
#include <array>

#include "cmeta_interpreter.hpp"

static const std::string CustomMusicRootPath = "/OoT3DR/Custom Music/";
static const std::string bcseqExtension      = ".bcseq";
static const std::string cmetaExtension      = ".cmeta";

class SequenceData {
  public:
    SequenceData();
    SequenceData(std::vector<u8>* rawBytesPtr_, std::array<u32, 4> banks_, u16 chFlags_, u8 volume_);
    SequenceData(std::string bcseqPath_, CMetaInterpreter& ci);
    SequenceData(std::string bcseqPath_, std::string cmetaPath_);
    ~SequenceData();

    /// Returns the raw bytes of the sequence.
    /// - RAW Type: Dereferences and returns a copy.
    ///   If this Sequence Data is empty, returns an empty byte vector.
    /// - PATH Type: Returns the raw bytes of the external sequence.
    ///   Reads the file only the first time this is called.
    std::vector<u8>& GetData(FS_Archive archive_);

    /// Returns the bank index.
    std::array<u32, 4> GetBanks();
    /// Returns the bits of the set flags.
    u16 GetChFlags();
    /// Returns the volume.
    u8 GetVolume();

    /// Keeps track of if the meta data has been set
    bool valuesSet = false;

  private:
    enum DataType {
        DataType_Raw,
        DataType_Path,
    };

    DataType dataType;

    /// RAW Type: Pointer to original sequence in the sound archive
    std::vector<u8>* rawBytesPtr;

    /// PATH Type: The full path to the external sequence
    std::string bcseqPath;
    /// PATH Type: The full path to the cmeta file
    std::string cmetaPath;
    /// PATH Type: The raw bytes of the external sequence
    std::vector<u8> rawBytes;

    std::array<u32, 4> banks;
    u16 chFlags;
    u8 volume;
};

// Forward declaration
class MusicCategoryLeaf;

class MusicCategoryNode {
  public:
    MusicCategoryNode(std::string Name_, std::vector<MusicCategoryNode*> children_);
    ~MusicCategoryNode();

    /// Returns the full path of this node.
    std::string GetFullPath();
    /// Returns a vector of this node's and it's children's directories.
    std::vector<std::string> GetDirectories();
    /// Sets this node's parent node.
    void SetParent(MusicCategoryNode* parent_);
    /// Returns true if this node has the given node as an ancestor.
    bool HasAncestor(MusicCategoryNode* ancestor);

    /// Copies the given Sequence Data into it's vector.
    void AddNewSeqData(SequenceData seqData);
    /// Adds all external Sequence Datas in this node's personal folder, and
    /// then recursively calls it's children to do the same
    void AddExternalSeqDatas(FS_Archive sdmcArchive);
    /// Returns a vector of this node's and it's ancestor's Sequence Datas, and which node owns it.
    std::vector<std::pair<MusicCategoryNode*, SequenceData*>> GetSeqDatas();
    /// Returns a random Sequence Data of this node or it's ancestors, and remove it from the owner.
    SequenceData GetAndRemoveRandomSeqData();
    /// Removes the Sequence Data in the vector matching the address, if found.
    void RemoveSeqData(SequenceData* seqDataPtr);
    /// Clears the Sequence Data vector.
    void ClearSeqDatas();

    /// Returns all leaves in this node's children.
    std::vector<MusicCategoryLeaf*> GetAllLeaves();
    /// Returns the first (and hopefully only) node in this family tree with the same name.
    /// If no match was found, returns nullptr.
    MusicCategoryNode* GetNodeByName(const std::string name);

    const std::string Name;

  protected:
    MusicCategoryNode* parent = nullptr;
    std::vector<MusicCategoryNode*> children;
    std::vector<SequenceData> seqDatas;

    std::string fullPath;

    /// Exists only to allow dynamic_cast
    virtual void ForDynamicCast();
};

class MusicCategoryLeaf : public MusicCategoryNode {
  public:
    MusicCategoryLeaf(std::string Name_, u16 fileRep_);
    ~MusicCategoryLeaf();

    /// ID of which file this node represents.
    const u16 FileRep;
};
