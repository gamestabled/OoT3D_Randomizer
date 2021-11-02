#pragma once

#include "element.hpp"

namespace UI {

class Scrollbar : public Element {
public:
    Scrollbar(int x, int y, int width, int height, int numTotal, int numDisplayed);

    void draw() const override;

    void setScrollBarSize(int numTotal, int numDisplayed);
    void setScrollPercent(float percent);

private:
    int triangleHeight;

    float barSize;
    int barY;
    int barYOffset;

    int barTrackLength;
    int barHeight;

};
}
