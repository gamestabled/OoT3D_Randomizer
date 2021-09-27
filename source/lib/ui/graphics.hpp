#pragma once

#include <citro2d.h>
#include <string>

#define GFX_DEPTH_DEFAULT 0.5f

class Graphics {
public:
    static Graphics* getInstance() {
        static Graphics instance;
        return &instance;
    }

    void beginFrame();
    void endFrame();
    void startTopScreen();
    void startBottomScreen();

    static size_t getTextWidth(const std::string& str);
    static void drawText(const std::string& str, int x, int y, float depth, float txtScale, uint32_t clr);

private:
    Graphics();
    ~Graphics();

    C3D_RenderTarget* top;
    C3D_RenderTarget* bot;

    Handle renderLock;
};