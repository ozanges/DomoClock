#!/bin/bash

cd ./scripts/

echo "Check style ESP8266 ... "
python3 code-format.py "/../src/core/*.c,*.h,*.ino"

echo "Check style RP2040 ... "
python3 code-format.py "/../src/ui/*.c,*.h,*.ino"