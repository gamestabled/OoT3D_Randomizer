#include "scroll_bar.hpp"

namespace UI {

Scrollbar::Scrollbar(int x_, int y_, int width_, int height_, int numTotal_, int numDisplayed_) : Element(x_, y_, width_, height_), barYOffset(0) {
    triangleHeight = width - 1;
    barY = triangleHeight + 1;
    barTrackLength = height - (2 * width);

    setScrollBarSize(numTotal_, numDisplayed_);
}

void Scrollbar::draw() const {
    C2D_DrawTriangle(pos.x + (width / 2), pos.y, UI::BACKGROUND_COLOR, pos.x, pos.y + triangleHeight, UI::BACKGROUND_COLOR, pos.x + width, pos.y + triangleHeight, UI::BACKGROUND_COLOR, 0.5f);
    C2D_DrawTriangle(pos.x + (width / 2), pos.y + height, UI::BACKGROUND_COLOR, pos.x, pos.y + height - triangleHeight, UI::BACKGROUND_COLOR, pos.x + width, pos.y + height - triangleHeight, UI::BACKGROUND_COLOR, 0.5f);

    C2D_DrawRectSolid(pos.x, pos.y + barY + barYOffset, 0.5f, width, barHeight, UI::BACKGROUND_COLOR);
}

void Scrollbar::setScrollBarSize(int numTotal, int numDisplayed) {
    barSize = (float)numDisplayed / (float)numTotal;
    if (barSize > 1.0f) {
        barSize = 1.0f;
    }
    barHeight = barSize * (float)barTrackLength;
}

void Scrollbar::setScrollPercent(float percent) {
    barYOffset = percent * (float)(barTrackLength - barHeight);
}
}
