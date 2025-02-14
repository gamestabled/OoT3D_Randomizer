#include <algorithm>
#include <memory>
#include <vector>

#include "utils.hpp"

std::string SanitizedString(std::string s) {
    // Remove leading spaces
    while (s.size() > 0 && s[0] == ' ') {
        s.erase(0, 1);
    }

    // Replace line breaks with spaces
    std::replace(s.begin(), s.end(), '\n', ' ');

    // Remove consecutive spaces
    while (s.find("  ") != std::string::npos) {
        s.erase(s.find("  "), 1);
    }

    return s;
}

using FILEPtr = std::unique_ptr<FILE, decltype(&std::fclose)>;

bool CopyFile(FS_Archive sdmcArchive, const char* dst, const char* src) {
    Result res = 0;
    Handle outFile;
    u32 bytesWritten = 0;
    // Delete dst if it exists
    FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, dst));

    // Open dst destination
    if (!R_SUCCEEDED(res = FSUSER_OpenFile(&outFile, sdmcArchive, fsMakePath(PATH_ASCII, dst),
                                           FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
        return false;
    }

    if (auto file = FILEPtr{ std::fopen(src, "r"), std::fclose }) {
        // obtain file size
        fseek(file.get(), 0, SEEK_END);
        const auto lSize = static_cast<size_t>(ftell(file.get()));
        rewind(file.get());

        // copy file into the buffer
        std::vector<char> buffer(lSize);
        fread(buffer.data(), 1, buffer.size(), file.get());

        // Write the buffer to final destination
        if (!R_SUCCEEDED(res = FSFILE_Write(outFile, &bytesWritten, 0, buffer.data(), buffer.size(), FS_WRITE_FLUSH))) {
            return false;
        }
    }

    FSFILE_Close(outFile);
    return true;
}
