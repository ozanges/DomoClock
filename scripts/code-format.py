#!/usr/bin/env python3

import os
import sys

script_dir = os.path.realpath(__file__)
script_dir = os.path.dirname(script_dir)
cfg_file = os.path.join(script_dir, 'code-format.cfg')

# print("\nFormatting demos")
# os.system(f'astyle --options={cfg_file} --recursive "{script_dir}/../demos/*.c,*.h"')

# print("\nFormatting examples")
# os.system(f'astyle --options={cfg_file} --recursive "{script_dir}/../examples/*.c,*.h"')

print("Formatting ui src")
os.system(f'astyle --options={cfg_file} --recursive "{script_dir}{sys.argv[1]}"')

# print("\nFormatting tests")
# os.system(f'astyle --options={cfg_file} --recursive "{script_dir}/../tests/*.c,*.h"')