#include "labelled_select.hpp"

#include "graphics.hpp"

namespace UI {

LabelledSelect::LabelledSelect(const std::string text_, const std::vector<std::string> options_, int x_, int y_, int width_, int height_, int* affectedValue_) : Element(x_, y_), width(width_), height(height_), text(text_),
        select(options_, x_ + width_ - (0.3f * width_), y_ + (0.16f * height_), 0.25f * width_, 0.66f * height_, affectedValue_) {
    select.setParent(this);
}

void LabelledSelect::update(const touchPosition& touchPos) {
    select.update(touchPos);
}

void LabelledSelect::draw() const {
    C2D_DrawRectSolid(pos.x, pos.y, 0.5f, width, height, BACKGROUND_COLOR);
    select.draw();
    Graphics::drawText(text, pos.x + 14, pos.y + (height / 2) - 7, GFX_DEPTH_DEFAULT, 0.5f, 0xFF000000);
}
}
