#include "button.hpp"
#include "util.hpp"

#include "graphics.hpp"

using namespace UI;

void Button::resetTextPos() {
    int textWidth = Graphics::getTextWidth(text);
    int textHeight = 14;
    textPos.x = pos.x + (width / 2) - (textWidth / 2);
    textPos.y = pos.y + (height / 2) - (textHeight / 2);
}

Button::Button(const std::string& text_, int x_, int y_, int width_, int height_, uint32_t color_, ButtonEvent func_) : Element(x_, y_), text(text_), width(width_), height(height_), color(color_), func(func_) {
    resetTextPos();
}

void Button::setPosition(int x, int y) {
    this->Element::setPosition(x, y);
    resetTextPos();
}

void Button::setPosition(Position& pos) {
    Button::setPosition(pos.x, pos.y);
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

void Button::draw() const {
    if (held) {
        C2D_DrawRectSolid(pos.x, pos.y, 0.5f, width, height, 0xFF444444);
    } else {
        C2D_DrawRectSolid(pos.x, pos.y, 0.5f, width, height, color);
    }
    Graphics::drawText(text, textPos.x, textPos.y, GFX_DEPTH_DEFAULT, 0.5f, 0xFF000000);
}

void Button::setText(std::string text) {
    this->text = text;
    resetTextPos();
}

std::string Button::getText() const {
    return text;
}
