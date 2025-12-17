#!/bin/bash

cd /home/tfanuele/DotMatrixReadout

sudo ./build/display --led-rows=32 --led-cols=64 --led-gpio-mapping=adafruit-hat-pwm --led-slowdown-gpio=3 -C 180,0,0 -B 0,0,0 -F 7x14B.bdf -f tom-thumb.bdf -s 11  -d '%I:%M %p' -d '%a %D' 