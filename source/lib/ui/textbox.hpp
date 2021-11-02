#pragma once

#include <3ds.h>
#include <string>
#include <functional>

#include "element.hpp"

namespace UI {

class Textbox : public Element {
public:
    Textbox(const std::string& text, int x, int y, int width, uint32_t color);

    void draw() const override;
    void setText(std::string text);
    std::string getText() const;

    void setColor(uint32_t color_) {
        color = color_;
    }

    void setWidth(int width_);

private:
    std::string text;
    uint32_t color;
};
} // namespace UI
