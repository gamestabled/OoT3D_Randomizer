from utils import load_json_with_comments
import os
import sys

HEADER = """// File generated automically. Do not edit. Edit description_table.jsonc instead."
#include "descriptions.hpp"

// clang-format off
"""

################## MAIN ####################

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_description_table.cpp")
data = load_json_with_comments("data/description_table.jsonc")

with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER)

    for option, description in data.items():
        all_strings = [s.replace('"', r'\"') for s in description]
        line = None
        if option == "GlitchDifficulties":
            line = ('const std::vector<string_view> GlitchDifficulties{' + 
                    ', '.join(f'"{s}"' for s in all_strings) + '};')
        else:
            line = (
                f'string_view {option} = "' +
                '\\n'.join(all_strings) + '";')
        line += "\n"
        out.write(line)