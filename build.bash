#!/bin/bash

echo "Building ESP8266 ... "
arduino-cli compile --config-file ./scripts/arduino-cli.esp8266.yaml --fqbn esp8266:esp8266:generic ./src/core/core.ino

echo "Building RP2040 ... "
arduino-cli compile --config-file ./scripts/arduino-cli.rp2040.yaml --fqbn rp2040:rp2040:waveshare_rp2040_lcd_1_28 ./src/ui/ui.ino