from utils import load_json_with_comments
import os
import sys

HEADER = """// File generated automically. Do not edit. Edit item_table.jsonc instead."
#include "../item_list.hpp"
#include "../logic.hpp"

using namespace Logic;

// clang-format off
void ItemTable_Init() {
"""

FOOTER = "}\n"

################## MAIN ####################

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_item_table.cpp")
data = load_json_with_comments("data/item_table.jsonc")

with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER)

    for key, line_data in data.items():
        item_type = line_data.get("ItemType", "ITEMTYPE_ITEM")
        get_item_id = line_data.get("GetItemID", "GI_RUPEE_GREEN")
        item_class = line_data.get("ItemClass", "ITEMCLASS_NONE")
        logic_ptr = line_data.get("LogicVar", "noVariable")
        hint_key = line_data.get("HintKey", "NONE")

        price = line_data.get("price", None)

        names = line_data.get("Name", {})

        name_text = [
            names.get("NAenglish_", ""),
            names.get("NAfrench_", ""),
            names.get("NAspanish_", ""),
            names.get("EURenglish_", ""),
            names.get("EURfrench_", ""),
            names.get("EURspanish_", ""),
            names.get("EURitalian_", ""),
            names.get("EURgerman_", ""),
        ]

        text_str = ', '.join(f'"{t}"' for t in name_text)

        if price is None:
            out.write(
                f'    itemTable[{key}] = Item({item_type}, {get_item_id}, {item_class}, '
                f'&{logic_ptr}, {hint_key}, Text{{{text_str}}});\n'
            )
        else:
            out.write(
                f'    itemTable[{key}] = Item({item_type}, {get_item_id}, {item_class}, '
                f'&{logic_ptr}, {hint_key}, {price}, Text{{{text_str}}});\n'
            )

    out.write(FOOTER)