#pragma once

#include <string>
#include <3ds.h>

/// Returns a new string with:
/// - Leading spaces removed.
/// - Line breaks replaced with spaces.
/// - Consecutive spaces removed.
std::string SanitizedString(std::string s);

bool CopyFile(FS_Archive sdmcArchive, const char* dst, const char* src);
