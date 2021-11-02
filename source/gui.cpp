#include "gui.hpp"

void GUI::doFrame(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    updateAll(touchPos, kDown, kHeld);

    graphics->beginFrame();
    graphics->startTopScreen();
    drawTopScreen();
    graphics->startBottomScreen();
    drawBottomScreen();
    graphics->endFrame();

    clearElements();
}

void GUI::updateAll(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if (spotlightElement != nullptr) {
        spotlightElement->update(touchPos, kDown, kHeld);
    } else {
        for (auto element : topFrameElements) {
            element->update(touchPos, kDown, kHeld);
        }
        for (auto element : bottomFrameElements) {
            element->update(touchPos, kDown, kHeld);
        }
    }
}

void GUI::clearElements() {
    topFrameElements.clear();
    bottomFrameElements.clear();
}

void GUI::drawTopScreen() {
    for (auto element : topFrameElements) {
        element->draw();
    }
}

void GUI::drawBottomScreen() {
    if (spotlightElement != nullptr) {
        C2D_Fade(0x44000000);
    }

    for (auto element : bottomFrameElements) {
        element->draw();
    }

    if (spotlightElement != nullptr) {
        C2D_Fade(0);
        spotlightElement->draw();
    }
}
