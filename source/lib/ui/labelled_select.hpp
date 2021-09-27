#pragma once

#include <3ds.h>
#include <string>
#include <vector>

#include "element.hpp"
#include "select.hpp"

namespace UI {

class LabelledSelect : public Element {
public:
    LabelledSelect(const std::string text, const std::vector<std::string> options, int x, int y, int width, int height, int* affectedValue);

    void update(const touchPosition& touchPos) override;
    void draw() const override;

    void setOpenListener(Select::SelectOpenListener* listener) {
        select.setOpenListener(listener);
    }

private:
    static const uint32_t BACKGROUND_COLOR = 0xFFCCCCCC;

    const int width;
    const int height;

    std::string text;
    Select select;
};
} // namespace UI
