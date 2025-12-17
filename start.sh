#!/bin/bash

sudo ./build/display --led-rows=32 --led-cols=64 --led-gpio-mapping=adafruit-hat -C 200,0,0 -B 0,0,10 -x 1 -s 5 -d '%I:%M %P' -d '%a %D' 