#include "button.hpp"
#include "util.hpp"

#include "graphics.hpp"

using namespace UI;

void Button::resetTextPos() {
    int textWidth = Graphics::getTextWidth(text.getText());
    if (textWidth > textWrapLength) {
        textWidth = textWrapLength;
    }
    int textHeight = 14;
    if (alignTextLeft) {
        textPos.x = pos.x + 6;
    } else {
        textPos.x = pos.x + (width / 2) - (textWidth / 2);
    }
    textPos.y = pos.y + (height / 2) - (textHeight / 2);
    text.setPosition(textPos);
    text.setWidth(textWidth);
}

Button::Button(const std::string& text_, int x_, int y_, int width_, int height_, uint32_t color_, ButtonEvent func_, bool alignTextLeft_) :
        Element(x_, y_, width_, height_), text(text_, 0, 0, 0, 0xFF000000), color(color_), func(func_), textWrapLength((float)width_ * 0.8f), alignTextLeft(alignTextLeft_) {
    resetTextPos();
}

void Button::setPosition(int x, int y) {
    this->Element::setPosition(x, y);
    resetTextPos();
}

void Button::setPosition(Position& pos) {
    Button::setPosition(pos.x, pos.y);
}

void Button::setSize(int width_, int heigth_) {
    width = width_;
    height = heigth_;
    textWrapLength = (float)width_ * 0.8f;
    resetTextPos();
}

void Button::update(const touchPosition& touchPos) {
    prevTouchPos = curTouchPos;
    curTouchPos = touchPos;

    if (touchIsOver(touchPos) && !Util::touchPressed(prevTouchPos)) {
        held = true;
    } else if (held && !Util::touchPressed(touchPos) && touchIsOver(prevTouchPos)) {
        held = false;
        if (func) {
            func(this);
        }
    } else if (!Util::touchPressed(touchPos)) {
        held = false;
    }
}

void Button::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if (hovered && (kDown & KEY_A)) {
        if (func) {
            func(this);
        }
    } else {
        update(touchPos);
    }
}

void Button::draw() const {
    if (held) {
        C2D_DrawRectSolid(pos.x, pos.y, 0.5f, width, height, 0xFF444444);
    } else {
        C2D_DrawRectSolid(pos.x, pos.y, 0.5f, width, height, color);
    }
    text.draw();
    if (hovered) {
        drawHover();
    }
}

void Button::drawHover() const {
    C2D_DrawRectangle(pos.x, pos.y, 0.5f, width, height, 0x8800EE00, 0x8800EE00, 0x8800EE00, 0x8800EE00);
}

void Button::setText(std::string text_) {
    text.setText(text_);
    resetTextPos();
}

std::string Button::getText() const {
    return text.getText();
}
