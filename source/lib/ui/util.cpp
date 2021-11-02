#include <3ds.h>
#include "util.hpp"

namespace UI {
namespace Util {

bool touchPressed(const touchPosition& pos) {
    return (pos.px != 0) && (pos.py != 0);
}

std::string getInput(const char* hintText) {
    SwkbdState swkbd;
    char text[60];
    SwkbdButton button = SWKBD_BUTTON_NONE;

    swkbdInit(&swkbd, SWKBD_TYPE_WESTERN, 2, -1);
    swkbdSetValidation(&swkbd, SWKBD_NOTBLANK, SWKBD_FILTER_AT | SWKBD_FILTER_PERCENT | SWKBD_FILTER_BACKSLASH, 2);
    swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);
    swkbdSetHintText(&swkbd, hintText);
    swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);

    button = swkbdInputText(&swkbd, text, sizeof(text));

    if (button == SWKBD_BUTTON_LEFT) {
        return "";
    }

    return std::string(text);
}
}
}
