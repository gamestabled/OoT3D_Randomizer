#include "description_table_jsonc.h"
#include "descriptions.hpp"
#include "json.hpp"

#include <string>
#include <unordered_map>

using json = nlohmann::json;

std::unordered_map<std::string, std::string> descriptionTable;

void InitDescriptionTable() {
    const char* data = reinterpret_cast<const char*>(description_table_jsonc);
    std::string text(data, description_table_jsonc_size);

    json table = json::parse(text.begin(), text.end(), nullptr, true, true);
    for (auto i = table.begin(); i != table.end(); ++i) {
        const std::string& key = i.key();
        const json& entry      = i.value();

        if (entry.is_array()) {
            std::string joined;
            joined.reserve(entry.size() * 64);
            for (size_t j = 0; j < entry.size(); ++j) {
                if (j > 0) {
                    joined.push_back('\n');
                }
                joined += entry[j].get<std::string>();
            }
            descriptionTable.emplace(key, std::move(joined));
        } else if (entry.is_string()) {
            descriptionTable.emplace(key, entry.get<std::string>());
        }
    }
}

std::string LoadDesc(std::string name) {
    if (descriptionTable.empty()) {
        InitDescriptionTable();
    }

    auto it = descriptionTable.find(name);
    if (it != descriptionTable.end()) {
        return it->second;
    }
    return name;
}
