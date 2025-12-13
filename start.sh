#!/bin/bash

sudo ./display --led-rows=32 --led-cols=64 --led-gpio-mapping=adafruit-hat -f ./matrixLib/rpi-rgb-led-matrix/fonts/helvR12.bdf -C 100,100,100 -x 1 -O 100,0,0 -d '%a %D' -d '%H:%M:%S'