/* Edited from https://github.com/devkitPro/libctru/blob/6360f4bdb1ca5f8131ffc92640c1dd16afb63083/libctru/source/services/fs.c */

#include <string.h>
#include "3ds/types.h"
#include "3ds/result.h"
#include "3ds/svc.h"
#include "3ds/srv.h"
#include "3ds/synchronization.h"
#include "3ds/services/fs.h"
#include "3ds/ipc.h"

static Handle fsuHandle;
static int fsuRefCount;
static int fsIsInit = 0;

Result fsInit(void)
{
	Result ret = 0;

	if(fsIsInit) return 0;
	if (AtomicPostIncrement(&fsuRefCount)) return 0;

	ret = srvGetServiceHandle(&fsuHandle, "fs:USER");
	if (R_SUCCEEDED(ret))
	{
		ret = FSUSER_Initialize(fsuHandle);
		if (R_FAILED(ret)) svcCloseHandle(fsuHandle);
	}

	if (R_FAILED(ret)) AtomicDecrement(&fsuRefCount);
	else fsIsInit = 1;

	return ret;
}

void fsExit(void)
{
	if (AtomicDecrement(&fsuRefCount)) return;
	svcCloseHandle(fsuHandle);
}

FS_Path fsMakePath(FS_PathType type, const void* path)
{
	FS_Path p = { type, 0, path };
	switch (type)
	{
		case PATH_ASCII:
			p.size = strlen((const char*)path)+1;
			break;
		case PATH_UTF16:
		{
			const u16* str = (const u16*)path;
			while (*str++) p.size++;
			p.size = (p.size+1)*2;
			break;
		}
		case PATH_EMPTY:
			p.size = 1;
			p.data = "";
		default:
			break;
	}
	return p;
}

Result FSUSER_Initialize(Handle session)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x801,0,2); // 0x8010002
	cmdbuf[1] = IPC_Desc_CurProcessId();

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(session))) return ret;

	return cmdbuf[1];
}

Result FSUSER_OpenFile(Handle* out, FS_Archive archive, FS_Path path, u32 openFlags, u32 attributes)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x802,7,2); // 0x80201C2
	cmdbuf[1] = 0;
	cmdbuf[2] = (u32) archive;
	cmdbuf[3] = (u32) (archive >> 32);
	cmdbuf[4] = path.type;
	cmdbuf[5] = path.size;
	cmdbuf[6] = openFlags;
	cmdbuf[7] = attributes;
	cmdbuf[8] = IPC_Desc_StaticBuffer(path.size, 0);
	cmdbuf[9] = (u32) path.data;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	if(out) *out = cmdbuf[3];

	return cmdbuf[1];
}

Result FSUSER_OpenFileDirectly(Handle* out, FS_ArchiveID archiveId, FS_Path archivePath, FS_Path filePath, u32 openFlags, u32 attributes)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x803,8,4); // 0x8030204
	cmdbuf[1] = 0;
	cmdbuf[2] = archiveId;
	cmdbuf[3] = archivePath.type;
	cmdbuf[4] = archivePath.size;
	cmdbuf[5] = filePath.type;
	cmdbuf[6] = filePath.size;
	cmdbuf[7] = openFlags;
	cmdbuf[8] = attributes;
	cmdbuf[9] = IPC_Desc_StaticBuffer(archivePath.size, 2);
	cmdbuf[10] = (u32) archivePath.data;
	cmdbuf[11] = IPC_Desc_StaticBuffer(filePath.size, 0);
	cmdbuf[12] = (u32) filePath.data;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	if(out) *out = cmdbuf[3];

	return cmdbuf[1];
}

Result FSUSER_DeleteFile(FS_Archive archive, FS_Path path)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x804,5,2); // 0x8040142
	cmdbuf[1] = 0;
	cmdbuf[2] = (u32) archive;
	cmdbuf[3] = (u32) (archive >> 32);
	cmdbuf[4] = path.type;
	cmdbuf[5] = path.size;
	cmdbuf[6] = IPC_Desc_StaticBuffer(path.size, 0);
	cmdbuf[7] = (u32) path.data;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	return cmdbuf[1];
}

// Result FSUSER_DeleteDirectory(FS_Archive archive, FS_Path path)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x806,5,2); // 0x8060142
// 	cmdbuf[1] = 0;
// 	cmdbuf[2] = (u32) archive;
// 	cmdbuf[3] = (u32) (archive >> 32);
// 	cmdbuf[4] = path.type;
// 	cmdbuf[5] = path.size;
// 	cmdbuf[6] = IPC_Desc_StaticBuffer(path.size, 0);
// 	cmdbuf[7] = (u32) path.data;

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	return cmdbuf[1];
// }

