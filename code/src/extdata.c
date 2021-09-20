#include "3ds/extdata.h"

#include "3ds/result.h"
#include "3ds/services/fs.h"
#include "3ds/srv.h"
#include "3ds/svc.h"

static u8 icn[14016];

Result extDataInit() {
    Result res;
    if(R_FAILED(res = srvInit())) {
        return res;
    }
    return fsInit();
}

Result extDataCreate() {
    FS_ExtSaveDataInfo extInfo;
    u64 icnSize;
    u32 icnSize2;

    Result res;
    Handle icnHandle;

    // Get the path to the icon from exefs
    struct {
        u32 type;
        char filename[8];
    } iconLowPath = {2, "icon"};
    FS_Path iconPath = { PATH_BINARY, sizeof(iconLowPath), &iconLowPath };

    // Open icon 
    if (R_FAILED(res = FSUSER_OpenFileDirectly(&icnHandle, ARCHIVE_ROMFS, fsMakePath(PATH_EMPTY, ""), iconPath, FS_OPEN_READ, 0))) {
        return res;
    }
    // Get file size (should be 14016)
    if (R_FAILED(res = FSFILE_GetSize(icnHandle, &icnSize))) {
        FSFILE_Close(icnHandle);
        return res;
    }
    // Read the icon into the icn buffer
    if (R_FAILED(res = FSFILE_Read(icnHandle, &icnSize2, 0, icn, icnSize))) {
        FSFILE_Close(icnHandle);
        return res;
    }
    // Close the file
    if (R_FAILED(res = FSFILE_Close(icnHandle))) {
        return res;
    }

    extInfo.mediaType = MEDIATYPE_SD;
    extInfo.saveId = 0x33500;
    // Create the extdata with the icon, one folder max (all the files are in /)
    // and per save file: 1 file, 1MiB max
    return FSUSER_CreateExtSaveData(extInfo, 1, 6, 6 * EXTDATA_MAXFILESIZE, icnSize, icn);
}

Result extDataMount(FS_Archive *out) {
    Result res;
    struct {
        u32 media;
        u32 saveIDLo;
        u32 saveIDHi;
    } extDataLowPath = { MEDIATYPE_SD, 0x33500, 0 };
    FS_Path extDataPath = { PATH_BINARY, sizeof(extDataLowPath), &extDataLowPath };

    // Try mounting the extdata archive
    if (R_SUCCEEDED(res = FSUSER_OpenArchive(out, ARCHIVE_EXTDATA, extDataPath))) {
        return res;
    }
    // If it failed, try to create the extdata
    if (R_FAILED(res = extDataCreate())) {
        return res;
    }
    // Mount the created extdata
    return FSUSER_OpenArchive(out, ARCHIVE_EXTDATA, extDataPath);
}

Result extDataCreateFile(Handle *out, FS_Archive fsa, char *filename, u64 filesize) {
    Result res;
    if (R_FAILED(res = FSUSER_CreateFile(fsa, fsMakePath(PATH_ASCII, filename), 0, filesize))) {
        return res;
    }
    if (out == NULL)
        return res;
    return extDataOpen(out, fsa, filename);
}

Result extDataOpenOrCreateFile(Handle *out, FS_Archive fsa, char *filename, u64 filesize) {
    FSUSER_CreateFile(fsa, fsMakePath(PATH_ASCII, filename), 0, filesize);
    return extDataOpen(out, fsa, filename);
}

u32 extDataReadFile(Handle handle, void *buf_out, u64 offset, u32 count) {
    Result res;
    u32 bytes_read;

    if (R_FAILED(res = FSFILE_Read(handle, &bytes_read, offset, buf_out, count))) {
        bytes_read = res;
    }

    return bytes_read;
}


u32 extDataReadFileDirectly(FS_Archive fsa, char *filename, void *buf_out, u64 offset, u32 count) {
    Result res;
    Handle handle;
    u32 bytes_read;

    if (R_FAILED(res = extDataOpen(&handle, fsa, filename))) {
        return res;
    }
    if (R_FAILED(res = FSFILE_Read(handle, &bytes_read, offset, buf_out, count))) {
        bytes_read = res;
    }
    extDataClose(handle);

    return bytes_read;
}

u32 extDataWriteFile(Handle handle, void *buf, u64 offset, u32 count) {
    Result res;
    u32 bytes_written;

    if (R_FAILED(res = FSFILE_Write(handle, &bytes_written, offset, buf, count, FS_WRITE_UPDATE_TIME))) {
        bytes_written = res;
    }
    
    return bytes_written;
}

u32 extDataWriteFileDirectly(FS_Archive fsa, char *filename, void *buf, u64 offset, u32 count) {
    Result res;
    Handle handle;
    u32 bytes_written;
    u64 file_size;

    if (offset == 0) {
        if (R_FAILED(res = extDataOpenOrCreateFile(&handle, fsa, filename, count))) {
            return -1;
        }
        // Resize file automatically if it's too small
        FSFILE_GetSize(handle, &file_size);
        if(file_size < count) {
            extDataClose(handle);
            if (R_FAILED(res = FSUSER_DeleteFile(fsa, fsMakePath(PATH_ASCII, filename)))) {
                return -2;
            }
            if (R_FAILED(res = extDataCreateFile(&handle, fsa, filename, count))) {
                return -3;
            }
        }
    } else {
        if (R_FAILED(res = extDataOpen(&handle, fsa, filename))) {
            return -1;
        }
        FSFILE_GetSize(handle, &file_size);
        if(file_size < offset + count) {
            extDataClose(handle);
            return -2;
        }
    }

    if (R_FAILED(res = FSFILE_Write(handle, &bytes_written, offset, buf, count, FS_WRITE_UPDATE_TIME))) {
        res = -3;
        bytes_written = res;
    }

    extDataClose(handle);
    
    return bytes_written;
}
