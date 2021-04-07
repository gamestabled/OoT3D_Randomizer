#include "debug.hpp"

void CitraPrint (std::string_view str) {
   svcOutputDebugString(str.data(), str.length());
}