// Result FSUSER_DeleteDirectoryRecursively(FS_Archive archive, FS_Path path)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x807,5,2); // 0x8070142
// 	cmdbuf[1] = 0;
// 	cmdbuf[2] = (u32) archive;
// 	cmdbuf[3] = (u32) (archive >> 32);
// 	cmdbuf[4] = path.type;
// 	cmdbuf[5] = path.size;
// 	cmdbuf[6] = IPC_Desc_StaticBuffer(path.size, 0);
// 	cmdbuf[7] = (u32) path.data;

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	return cmdbuf[1];
// }

Result FSUSER_CreateFile(FS_Archive archive, FS_Path path, u32 attributes, u64 fileSize)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x808,8,2); // 0x8080202
	cmdbuf[1] = 0;
	cmdbuf[2] = (u32) archive;
	cmdbuf[3] = (u32) (archive >> 32);
	cmdbuf[4] = path.type;
	cmdbuf[5] = path.size;
	cmdbuf[6] = attributes;
	cmdbuf[7] = (u32) fileSize;
	cmdbuf[8] = (u32) (fileSize >> 32);
	cmdbuf[9] = IPC_Desc_StaticBuffer(path.size, 0);
	cmdbuf[10] = (u32) path.data;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	return cmdbuf[1];
}

// Result FSUSER_CreateDirectory(FS_Archive archive, FS_Path path, u32 attributes)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x809,6,2); // 0x8090182
// 	cmdbuf[1] = 0;
// 	cmdbuf[2] = (u32) archive;
// 	cmdbuf[3] = (u32) (archive >> 32);
// 	cmdbuf[4] = path.type;
// 	cmdbuf[5] = path.size;
// 	cmdbuf[6] = attributes;
// 	cmdbuf[7] = IPC_Desc_StaticBuffer(path.size, 0);
// 	cmdbuf[8] = (u32) path.data;

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	return cmdbuf[1];
// }

// Result FSUSER_OpenDirectory(Handle* out, FS_Archive archive, FS_Path path)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x80B,4,2); // 0x80B0102
// 	cmdbuf[1] = (u32) archive;
// 	cmdbuf[2] = (u32) (archive >> 32);
// 	cmdbuf[3] = path.type;
// 	cmdbuf[4] = path.size;
// 	cmdbuf[5] = IPC_Desc_StaticBuffer(path.size, 0);
// 	cmdbuf[6] = (u32) path.data;

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	if(out) *out = cmdbuf[3];

// 	return cmdbuf[1];
// }

Result FSUSER_OpenArchive(FS_Archive* archive, FS_ArchiveID id, FS_Path path)
{
	if(!archive) return -2;

	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x80C,3,2); // 0x80C00C2
	cmdbuf[1] = id;
	cmdbuf[2] = path.type;
	cmdbuf[3] = path.size;
	cmdbuf[4] = IPC_Desc_StaticBuffer(path.size, 0);
	cmdbuf[5] = (u32) path.data;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	*archive = cmdbuf[2] | ((u64) cmdbuf[3] << 32);

	return cmdbuf[1];
}

Result FSUSER_CloseArchive(FS_Archive archive)
{
	if(!archive) return -2;

	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x80E,2,0); // 0x80E0080
	cmdbuf[1] = (u32) archive;
	cmdbuf[2] = (u32) (archive >> 32);

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	return cmdbuf[1];
}

// Result FSUSER_CheckAuthorityToAccessExtSaveData(bool* access, FS_MediaType mediaType, u64 saveId, u32 processId)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x83D,4,0); // 0x83D0100
// 	cmdbuf[1] = mediaType;
// 	cmdbuf[2] = (u32) saveId;
// 	cmdbuf[3] = (u32) (saveId >> 32);
// 	cmdbuf[4] = processId;

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	if(access) *access = cmdbuf[2] & 0xFF;

// 	return cmdbuf[1];
// }

Result FSUSER_CreateExtSaveData(FS_ExtSaveDataInfo info, u32 directories, u32 files, u64 sizeLimit, u32 smdhSize, u8* smdh)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x851,9,2); // 0x8510242
	memcpy(&cmdbuf[1], &info, sizeof(FS_ExtSaveDataInfo));
	cmdbuf[5] = directories;
	cmdbuf[6] = files;
	cmdbuf[7] = (u32) sizeLimit;
	cmdbuf[8] = (u32) (sizeLimit >> 32);
	cmdbuf[9] = smdhSize;
	cmdbuf[10] = IPC_Desc_Buffer(smdhSize, IPC_BUFFER_R);
	cmdbuf[11] = (u32) smdh;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

	return cmdbuf[1];
}

