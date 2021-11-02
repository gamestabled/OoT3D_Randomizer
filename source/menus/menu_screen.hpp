#pragma once

#include <3ds.h>
#include <stack>
#include "../lib/ui.hpp"

class MenuScreen : public UI::Element {
public:
    MenuScreen(int x, int y) : UI::Element(x, y) {}

    virtual UI::Element* getTopScreenElement() = 0;
};

class MenuStack : public UI::Element {
public:
    MenuStack() : UI::Element(0, 0) {}

    static void pushToMenuStack(MenuScreen* menu) {
        menuStack.push(menu);
    }

    static void popMenuStack() {
        menuStack.pop();
    }

    static size_t menuStackSize() {
        return menuStack.size();
    }

    static UI::Element* getTopScreenElement() {
        return menuStack.top()->getTopScreenElement();
    }

    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld) override {
        menuStack.top()->update(touchPos, kDown, kHeld);
    }

    void draw() const override {
        menuStack.top()->draw();
    }

private:
    inline static std::stack<MenuScreen*> menuStack;
};
