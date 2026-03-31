import json
import os
import sys

HEADER = """// File generated automically. Do not edit. Edit location_table.jsonc instead."
#include "../item_location.hpp"

// clang-format off
void LocationTable_Init() {
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

################## MAIN ####################

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_location_table.cpp")
data = load_json_with_comments("data/location_table.jsonc")

with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER)

    for key, line_data in data.items():
        location_type = line_data.get("type", "Base")
        scene = line_data.get("scene", "0xFF")
        flag = line_data.get("flag", "0xFF")
        name = line_data.get("name", "Invalid Location")
        hint_key = line_data.get("HintKey", None)
        vanilla_item = line_data.get("vanillaItem", None)
        categories = line_data.get("categories", [])
        check = line_data.get("SpoilerCollectionCheck", None)
        group = line_data.get("SpoilerCollectionCheckGroup", None)

        cat_str = ', '.join(f"Category::{t}" for t in categories)

        line = (
            f'locationTable[{key}] = ItemLocation::{location_type}'
            f'({scene}, {flag}, "{name}", '
        )

        if hint_key:
            line += f'{hint_key}, '

        if vanilla_item:
            line += f'{vanilla_item}, '
        
        line += f'{{{cat_str}}}'

        if check:
            line += f', SpoilerCollectionCheck::{check}'
        
        if group:
            line += f', SpoilerCollectionCheckGroup::{group}'
        
        out.write(f"    {line});\n")

    out.write(FOOTER)