#include "debug.hpp"

#include <3ds.h>

void CitraPrint (std::string_view str) {
  svcOutputDebugString(str.data(), str.length());
}
