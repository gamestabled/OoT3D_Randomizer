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

def format_categories(cat_list):
    cat_str = ", ".join(f"Category::{c}" for c in cat_list) + ","
    return cat_str[:-1] # remove trailing comma

def parse_entry(key, value):
    if len(value) < 4:
        raise ValueError(f"{key} is too short")

    loc_type = value[0]

    # Hints
    if loc_type == "HintStone" or loc_type == "OtherHint":
        scene = value[1]
        flag  = value[2]
        name     = value[3]

        return {
            "constructor": "Hint",
            "scene": scene,
            "flag": flag,
            "name": name
        }

    # GS Tokens
    if loc_type == "GSToken":
        scene = value[1]
        flag  = value[2]
        name     = value[3]
        hintKey  = value[4]
        vanillaItem = None
        categories = value[5]

        remaining = value[6:]

        check = None
        group = None

        for r in remaining:
            if isinstance(r, str) and ")" in r:
                check = r
            else:
                group = r

        return {
            "constructor": "Normal",
            "loc_type": loc_type,
            "scene": scene,
            "flag": flag,
            "name": name,
            "hintKey": hintKey,
            "vanillaItem": vanillaItem,
            "categories": categories,
            "check": check,
            "group": group
        }

    # Everything else
    if len(value) < 7:
        raise ValueError(f"{key} is missing required fields")

    scene = value[1]
    flag  = value[2]
    name     = value[3]
    hintKey  = value[4]
    vanillaItem = value[5]
    categories = value[6]

    remaining = value[7:]

    check = None
    group = None

    for r in remaining:
        if isinstance(r, str) and ")" in r:
            check = r
        else:
            group = r

    return {
        "constructor": "Normal",
        "loc_type": loc_type,
        "scene": scene,
        "flag": flag,
        "name": name,
        "hintKey": hintKey,
        "vanillaItem": vanillaItem,
        "categories": categories,
        "check": check,
        "group": group
    }


def generate_cpp_line(key, e):
    # Gosip stones have a different constructor
    if e["constructor"] == "Hint":
        return (
            f'locationTable[{key}] = ItemLocation::HintStone('
            f'{e["scene"]}, {e["flag"]}, "{e["name"]}", {{}});'
        )

    cat_str = format_categories(e["categories"])

    line = (
        f'locationTable[{key}] = ItemLocation::{e["loc_type"]}'
        f'({e["scene"]}, {e["flag"]}, "{e["name"]}", {e["hintKey"]}'
    )

    if e["vanillaItem"]:
        line += f', {e["vanillaItem"]}'
    
    line += f', {{{cat_str}}}'

    if e["check"]:
        line += f', SpoilerCollectionCheck::{e["check"]}'

    if e["group"]:
        line += f', SpoilerCollectionCheckGroup::{e["group"]}'

    line += ");"

    return line

################## MAIN ####################

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_location_table.cpp")
data = load_json_with_comments("data/location_table.jsonc")

with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER)

    for key, value in data.items():
        entry = parse_entry(key, value)
        out.write("    " + generate_cpp_line(key, entry) + "\n")

    out.write(FOOTER)