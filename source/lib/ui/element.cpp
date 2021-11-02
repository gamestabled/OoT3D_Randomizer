#include "element.hpp"

using namespace UI;

const Position& Element::getPosition() const {
    return pos;
}

void Element::setPosition(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void Element::setPosition(Position& pos_) {
    pos = pos_;
}

void Element::update(const touchPosition& touchPos) {
}

void Element::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    this->update(touchPos);
}

void Element::draw() const {
}

const uint32_t UI::BACKGROUND_COLOR = 0xFFCCCCCC;
const int UI::SCREEN_BOT_WIDTH = 320;
const int UI::SCREEN_BOT_HEIGHT = 240;
const int UI::SCREEN_TOP_WIDTH = 400;
const int UI::SCREEN_TOP_HEIGHT = 240;