#pragma once

#include <string>

/// Returns a new string with:
/// - Leading spaces removed.
/// - Line breaks replaced with spaces.
/// - Consecutive spaces removed.
std::string SanitizedString(std::string s);
