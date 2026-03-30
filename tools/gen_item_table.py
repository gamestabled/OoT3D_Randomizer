import json
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

# stops commentjson from being a dependency
def strip_comments(text):
    result = []
    i = 0
    length = len(text)

    in_single = False   # //
    in_multi  = False   # /* */
    in_string = False   # "..."

    while i < length:
        char = text[i]
        next_char = text[i + 1] if i + 1 < length else ""

        # string literals
        if not in_single and not in_multi:
            if char == '"' and (i == 0 or text[i - 1] != '\\'):
                in_string = not in_string
                result.append(char)
                i += 1
                continue

        if in_string:
            result.append(char)
            i += 1
            continue

        # start of a single-line comment
        if not in_multi and char == '/' and next_char == '/':
            in_single = True
            i += 2
            continue

        # start of a multi-line comment
        if not in_single and char == '/' and next_char == '*':
            in_multi = True
            i += 2
            continue

        # end of a single-line comment
        if in_single and char == '\n':
            in_single = False
            result.append(char)
            i += 1
            continue

        # end of a multi-line comment
        if in_multi and char == '*' and next_char == '/':
            in_multi = False
            i += 2
            continue

        # skip characters inside comments
        if in_single or in_multi:
            i += 1
            continue

        # normal character
        result.append(char)
        i += 1

    return ''.join(result)

def load_json_with_comments(path):
    with open(path, encoding="utf-8") as f:
        raw = f.read()

    cleaned = strip_comments(raw)
    return json.loads(cleaned)

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_item_table.cpp")
data = load_json_with_comments("data/item_table.jsonc")

with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER)

    for key, value in data.items():
        if len(value) == 6:
            item_type, get_id, item_class, logic, hint, names = value
            price = None
        elif len(value) == 7:
            item_type, get_id, item_class, logic, hint, price, names = value
        else:
            raise ValueError(f"{key} has invalid field count: {len(value)}")

        logic_ptr = f"&{logic}"

        text = [
            names.get("NAenglish_", ""),
            names.get("NAfrench_", ""),
            names.get("NAspanish_", ""),
            names.get("EURenglish_", ""),
            names.get("EURfrench_", ""),
            names.get("EURspanish_", ""),
            names.get("EURitalian_", ""),
            names.get("EURgerman_", ""),
        ]

        text_str = ', '.join(f'"{t}"' for t in text)

        if price is None:
            out.write(
                f'    itemTable[{key}] = Item({item_type}, {get_id}, {item_class}, '
                f'{logic_ptr}, {hint}, Text{{{text_str}}});\n'
            )
        else:
            out.write(
                f'    itemTable[{key}] = Item({item_type}, {get_id}, {item_class}, '
                f'{logic_ptr}, {hint}, {price}, Text{{{text_str}}});\n'
            )

    out.write(FOOTER)