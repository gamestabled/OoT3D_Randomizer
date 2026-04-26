from utils import load_json_with_comments
import os
import sys

HEADER = """// File generated automically. Do not edit. Edit settings_table.jsonc instead."
#include "settings.hpp"
#include "descriptions.hpp"
#include "../../code/src/enemy_souls.h"

using namespace Cosmetics;

// clang-format off
namespace Settings {
"""

all_options = []
categories = {}
definitions = {}  # Maps definition names to their vector definitions

def format_definition_value(token):
    if token == "$RANDOM_CHOICE":
        return 'std::string(Cosmetics::RANDOM_CHOICE_STR)'
    elif token == "$RANDOM_COLOR":
        return 'std::string(Cosmetics::RANDOM_COLOR_STR)'
    elif token == "$CUSTOM_COLOR":
        return 'std::string(Cosmetics::CUSTOM_COLOR_STR)'
    else:
        # Regular string literal
        return f'"{token}"'

def generate_option_decl(key, value):
    typ = value["type"]
    name = value["name"]
    descriptions = value.get("descriptions", [])
    def format_description_token(token):
        if token == "''":
            return '""'
        if isinstance(token, str) and token.startswith("'") and token.endswith("'"):
            return f'"{token[1:-1]}"'
        if token == "cosmeticDescriptions":
            return "cosmeticDescriptions"
        return token

    MACRO_VALUES = {
        "RAINBOW_TUNIC": 30,  # childTunicOptions.size() - 2 = 32 - 2
        "SAME_AS_KOKIRI": 31,  # childTunicOptions.size() - 1 = 32 - 1
        "RAINBOW_NAVI": 22,  # naviOuterOptionNames.size() - 2 = 24 - 2
        "SAME_AS_INNER_NAVI": 23,  # naviOuterOptionNames.size() - 1 = 24 - 1
        "RAINBOW_TRAIL": 14,  # weaponTrailOuterOptionNames.size() - 2 = 16 - 2
        "SAME_AS_INNER_TRAIL": 15,  # weaponTrailOuterOptionNames.size() - 1 = 16 - 1
    }

    if isinstance(descriptions, str):
        if descriptions == "''":
            descriptions_str = '{""}'
        elif descriptions == "cosmeticDescriptions":
            descriptions_str = '{cosmeticDescriptions}'
        else:
            descriptions_str = f"{{{descriptions}}}"
    else:
        descriptions_str = "{" + ", ".join(format_description_token(d) for d in descriptions) + "}"
    category_enum = "OptionCategory::" + value.get("category", "Setting")
    default = value.get("default", 0)
    if isinstance(default, bool):
        default = str(default).lower()
    elif isinstance(default, str) and default in MACRO_VALUES:
        # Replace macro references with numeric values
        default = MACRO_VALUES[default]
    hidden = value.get("default_hidden", False)
    indent = value.get("indent", 0)
    
    if typ == "Bool":
        falsetxt = value.get("falsetxt", "Off")
        truetxt = value.get("truetxt", "On")
        options = [falsetxt, truetxt]
        if isinstance(default, str):
            default = 1 if default == truetxt else 0
        return f'Option {key} = Option::Bool("{name}", {{"{falsetxt}","{truetxt}"}}, {descriptions_str}, {category_enum}, {default});'
    elif typ == "Choice":
        options = value["options"]
        if isinstance(options, str):
            # Check if this references a defined vector
            if options in definitions:
                options_str = options  # Use the variable name directly
            else:
                options_str = f"{options}"  # Keep as variable reference
        else:
            options_str = "{" + ", ".join(f'"{o}"' for o in options) + "}"
            if isinstance(default, str):
                default = options.index(default)
        return f'Option {key} = Option::U8("{name}", {options_str}, {descriptions_str}, {category_enum}, {default});'
    elif typ == "Count":
        minv = value["min"]
        maxv = value["max"]
        return f'Option {key} = Option::U8({indent}, "{name}", {{NumOpts({minv}, {maxv})}}, {descriptions_str}, {category_enum}, {default}, {str(hidden).lower()});'
    elif typ == "NumericChoice":
        minv = value["min"]
        maxv = value["max"]
        options = value["options"]
        num_opts = f'NumOpts({minv}, {maxv})'
        extra_opts = ", ".join(f'{{"{o}"}}' for o in options if o != "__num__")
        options_str = f'MultiVecOpts({{{num_opts}, {extra_opts}}})'
        return f'Option {key} = Option::U8("{name}", {{{options_str}}}, {descriptions_str});'
    elif typ == "LogicTrick":
        if "options" in value:
            options = value["options"]
            if isinstance(options, str):
                options_str = f"{options}"
            else:
                options_str = "{" + ", ".join(f'"{o}"' for o in options) + "}"
            return f'Option {key} = Option::U8("{name}", {options_str}, {descriptions_str}, {category_enum}, {default});'
        else:
            return f'Option {key} = LogicTrick("{name}", {descriptions_str});'
    elif typ == "GlitchDifficultyOptions":
        mask = value.get("GlitchDifficultyOptions")
        if mask is None:
            raise ValueError(f"Missing GlitchDifficultyOptions field for option {key}")
        options_str = f"GlitchDifficultyOptions({mask})"
        return f'Option {key} = Option::U8("{name}", {options_str}, {descriptions_str}, {category_enum}, {default});'

def process_category(name, data):
    options = []
    for key, value in data.items():
        if key.startswith('_'):
            # _definitions is a special case
            if key == '_definitions':
                continue
            sub_name = key[1:]
            sub_options = process_category(sub_name, value)
            categories[sub_name] = sub_options
            options.extend(sub_options)
        elif isinstance(value, dict) and "type" in value:
            # Option
            opt_decl = generate_option_decl(key, value)
            all_options.append(opt_decl)
            options.append(f"&{key}")
        elif isinstance(value, dict):
            # Child category
            child_options = process_category(key, value)
            categories[key] = child_options
            options.extend(child_options)
    categories[name] = options
    return options

################## MAIN ####################

output_dir = sys.argv[1] if len(sys.argv) > 1 else "source/generated/"
os.makedirs(output_dir, exist_ok=True)
out_path = os.path.join(output_dir, "generated_settings_table.cpp")
json_data = load_json_with_comments("data/settings_table.jsonc")

if "_definitions" in json_data:
    definitions = json_data["_definitions"]

# Process each category individually
for category, data in json_data.items():
    process_category(category, data)

# Write output file
with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER)
    
    # Vector definitions
    for def_name, def_values in definitions.items():
        elements = ", ".join(format_definition_value(v) for v in def_values)
        out.write(f'std::vector<std::string> {def_name} = {{{elements}}};\n')
    
    out.write("\n")
    
    # All Options
    for opt in all_options:
        out.write(opt + "\n")
    out.write("\n")

    # Enemy Souls Options
    soulsBlock = """// Initialize startingEnemySoulsOptions with one Option for each element in SoulMenuNames
std::vector<Option *> startingEnemySoulsOptions = mapArrayToOptions(SoulMenuNames, [](SoulMenuInfo info){
    return Option::U8 (info.name, {"Off", "On"}, {""});
});
"""
    out.write(soulsBlock + "\n")
    
    # Category vectors
    for cat, opts in categories.items():
        opts_str = ", ".join(opts)
        out.write(f"std::vector<Option *> {cat} = {{{opts_str}}};\n")
    out.write("}\n")
