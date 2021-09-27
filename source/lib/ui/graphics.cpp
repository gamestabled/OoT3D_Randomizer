#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

#include "graphics.hpp"

Graphics::Graphics() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    svcCreateMutex(&renderLock, false);

    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

Graphics::~Graphics() {
    svcCloseHandle(renderLock);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

void Graphics::beginFrame() {
    svcWaitSynchronization(renderLock, U64_MAX);
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(top, 0xFF2D2D2D);
    C2D_TargetClear(bot, 0xFF2D2D2D);
}

void Graphics::endFrame() {
    C3D_FrameEnd(0);
    svcReleaseMutex(renderLock);
}

void Graphics::startTopScreen() {
    C2D_SceneBegin(top);
}

void Graphics::startBottomScreen() {
    C2D_SceneBegin(bot);
}

size_t Graphics::getTextWidth(const std::string& str) {
    float ret = 0;
    C2D_Text tmpTxt;
    C2D_TextBuf tmpBuf = C2D_TextBufNew(512);

    C2D_TextParse(&tmpTxt, tmpBuf, str.c_str());
    C2D_TextOptimize(&tmpTxt);

    C2D_TextGetDimensions(&tmpTxt, 0.5f, 0.5f, &ret, NULL);
    C2D_TextBufDelete(tmpBuf);

    return (size_t)ret;
}

void Graphics::drawText(const std::string& str, int x, int y, float depth, float txtScale, uint32_t clr) {
    C2D_Text tmpTxt;
    C2D_TextBuf tmpBuf = C2D_TextBufNew(512);

    C2D_TextParse(&tmpTxt, tmpBuf, str.c_str());
    C2D_TextOptimize(&tmpTxt);
    C2D_DrawText(&tmpTxt, C2D_WithColor, (float)x, (float)y, depth, txtScale, txtScale, clr);
    C2D_TextBufDelete(tmpBuf);
}
