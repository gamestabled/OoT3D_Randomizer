#ifndef _EXTDATA_H_
#define _EXTDATA_H_

#include "3ds/result.h"
#include "3ds/services/fs.h"

#define EXTDATA_MAXFILESIZE (1 << 20)

/**
 * @brief Initializes the fs and srvpm services.
 */
Result extDataInit();

/**
 * @brief Mounts the extData archive. Creates it first if it does not exist yet.
 * @param out Pointer to output the archive handle to.
 */
Result extDataMount(FS_Archive* out);

/**
 * @brief Creates a file in extdata with the given size and opens it. Fails if the file already exists.
 * @param out Pointer to output the file handle to. NULL if you only want to create the file.
 * @param fsa The archive obtained from extDataMount.
 * @param filename The path to the file to create in the extData.
 * @param filesize The size of the file to create
 */
Result extDataCreateFile(Handle* out, FS_Archive fsa, char* filename, u64 filesize);

/**
 * @brief Opens a file from extData. If it does not exist yet, creates it with the given size.
 * @param out Pointer to output the file handle to.
 * @param fsa The archive obtained from extDataMount.
 * @param filename The path to the file to create in the extData.
 * @param filesize The size of the file to create
 */
Result extDataOpenOrCreateFile(Handle* out, FS_Archive fsa, char* filename, u64 filesize);

/**
 * @brief Reads data from an extData file.
 * @param handle File handle obtained from extDataOpen.
 * @param buf_out Buffer to write the read data to.
 * @param offset Offset to start reading from.
 * @param count Number of bytes to read.
 * @return The number of bytes read.
 */
u32 extDataReadFile(Handle handle, void* buf_out, u64 offset, u32 count);

/**
 * @brief Reads data from an extData file directly without having to open or close it manually.
 * @param fsa The archive obtained from extDataMount.
 * @param filename The path to the file to create in the extData.
 * @param buf_out Buffer to write the read data to.
 * @param offset Offset to start reading from.
 * @param count Number of bytes to read.
 * @return The number of bytes read. <0 indicates an error.
 */
u32 extDataReadFileDirectly(FS_Archive fsa, char* filename, void* buf_out, u64 offset, u32 count);

/**
 * @brief Writes data to an extData file.
 * @param handle File handle obtained from extDataOpen.
 * @param buf_out Buffer to read the data from.
 * @param offset Offset to start writing from.
 * @param count Number of bytes to write.
 * @return The number of bytes written. <0 indicates an error.
 */
u32 extDataWriteFile(Handle handle, void* buf, u64 offset, u32 count);

/**
 * @brief Reads data from an extData file directly without having to open or close it manually.
 * If offset == 0, the file is resized/created automatically if it is too small/does not exist.
 * @param fsa The archive obtained from extDataMount.
 * @param filename The path to the file to create in the extData.
 * @param buf_out Buffer to write the read data to.
 * @param offset Offset to start reading from.
 * @param count Number of bytes to read.
 * @return The number of bytes read. <0 indicates an error.
 */
u32 extDataWriteFileDirectly(FS_Archive fsa, char* filename, void* buf, u64 offset, u32 count);

/**
 * @brief Unmounts the extData archive.
 * @param fsa FS_Archive : The archive obtained from extDataMount.
 */
#define extDataUnmount(fsa) FSUSER_CloseArchive(fsa)

/**
 * @brief Deletes a file from extData.
 * @param fsa FS_Archive : The archive obtained from extDataMount.
 * @param filename char* : The path to the file to delete in the extData.
 */
#define extDataDeleteFile(fsa, filename) FSUSER_DeleteFile(fsa, fsMakePath(PATH_ASCII, filename))

/**
 * @brief Opens a file from extData.
 * @param out Handle* : Pointer to output the file handle to.
 * @param fsa FS_Archive : The archive obtained from extDataMount.
 * @param filename char* : The path to the file to open in the extData.
 */
#define extDataOpen(out, fsa, filename) \
    FSUSER_OpenFile(out, fsa, fsMakePath(PATH_ASCII, filename), FS_OPEN_WRITE | FS_OPEN_READ, 0)

/**
 * @brief Closes a file opened from extdata.
 * @param handle Handle : File handle obtained from extDataOpen
 */
#define extDataClose(handle) FSFILE_Close(handle)

#endif // _EXTDATA_H_
