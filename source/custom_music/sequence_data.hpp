#pragma once

#include <3ds.h>
#include <vector>
#include <string>

static const std::string CustomMusicRootPath = "/OoT3DR/Custom Music/";

class SequenceData {
  public:
    SequenceData();
    SequenceData(std::vector<u8>* rawBytesPtr_, u32 bankNum_, u16 chFlags_);
    SequenceData(std::string filePath_, u32 bankNum_, u16 chFlags_);
    ~SequenceData();

    /// Returns the raw bytes of the sequence.
    /// - RAW Type: Dereferences and returns a copy.
    ///   If this Sequence Data is empty, returns an empty byte vector.
    /// - PATH Type: Returns the raw bytes of the external sequence.
    ///   Reads the file only the first time this is called.
    std::vector<u8> GetData(FS_Archive archive_);
    /// Returns the bits of the set flags.
    u16 GetChFlags();
    /// Returns the bank index.
    u32 GetBank();

  private:
    enum DataType {
        DataType_Raw,
        DataType_Path,
    };

    DataType dataType;

    /// RAW Type: Pointer to original sequence in the sound archive
    std::vector<u8>* rawBytesPtr;

    /// PATH Type: The full path to the external sequence
    std::string filePath;
    /// PATH Type: The raw bytes of the external sequence
    std::vector<u8> rawBytes;

    u32 bankNum;
    u16 chFlags;
};

// Forward declaration
class AudioCategoryLeaf;

class AudioCategory {
  public:
    AudioCategory(std::string Name_, std::vector<AudioCategory*> children_);
    ~AudioCategory();

    /// Creates it's folder in it's parent's, and then calls each child to do the same.
    void CreateDirectories(FS_Archive sdmcArchive);
    /// Returns the full path of this node.
    std::string GetFullPath();
    /// Sets this node's parent node.
    void SetParent(AudioCategory* parent_);
    /// Returns true if this node has the given node as an ancestor.
    bool HasAncestor(AudioCategory* ancestor);

    /// Copies the given Sequence Data into it's vector.
    void AddNewSeqData(SequenceData seqData);
    /// Adds all external Sequence Datas in this node's personal folder.
    void AddExternalSeqDatas(FS_Archive sdmcArchive);
    /// Returns a vector of this node's and it's ancestor's Sequence Datas, and which node owns it.
    std::vector<std::pair<AudioCategory*, SequenceData*>> GetSeqDatas();
    /// Returns a random Sequence Data of this node or it's ancestors, and remove it from the owner.
    SequenceData GetAndRemoveRandomSeqData();
    /// Removes the Sequence Data in the vector matching the address, if found.
    void RemoveSeqData(SequenceData* seqDataPtr);
    /// Clears the Sequence Data vector.
    void ClearSeqDatas();

    /// Returns all leaves in this node.
    std::vector<AudioCategoryLeaf*> GetAllLeaves();

    const std::string Name;

  protected:
    AudioCategory* parent = nullptr;
    std::vector<AudioCategory*> children;
    std::vector<SequenceData> seqDatas;

    std::string fullPath;

    /// Exists only to allow dynamic_cast
    virtual void ForDynamicCast();
};

class AudioCategoryLeaf : public AudioCategory {
  public:
    AudioCategoryLeaf(std::string Name_, u16 fileRep_);
    ~AudioCategoryLeaf();

    /// ID of which file this node represents.
    const u16 FileRep;
};
