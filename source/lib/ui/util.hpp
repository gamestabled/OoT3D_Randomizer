#include "3ds.h"

#include <string>

namespace UI {
namespace Util {
    bool touchPressed(const touchPosition& pos);
    std::string getInput(const char* hintText);
}
}
