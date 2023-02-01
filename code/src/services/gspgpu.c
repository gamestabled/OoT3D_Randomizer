#include "3ds/types.h"
#include "3ds/result.h"
#include "3ds/svc.h"
#include "3ds/srv.h"
#include "3ds/synchronization.h"
#include "3ds/services/gspgpu.h"
#include "3ds/ipc.h"
#include <string.h>

#define GSP_EVENT_STACK_SIZE 0x1000

Handle gspGpuHandle;
static int gspRefCount;

Result gspInit(void) {
    Result res = 0;
    if (AtomicPostIncrement(&gspRefCount))
        return 0;
    // res = srvGetServiceHandle(&gspGpuHandle, "gsp::Gpu");
    res = srvGetServiceHandleDirect(&gspGpuHandle, "gsp::Gpu");
    if (R_FAILED(res))
        AtomicDecrement(&gspRefCount);
    return res;
}

Result GSPGPU_SetBufferSwap(u32 screenid, GSPGPU_FramebufferInfo* framebufinfo) {
    u32* cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x5, 8, 0); // 0x50200
    cmdbuf[1] = screenid;
    memcpy(&cmdbuf[2], framebufinfo, sizeof(GSPGPU_FramebufferInfo));

    Result ret = 0;
    if (R_FAILED(ret = svcSendSyncRequest(gspGpuHandle)))
        return ret;

    return cmdbuf[1];
}