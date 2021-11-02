#pragma once


extern "C" {
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
}

namespace UI {

extern const uint32_t BACKGROUND_COLOR;
extern const int SCREEN_BOT_WIDTH;
extern const int SCREEN_BOT_HEIGHT;
extern const int  SCREEN_TOP_WIDTH;
extern const int  SCREEN_TOP_HEIGHT;

class Position {
public:
    int x;
    int y;
};

// The base class for all UI elements
class Element {
public:
    Element(int x_, int y_, int width_, int height_) {
        pos.x = x_;
        pos.y = y_;
        width = width_;
        height = height_;
    }

    Element(int x_, int y_) : Element(x_, y_, 0, 0) {}

    Element(Position pos_) : pos(pos_), width(0), height(0) {
    }

    virtual ~Element() {}

    void setParent(Element* parent_) {
        parent = parent_;
    }

    Element* getParent() const {
        return parent;
    }

    void setSize(int width_, int height_) {
        width = width_;
        height = height_;
    }

    const Position& getPosition() const;
    virtual void setPosition(int x, int y);
    virtual void setPosition(Position& pos);
    virtual void update(const touchPosition& touchPos);
    virtual void update(const touchPosition& touchPos, u32 kDown, u32 kHeld);

    virtual void draw() const;

protected:
    Position pos;
    int width;
    int height;
    Element* parent = nullptr;
};
} // namespace UI
