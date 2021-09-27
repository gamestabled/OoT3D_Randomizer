#include <3ds.h>

namespace Util {
    bool touchPressed(const touchPosition& pos) {
        return (pos.px != 0) && (pos.py != 0);
    }
}
