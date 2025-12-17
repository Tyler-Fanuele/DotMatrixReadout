# DotMatrixReadout

## set up board

I am using a 64x32 ada fruit led matrix with a raspi 3b and a ada fruit raspi matrix bonnet

## set up software

make sure you run the library installer in the lib directory.

if you want the clock to be persistant without internet, you will need a rtc clock. I used this tutorial https://pimylifeup.com/raspberry-pi-rtc/.

cmake . will build my code and also the rpi rgb led matrix library code if it is not built.

you will need to install libgraphicsmagick++-dev and libwebp-dev for the icon display.

I set the start.sh script to run on startup with systemd.

