/**
 * @file fs.h
 * @brief Filesystem Services
 * Edited from
 * https://github.com/devkitPro/libctru/blob/6360f4bdb1ca5f8131ffc92640c1dd16afb63083/libctru/include/3ds/services/fs.h
 */
#pragma once

#include "../types.h"

/// Open flags.
enum {
    FS_OPEN_READ   = BIT(0), ///< Open for reading.
    FS_OPEN_WRITE  = BIT(1), ///< Open for writing.
    FS_OPEN_CREATE = BIT(2), ///< Create file.
};

/// Write flags.
enum {
    FS_WRITE_FLUSH       = BIT(0), ///< Flush.
    FS_WRITE_UPDATE_TIME = BIT(8), ///< Update file timestamp.
};

/// Attribute flags.
enum {
    FS_ATTRIBUTE_DIRECTORY = BIT(0),  ///< Directory.
    FS_ATTRIBUTE_HIDDEN    = BIT(8),  ///< Hidden.
    FS_ATTRIBUTE_ARCHIVE   = BIT(16), ///< Archive.
    FS_ATTRIBUTE_READ_ONLY = BIT(24), ///< Read-only.
};

/// Media types.
typedef enum {
    MEDIATYPE_NAND      = 0, ///< NAND.
    MEDIATYPE_SD        = 1, ///< SD card.
    MEDIATYPE_GAME_CARD = 2, ///< Game card.
} FS_MediaType;

/// System media types.
typedef enum {
    SYSTEM_MEDIATYPE_CTR_NAND  = 0, ///< CTR NAND.
    SYSTEM_MEDIATYPE_TWL_NAND  = 1, ///< TWL NAND.
    SYSTEM_MEDIATYPE_SD        = 2, ///< SD card.
    SYSTEM_MEDIATYPE_TWL_PHOTO = 3, ///< TWL Photo.
} FS_SystemMediaType;

/// Archive IDs.
typedef enum {
    ARCHIVE_ROMFS                    = 0x00000003, ///< RomFS archive.
    ARCHIVE_SAVEDATA                 = 0x00000004, ///< Save data archive.
    ARCHIVE_EXTDATA                  = 0x00000006, ///< Ext data archive.
    ARCHIVE_SHARED_EXTDATA           = 0x00000007, ///< Shared ext data archive.
    ARCHIVE_SYSTEM_SAVEDATA          = 0x00000008, ///< System save data archive.
    ARCHIVE_SDMC                     = 0x00000009, ///< SDMC archive.
    ARCHIVE_SDMC_WRITE_ONLY          = 0x0000000A, ///< Write-only SDMC archive.
    ARCHIVE_BOSS_EXTDATA             = 0x12345678, ///< BOSS ext data archive.
    ARCHIVE_CARD_SPIFS               = 0x12345679, ///< Card SPI FS archive.
    ARCHIVE_EXTDATA_AND_BOSS_EXTDATA = 0x1234567B, ///< Ext data and BOSS ext data archive.
    ARCHIVE_SYSTEM_SAVEDATA2         = 0x1234567C, ///< System save data archive.
    ARCHIVE_NAND_RW                  = 0x1234567D, ///< Read-write NAND archive.
    ARCHIVE_NAND_RO                  = 0x1234567E, ///< Read-only NAND archive.
    ARCHIVE_NAND_RO_WRITE_ACCESS     = 0x1234567F, ///< Read-only write access NAND archive.
    ARCHIVE_SAVEDATA_AND_CONTENT     = 0x2345678A, ///< User save data and ExeFS/RomFS archive.
    ARCHIVE_SAVEDATA_AND_CONTENT2    = 0x2345678E, ///< User save data and ExeFS/RomFS archive (only ExeFS for fs:LDR).
    ARCHIVE_NAND_CTR_FS              = 0x567890AB, ///< NAND CTR FS archive.
    ARCHIVE_TWL_PHOTO                = 0x567890AC, ///< TWL PHOTO archive.
    ARCHIVE_TWL_SOUND                = 0x567890AD, ///< TWL SOUND archive.
    ARCHIVE_NAND_TWL_FS              = 0x567890AE, ///< NAND TWL FS archive.
    ARCHIVE_NAND_W_FS                = 0x567890AF, ///< NAND W FS archive.
    ARCHIVE_GAMECARD_SAVEDATA        = 0x567890B1, ///< Game card save data archive.
    ARCHIVE_USER_SAVEDATA            = 0x567890B2, ///< User save data archive.
    ARCHIVE_DEMO_SAVEDATA            = 0x567890B4, ///< Demo save data archive.
} FS_ArchiveID;