// Result FSUSER_DeleteExtSaveData(FS_ExtSaveDataInfo info)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x852,4,0); // 0x8520100
// 	memcpy(&cmdbuf[1], &info, sizeof(FS_ExtSaveDataInfo));

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	return cmdbuf[1];
// }

// Result FSUSER_GetExtDataBlockSize(u64* totalBlocks, u64* freeBlocks, u32* blockSize, FS_ExtSaveDataInfo info)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x854,4,0); // 0x8540100
// 	memcpy(&cmdbuf[1], &info, sizeof(FS_ExtSaveDataInfo));

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	if(totalBlocks) *totalBlocks = cmdbuf[2] | ((u64) cmdbuf[3] << 32);
// 	if(freeBlocks) *freeBlocks = cmdbuf[4] | ((u64) cmdbuf[5] << 32);
// 	if(blockSize) *blockSize = cmdbuf[6];

// 	return cmdbuf[1];
// }

// Result FSUSER_EnumerateExtSaveData(u32* idsWritten, u32 idsSize, FS_MediaType mediaType, u32 idSize, bool shared, u8* ids)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x855,4,2); // 0x8550102
// 	cmdbuf[1] = idsSize;
// 	cmdbuf[2] = mediaType;
// 	cmdbuf[3] = idSize;
// 	cmdbuf[4] = shared;
// 	cmdbuf[5] = IPC_Desc_Buffer(idsSize, IPC_BUFFER_W);
// 	cmdbuf[6] = (u32) ids;

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(fsuHandle))) return ret;

// 	if(idsWritten) *idsWritten = cmdbuf[2];

// 	return cmdbuf[1];
// }

// Result FSFILE_OpenSubFile(Handle handle, Handle* subFile, u64 offset, u64 size)
// {
// 	u32 *cmdbuf = getThreadCommandBuffer();

// 	cmdbuf[0] = IPC_MakeHeader(0x801,4,0); // 0x8010100
// 	cmdbuf[1] = (u32) offset;
// 	cmdbuf[2] = (u32) (offset >> 32);
// 	cmdbuf[3] = (u32) size;
// 	cmdbuf[4] = (u32) (size >> 32);

// 	Result ret = 0;
// 	if(R_FAILED(ret = svcSendSyncRequest(handle))) return ret;

// 	if(subFile) *subFile = cmdbuf[3];

// 	return cmdbuf[1];
// }

Result FSFILE_Read(Handle handle, u32* bytesRead, u64 offset, void* buffer, u32 size)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x802,3,2); // 0x80200C2
	cmdbuf[1] = (u32) offset;
	cmdbuf[2] = (u32) (offset >> 32);
	cmdbuf[3] = size;
	cmdbuf[4] = IPC_Desc_Buffer(size, IPC_BUFFER_W);
	cmdbuf[5] = (u32) buffer;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(handle))) return ret;

	if(bytesRead) *bytesRead = cmdbuf[2];

	return cmdbuf[1];
}

Result FSFILE_Write(Handle handle, u32* bytesWritten, u64 offset, const void* buffer, u32 size, u32 flags)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x803,4,2); // 0x8030102
	cmdbuf[1] = (u32) offset;
	cmdbuf[2] = (u32) (offset >> 32);
	cmdbuf[3] = size;
	cmdbuf[4] = flags;
	cmdbuf[5] = IPC_Desc_Buffer(size, IPC_BUFFER_R);
	cmdbuf[6] = (u32) buffer;

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(handle))) return ret;

	if(bytesWritten) *bytesWritten = cmdbuf[2];

	return cmdbuf[1];
}

Result FSFILE_GetSize(Handle handle, u64* size)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x804,0,0); // 0x8040000

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(handle))) return ret;

	if(size) *size = cmdbuf[2] | ((u64) cmdbuf[3] << 32);

	return cmdbuf[1];
}

Result FSFILE_Close(Handle handle)
{
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x808,0,0); // 0x8080000

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(handle))) return ret;

	ret = cmdbuf[1];
	if(R_SUCCEEDED(ret)) ret = svcCloseHandle(handle);

	return ret;
}

Result FSFILE_Flush(Handle handle)
{
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x809,0,0); // 0x8090000

	Result ret = 0;
	if(R_FAILED(ret = svcSendSyncRequest(handle))) return ret;

	return cmdbuf[1];
}
