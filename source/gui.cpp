#include "gui.hpp"

void GUI::doFrame(const touchPosition& touchPos) {
    updateAll(touchPos);

    graphics->beginFrame();
    graphics->startTopScreen();
    drawTopScreen();
    graphics->startBottomScreen();
    drawBottomScreen();
    graphics->endFrame();

    clearElements();
}

void GUI::updateAll(const touchPosition& touchPos) {
    if (spotlightElement != nullptr) {
        spotlightElement->update(touchPos);
    } else {
        for (auto element : topFrameElements) {
            element->update(touchPos);
        }
        for (auto element : bottomFrameElements) {
            element->update(touchPos);
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
