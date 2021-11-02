#pragma once

#include <3ds.h>
#include <string>
#include <functional>

#include "element.hpp"
#include "textbox.hpp"

namespace UI {

class Button : public Element {
public:
    using ButtonEvent = std::function<void(Button*)>;

    Button(const std::string& text, int x, int y, int width, int height, uint32_t color, ButtonEvent func, bool alignTextLeft = false);

    void update(const touchPosition& touchPos) override;
    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld);
    void draw() const override;
    void setText(std::string text);
    std::string getText() const;
    void setPosition(int x, int y) override;
    void setPosition(Position& pos) override;

    void setColor(uint32_t color_) {
        color = color_;
    }

    void setSize(int width_, int heigth_);
    void setEvent(ButtonEvent eventFunc) {
        func = eventFunc;
    }

    void setHovered() {
        hovered = true;
    }

    void unsetHovered() {
        hovered = false;
    }

private:
    bool touchIsOver(const touchPosition& touchPos) {
        return (touchPos.px > pos.x) && (touchPos.px < pos.x + width) && (touchPos.py > pos.y) && (touchPos.py < pos.y + height);
    }

    void resetTextPos();
    void drawHover() const;

    Textbox text;
    uint32_t color;
    ButtonEvent func = nullptr;
    Position textPos;
    int textWrapLength;
    touchPosition prevTouchPos;
    touchPosition curTouchPos;
    bool held = false;
    bool hovered = false;
    bool alignTextLeft = false;
};
} // namespace UI