/// Path types.
typedef enum {
    PATH_INVALID = 0, ///< Invalid path.
    PATH_EMPTY   = 1, ///< Empty path.
    PATH_BINARY  = 2, ///< Binary path. Meaning is per-archive.
    PATH_ASCII   = 3, ///< ASCII text path.
    PATH_UTF16   = 4, ///< UTF-16 text path.
} FS_PathType;

/// Secure value slot.
typedef enum {
    SECUREVALUE_SLOT_SD = 0x1000, ///< SD application.
} FS_SecureValueSlot;

/// Card SPI baud rate.
typedef enum {
    BAUDRATE_512KHZ = 0, ///< 512KHz.
    BAUDRATE_1MHZ   = 1, ///< 1MHz.
    BAUDRATE_2MHZ   = 2, ///< 2MHz.
    BAUDRATE_4MHZ   = 3, ///< 4MHz.
    BAUDRATE_8MHZ   = 4, ///< 8MHz.
    BAUDRATE_16MHZ  = 5, ///< 16MHz.
} FS_CardSpiBaudRate;

/// Card SPI bus mode.
typedef enum {
    BUSMODE_1BIT = 0, ///< 1-bit.
    BUSMODE_4BIT = 1, ///< 4-bit.
} FS_CardSpiBusMode;

/// Card SPI bus mode.
typedef enum {
    SPECIALCONTENT_UPDATE    = 1, ///< Update.
    SPECIALCONTENT_MANUAL    = 2, ///< Manual.
    SPECIALCONTENT_DLP_CHILD = 3, ///< DLP child.
} FS_SpecialContentType;

typedef enum {
    CARD_CTR = 0, ///< CTR card.
    CARD_TWL = 1, ///< TWL card.
} FS_CardType;

/// FS control actions.
typedef enum {
    FS_ACTION_UNKNOWN = 0,
} FS_Action;

/// Archive control actions.
typedef enum {
    ARCHIVE_ACTION_COMMIT_SAVE_DATA = 0, ///< Commits save data changes. No inputs/outputs.
    ARCHIVE_ACTION_GET_TIMESTAMP =
        1, ///< Retrieves a file's last-modified timestamp. In: "u16*, UTF-16 Path", Out: "u64, Time Stamp".
    ARCHIVE_ACTION_UNKNOWN =
        0x789D, //< Unknown action; calls FSPXI command 0x56. In: "FS_Path instance", Out: "u32[4], Unknown"
} FS_ArchiveAction;

/// Secure save control actions.
typedef enum {
    SECURESAVE_ACTION_DELETE = 0, ///< Deletes a save's secure value. In: "u64, ((SecureValueSlot << 32) |
                                  ///< (TitleUniqueId << 8) | TitleVariation)", Out: "u8, Value Existed"
    SECURESAVE_ACTION_FORMAT = 1, ///< Formats a save. No inputs/outputs.
} FS_SecureSaveAction;

/// File control actions.
typedef enum {
    FILE_ACTION_UNKNOWN = 0,
} FS_FileAction;

/// Directory control actions.
typedef enum {
    DIRECTORY_ACTION_UNKNOWN = 0,
} FS_DirectoryAction;

/// Directory entry.
typedef struct {
    u16 name[0x106];      ///< UTF-16 directory name.
    char shortName[0x0A]; ///< File name.
    char shortExt[0x04];  ///< File extension.
    u8 valid;             ///< Valid flag. (Always 1)
    u8 reserved;          ///< Reserved.
    u32 attributes;       ///< Attributes.
    u64 fileSize;         ///< File size.
} FS_DirectoryEntry;

/// Archive resource information.
typedef struct {
    u32 sectorSize;    ///< Size of each sector, in bytes.
    u32 clusterSize;   ///< Size of each cluster, in bytes.
    u32 totalClusters; ///< Total number of clusters.
    u32 freeClusters;  ///< Number of free clusters.
} FS_ArchiveResource;

/// Program information.
typedef struct {
    u64 programId;              ///< Program ID.
    FS_MediaType mediaType : 8; ///< Media type.
    u8 padding[7];              ///< Padding.
} FS_ProgramInfo;

/// Product information.
typedef struct {
    char productCode[0x10]; ///< Product code.
    char companyCode[0x2];  ///< Company code.
    u16 remasterVersion;    ///< Remaster version.
} FS_ProductInfo;

