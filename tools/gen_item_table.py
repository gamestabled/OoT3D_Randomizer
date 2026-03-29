import json
import os
import sys

def load_json_with_comments(path):
    with open(path, encoding="utf-8") as f:
        lines = []
        for line in f:
            line = line.split("//")[0]
            if line.strip():
                lines.append(line)
        return json.loads("\n".join(lines))

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_item_table.cpp")
data = load_json_with_comments("data/item_table.jsonc")

with open(out_path, "w", encoding="utf-8") as out:
    out.write('// File generated automically. Do not edit. Edit item_table.jsonc instead."\n\n')
    out.write('#include "../item_list.hpp"\n')
    out.write('#include "../logic.hpp"\n\n')
    out.write("using namespace Logic;\n\n")
    out.write("// clang-format off\n")
    out.write("void ItemTable_Init() {\n")

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

    out.write("};\n")