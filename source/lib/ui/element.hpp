#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

namespace UI {

class Position {
public:
    int x;
    int y;
};

// The base class for all UI elements
class Element {
public:
    Element(int x_, int y_) {
        pos.x = x_;
        pos.y = y_;
    }

    Element(Position pos_) : pos(pos_) {
    }

    void setParent(Element* parent_) {
        parent = parent_;
    }

    Element* getParent() const {
        return parent;
    }

    const Position& getPosition() const;
    virtual void setPosition(int x, int y);
    virtual void setPosition(Position& pos);
    virtual void update(const touchPosition& touchPos);
    virtual void draw() const;

protected:
    Position pos;
    Element* parent = nullptr;
};
} // namespace UI
