import os
import subprocess
from pathlib import Path

scripts_to_run = [
    "gen_description_table.py",
    "gen_item_table.py",
    "gen_location_table.py",
    "gen_settings_table.py",
]

for script in scripts_to_run:
    script_path = os.path.join(Path(__file__).resolve().parent, script)
    subprocess.run(["python3", script_path, os.path.join("source", "generated")])