/// Integrity verification seed.
typedef struct {
    u8 aesCbcMac[0x10];   ///< AES-CBC MAC over a SHA256 hash, which hashes the first 0x110-bytes of the cleartext SEED.
    u8 movableSed[0x120]; ///< The "nand/private/movable.sed", encrypted with AES-CTR using the above MAC for the
                          ///< counter.
} FS_IntegrityVerificationSeed;

/// Ext save data information.
typedef struct PACKED {
    FS_MediaType mediaType : 8; ///< Media type.
    u8 unknown;                 ///< Unknown.
    u16 reserved1;              ///< Reserved.
    u64 saveId;                 ///< Save ID.
    u32 reserved2;              ///< Reserved.
} FS_ExtSaveDataInfo;

/// System save data information.
typedef struct {
    FS_MediaType mediaType : 8; ///< Media type.
    u8 unknown;                 ///< Unknown.
    u16 reserved;               ///< Reserved.
    u32 saveId;                 ///< Save ID.
} FS_SystemSaveDataInfo;

/// Device move context.
typedef struct {
    u8 ivs[0x10];              ///< IVs.
    u8 encryptParameter[0x10]; ///< Encrypt parameter.
} FS_DeviceMoveContext;

/// Filesystem path data, detailing the specific target of an operation.
typedef struct {
    FS_PathType type; ///< FS path type.
    u32 size;         ///< FS path size.
    const void* data; ///< Pointer to FS path data.
} FS_Path;

/// SDMC/NAND speed information
typedef struct {
    bool highSpeedModeEnabled; ///< Whether or not High Speed Mode is enabled.
    bool usesHighestClockRate; ///< Whether or not a clock divider of 2 is being used.
    u16 sdClkCtrl;             ///< The value of the SD_CLK_CTRL register.
} FS_SdMmcSpeedInfo;

/// Filesystem archive handle, providing access to a filesystem's contents.
typedef u64 FS_Archive;

/// Initializes FS.
Result fsInit(void);

/// Exits FS.
void fsExit(void);

/**
 * @brief Creates an FS_Path instance.
 * @param type Type of path.
 * @param path Path to use.
 * @return The created FS_Path instance.
 */
FS_Path fsMakePath(FS_PathType type, const void* path);

/**
 * @brief Initializes a FSUSER session.
 * @param session The handle of the FSUSER session to initialize.
 */
Result FSUSER_Initialize(Handle session);

/**
 * @brief Opens a file.
 * @param out Pointer to output the file handle to.
 * @param archive Archive containing the file.
 * @param path Path of the file.
 * @param openFlags Flags to open the file with.
 * @param attributes Attributes of the file.
 */
Result FSUSER_OpenFile(Handle* out, FS_Archive archive, FS_Path path, u32 openFlags, u32 attributes);

/**
 * @brief Opens a file directly, bypassing the requirement of an opened archive handle.
 * @param out Pointer to output the file handle to.
 * @param archiveId ID of the archive containing the file.
 * @param archivePath Path of the archive containing the file.
 * @param filePath Path of the file.
 * @param openFlags Flags to open the file with.
 * @param attributes Attributes of the file.
 */
Result FSUSER_OpenFileDirectly(Handle* out, FS_ArchiveID archiveId, FS_Path archivePath, FS_Path filePath,
                               u32 openFlags, u32 attributes);

/**
 * @brief Deletes a file.
 * @param archive Archive containing the file.
 * @param path Path of the file.
 */
Result FSUSER_DeleteFile(FS_Archive archive, FS_Path path);

// /**
//  * @brief Deletes a directory, failing if it is not empty.
//  * @param archive Archive containing the directory.
//  * @param path Path of the directory.
//  */
// Result FSUSER_DeleteDirectory(FS_Archive archive, FS_Path path);

// /**
//  * @brief Deletes a directory, also deleting its contents.
//  * @param archive Archive containing the directory.
//  * @param path Path of the directory.
//  */
// Result FSUSER_DeleteDirectoryRecursively(FS_Archive archive, FS_Path path);

/**
 * @brief Creates a file.
 * @param archive Archive to create the file in.
 * @param path Path of the file.
 * @param attributes Attributes of the file.
 * @param fileSize Size of the file.
 */
Result FSUSER_CreateFile(FS_Archive archive, FS_Path path, u32 attributes, u64 fileSize);

// /**
//  * @brief Creates a directory
//  * @param archive Archive to create the directory in.
//  * @param path Path of the directory.
//  * @param attributes Attributes of the directory.
//  */
// Result FSUSER_CreateDirectory(FS_Archive archive, FS_Path path, u32 attributes);

