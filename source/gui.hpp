#pragma once

#include <vector>

#include "lib/ui.hpp"

class GUI : public UI::Select::SelectOpenListener {
public:
    void signalOpen(UI::Select* openSelect) override {
        setSpotlightElement(openSelect);
    }

    void signalClose(UI::Select* closeSelect) override {
        clearSpotlightElement();
    }

    // Adds an element to the top screen on the next frame
    void addElementToTop(UI::Element* element) {
        topFrameElements.push_back(element);
    }

    // Adds an element to the bottom screen on the next frame
    void addElementToBottom(UI::Element* element) {
        bottomFrameElements.push_back(element);
    }

    // Sets an element as the spotlight element
    void setSpotlightElement(UI::Element* element) {
        spotlightElement = element;
    }

    void clearSpotlightElement() {
        spotlightElement = nullptr;
    }

    void doFrame(const touchPosition& touchPos) {
        updateAll(touchPos);

        graphics->beginFrame();
        graphics->startTopScreen();
        drawTopScreen();
        graphics->startBottomScreen();
        drawBottomScreen();
        graphics->endFrame();

        clearElements();
    }

    void updateAll(const touchPosition& touchPos) {
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

    void drawTopScreen() {
        for (auto element : topFrameElements) {
            element->draw();
        }
    }

    void drawBottomScreen() {
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

private:
    void clearElements() {
        topFrameElements.clear();
        bottomFrameElements.clear();
    }

    Graphics* graphics = Graphics::getInstance();
    std::vector<UI::Element*> topFrameElements;
    std::vector<UI::Element*> bottomFrameElements;
    UI::Element* spotlightElement = nullptr;
};
