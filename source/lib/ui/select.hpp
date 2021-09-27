#pragma once

#include <3ds.h>
#include <string>
#include <vector>

#include "element.hpp"
#include "button.hpp"

namespace UI {

class Select : public Element {
public:
    Select(const std::vector<std::string> options, int x, int y, int width, int height, int* affectedValue);

    void setCurrentOption(size_t option);
    void open();
    void close();
    void toggleOpen();

    static void toggleOpenFromPress(Button* button);

    void update(const touchPosition& touchPos) override;
    void draw() const override;

    class SelectOpenListener {
    public:
        virtual void signalOpen(Select* openSelect) = 0;
        virtual void signalClose(Select* closeSelect) = 0;
    };

    void setOpenListener(SelectOpenListener* listener) {
        openListener = listener;
    }

private:
    static const uint32_t BACKGROUND_COLOR = 0xFFCCCCCC;
    static const uint32_t SELECTED_COLOR = 0xFF44CC44;

    static void toggleFromPress(Button*);

    const int width;
    const int height;

    std::vector<std::string> options;
    std::vector<Button> optionButtons;
    Button mainButton;
    size_t currentOption = 0;
    bool isOpen = false;
    int* affectedValue;
    SelectOpenListener* openListener = nullptr;
};
} // namespace UI
