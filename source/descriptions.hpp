#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <string_view>

extern std::unordered_map<std::string, std::string> descriptionTable;

extern void InitDescriptionTable();
extern std::string LoadDesc(std::string name);
