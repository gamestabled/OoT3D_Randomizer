#pragma once

#include <3ds.h>
#include <string>
#include <vector>

class BinaryDataHandler {
  public:
    void Close();
    bool SuccessfullyInitialized();

    u32 position = 0;

  protected:
    BinaryDataHandler();
    ~BinaryDataHandler();

    bool init = false;

    Handle fsHandle = 0;
};

class BinaryDataReader : public BinaryDataHandler {
  public:
    BinaryDataReader(FS_Archive archive_, std::string filePath_);
    ~BinaryDataReader();

    u64 GetFileSize();

    u8 ReadByte();
    std::vector<char> ReadChars(u32 count);
    std::vector<u8> ReadBytes(u32 count);
    s16 ReadS16();
    u16 ReadU16();
    s32 ReadS32();
    u32 ReadU32();

    std::vector<u8> ReadAll();

  private:
    u64 fileSize;
};

class BinaryDataWriter : public BinaryDataHandler {
  public:
    BinaryDataWriter(FS_Archive archive_, std::string filePath_);
    ~BinaryDataWriter();

    void Write(char buf);
    void Write(u8 buf);
    void Write(std::vector<char> buf);
    void Write(std::vector<u8> buf);
    void Write(s16 buf);
    void Write(u16 buf);
    void Write(s32 buf);
    void Write(u32 buf);

  private:
};
