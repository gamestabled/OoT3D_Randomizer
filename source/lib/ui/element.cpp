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

void Element::draw() const {
}
