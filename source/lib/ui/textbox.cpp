#include "textbox.hpp"
#include "util.hpp"

#include "graphics.hpp"

using namespace UI;

Textbox::Textbox(const std::string& text_, int x_, int y_, int width_, uint32_t color_) :
    Element(x_, y_, width_, 0), text(text_), color(color_) {
}

void Textbox::draw() const {
    Graphics::drawTextWrap(text, pos.x, pos.y, GFX_DEPTH_DEFAULT, 0.5f, width, color);
}

void Textbox::setText(std::string text_) {
    text = text_;
}

std::string Textbox::getText() const {
    return text;
}

void Textbox::setWidth(int width_) {
    setSize(width_, 0);
}
