#pragma once

#include <3ds.h>
#include <string>
#include <functional>

#include "element.hpp"

namespace UI {

class Button : public Element {
public:
    using ButtonEvent = std::function<void(Button*)>;

    Button(const std::string& text, int x, int y, int width, int height, uint32_t color, ButtonEvent func);

    void update(const touchPosition& touchPos) override;
    void draw() const override;
    void setText(std::string text);
    std::string getText() const;
    void setPosition(int x, int y) override;
    void setPosition(Position& pos) override;

    void setColor(uint32_t color_) {
        color = color_;
    }

    void setDepth(float depth_) {
        depth = depth_;
    }

    float getDepth() {
        return depth;
    }

private:
    bool touchIsOver(const touchPosition& touchPos) {
        return (touchPos.px > pos.x) && (touchPos.px < pos.x + width) && (touchPos.py > pos.y) && (touchPos.py < pos.y + height);
    }

    void resetTextPos();

    std::string text;
    int width;
    int height;
    float depth = 0.5f;
    uint32_t color;
    ButtonEvent func = nullptr;
    Position textPos;
    touchPosition prevTouchPos;
    touchPosition curTouchPos;
    bool held = false;
};
} // namespace UI
