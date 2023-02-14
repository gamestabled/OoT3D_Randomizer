#include "ctr_binary_data.hpp"

// Handler

BinaryDataHandler::BinaryDataHandler() {
}

BinaryDataHandler::~BinaryDataHandler() = default;

void BinaryDataHandler::Close() {
    FSFILE_Close(fsHandle);
}

bool BinaryDataHandler::SuccessfullyInitialized() {
    return init;
}

// Reader

BinaryDataReader::BinaryDataReader(FS_Archive archive_, std::string filePath_) {
    if (!R_SUCCEEDED(FSUSER_OpenFile(&fsHandle, archive_, fsMakePath(PATH_ASCII, filePath_.c_str()), FS_OPEN_READ,
                                     FS_ATTRIBUTE_ARCHIVE))) {
        return;
    }
    FSFILE_GetSize(fsHandle, &fileSize);
    init = true;
}

BinaryDataReader::~BinaryDataReader() = default;

u64 BinaryDataReader::GetFileSize() {
    return fileSize;
}

u8 BinaryDataReader::ReadByte() {
    u32 bytesRead = 0;
    u8 value      = 0;

    FSFILE_Read(fsHandle, &bytesRead, position, &value, sizeof(u8));
    BinaryDataReader::position += sizeof(u8);

    return value;
}

std::vector<char> BinaryDataReader::ReadChars(u32 count) {
    u32 bytesRead = 0;
    std::vector<char> chars(count, 0);

    FSFILE_Read(fsHandle, &bytesRead, position, &chars[0], count);
    position += bytesRead;

    return chars;
}

std::vector<u8> BinaryDataReader::ReadBytes(u32 count) {
    u32 bytesRead = 0;
    std::vector<u8> bytes(count, 0);

    FSFILE_Read(fsHandle, &bytesRead, position, &bytes[0], count);
    position += bytesRead;

    return bytes;
}

s16 BinaryDataReader::ReadS16() {
    u32 bytesRead = 0;
    s16 value     = 0;

    FSFILE_Read(fsHandle, &bytesRead, position, &value, sizeof(s16));
    BinaryDataReader::position += sizeof(s16);

    return value;
}

u16 BinaryDataReader::ReadU16() {
    return (u16)ReadS16();
}

s32 BinaryDataReader::ReadS32() {
    u32 bytesRead = 0;
    u32 value     = 0;

    FSFILE_Read(fsHandle, &bytesRead, position, &value, sizeof(s32));
    BinaryDataReader::position += sizeof(s32);

    return value;
}

u32 BinaryDataReader::ReadU32() {
    return (u32)ReadS32();
}

std::vector<u8> BinaryDataReader::ReadAll() {
    position = 0;
    FSFILE_GetSize(fsHandle, &fileSize);
    return ReadBytes(fileSize);
}

// Writer

BinaryDataWriter::BinaryDataWriter(FS_Archive archive_, std::string filePath_) {
    if (!R_SUCCEEDED(FSUSER_OpenFile(&fsHandle, archive_, fsMakePath(PATH_ASCII, filePath_.c_str()),
                                     FS_OPEN_WRITE | FS_OPEN_CREATE, FS_ATTRIBUTE_ARCHIVE))) {
        return;
    }
    init = true;
}

BinaryDataWriter::~BinaryDataWriter() = default;

void BinaryDataWriter::Write(char buf) {
    Write((u8)buf);
}

void BinaryDataWriter::Write(u8 buf) {
    u32 bytesWritten = 0;
    FSFILE_Write(fsHandle, &bytesWritten, position, &buf, sizeof(buf), FS_WRITE_UPDATE_TIME);
    position += bytesWritten;
}

void BinaryDataWriter::Write(std::vector<char> buf) {
    u32 bytesWritten = 0;
    FSFILE_Write(fsHandle, &bytesWritten, position, &buf[0], buf.size(), FS_WRITE_UPDATE_TIME);
    position += bytesWritten;
}

void BinaryDataWriter::Write(std::vector<u8> buf) {
    u32 bytesWritten = 0;
    FSFILE_Write(fsHandle, &bytesWritten, position, &buf[0], buf.size(), FS_WRITE_UPDATE_TIME);
    position += bytesWritten;
}

void BinaryDataWriter::Write(s16 buf) {
    u32 bytesWritten = 0;
    FSFILE_Write(fsHandle, &bytesWritten, position, &buf, sizeof(buf), FS_WRITE_UPDATE_TIME);
    position += bytesWritten;
}

void BinaryDataWriter::Write(u16 buf) {
    Write((s16)buf);
}

void BinaryDataWriter::Write(s32 buf) {
    u32 bytesWritten = 0;
    FSFILE_Write(fsHandle, &bytesWritten, position, &buf, sizeof(buf), FS_WRITE_UPDATE_TIME);
    position += bytesWritten;
}

void BinaryDataWriter::Write(u32 buf) {
    Write((s32)buf);
}