// /**
//  * @brief Opens a directory.
//  * @param out Pointer to output the directory handle to.
//  * @param archive Archive containing the directory.
//  * @param path Path of the directory.
//  */
// Result FSUSER_OpenDirectory(Handle *out, FS_Archive archive, FS_Path path);

/**
 * @brief Opens an archive.
 * @param archive Pointer to output the opened archive to.
 * @param id ID of the archive.
 * @param path Path of the archive.
 */
Result FSUSER_OpenArchive(FS_Archive* archive, FS_ArchiveID id, FS_Path path);

/**
 * @brief Closes an archive.
 * @param archive Archive to close.
 */
Result FSUSER_CloseArchive(FS_Archive archive);

// /**
//  * @brief Gets the number of free bytes within an archive.
//  * @param freeBytes Pointer to output the free bytes to.
//  * @param archive Archive to check.
//  */
// Result FSUSER_GetFreeBytes(u64* freeBytes, FS_Archive archive);

// /**
//  * @brief Checks a process's authority to access a save data archive.
//  * @param access Pointer to output the access status to.
//  * @param mediaType Media type of the save data.
//  * @param saveId ID of the save data.
//  * @param processId ID of the process to check.
//  */
// Result FSUSER_CheckAuthorityToAccessExtSaveData(bool* access, FS_MediaType mediaType, u64 saveId, u32 processId);

/**
 * @brief Creates ext save data.
 * @param info Info of the save data.
 * @param directories Number of directories.
 * @param files Number of files.
 * @param sizeLimit Size limit of the save data.
 * @param smdhSize Size of the save data's SMDH data.
 * @param smdh SMDH data.
 */
Result FSUSER_CreateExtSaveData(FS_ExtSaveDataInfo info, u32 directories, u32 files, u64 sizeLimit, u32 smdhSize,
                                u8* smdh);

// /**
//  * @brief Deletes ext save data.
//  * @param info Info of the save data.
//  */
// Result FSUSER_DeleteExtSaveData(FS_ExtSaveDataInfo info);

// /**
//  * @brief Gets an ext data archive's block information.
//  * @param totalBlocks Pointer to output the total blocks to.
//  * @param freeBlocks Pointer to output the free blocks to.
//  * @param blockSize Pointer to output the block size to.
//  * @param info Info of the save data.
//  */
// Result FSUSER_GetExtDataBlockSize(u64* totalBlocks, u64* freeBlocks, u32* blockSize, FS_ExtSaveDataInfo info);

// /**
//  * @brief Enumerates ext save data.
//  * @param idsWritten Pointer to output the number of IDs written to.
//  * @param idsSize Size of the IDs buffer.
//  * @param mediaType Media type to enumerate over.
//  * @param idSize Size of each ID element.
//  * @param shared Whether to enumerate shared ext save data.
//  * @param ids Pointer to output IDs to.
//  */
// Result FSUSER_EnumerateExtSaveData(u32* idsWritten, u32 idsSize, FS_MediaType mediaType, u32 idSize, bool shared, u8*
// ids);

// /**
//  * @brief Opens a handle to a sub-section of a file.
//  * @param handle Handle of the file.
//  * @param subFile Pointer to output the sub-file to.
//  * @param offset Offset of the sub-section.
//  * @param size Size of the sub-section.
//  */
// Result FSFILE_OpenSubFile(Handle handle, Handle* subFile, u64 offset, u64 size);

/**
 * @brief Reads from a file.
 * @param handle Handle of the file.
 * @param bytesRead Pointer to output the number of bytes read to.
 * @param offset Offset to read from.
 * @param buffer Buffer to read to.
 * @param size Size of the buffer.
 */
Result FSFILE_Read(Handle handle, u32* bytesRead, u64 offset, void* buffer, u32 size);

/**
 * @brief Writes to a file.
 * @param handle Handle of the file.
 * @param bytesWritten Pointer to output the number of bytes written to.
 * @param offset Offset to write to.
 * @param buffer Buffer to write from.
 * @param size Size of the buffer.
 * @param flags Flags to use when writing.
 */
Result FSFILE_Write(Handle handle, u32* bytesWritten, u64 offset, const void* buffer, u32 size, u32 flags);

/**
 * @brief Gets the size of a file.
 * @param handle Handle of the file.
 * @param size Pointer to output the size to.
 */
Result FSFILE_GetSize(Handle handle, u64* size);

/**
 * @brief Closes a file.
 * @param handle Handle of the file.
 */
Result FSFILE_Close(Handle handle);

/**
 * @brief Flushes a file's contents.
 * @param handle Handle of the file.
 */
Result FSFILE_Flush(Handle handle);
