# OpenScan-Lite
An arduino-based branch of the OpenScan project

# Why?/ What can it do?/ How to use?/What you need
A simpler, cheaper version of OpenScan Classic, but with less feature 
This is basically a glorified stand, it will only program and pose the object you are trying to scan, it will NOT program the picture-taking
Simply download the code, and run it, It's controlled via the serial monitor; 1 to start scanning, 2 to stop 
2 steppers, 2 drivers, 1 arduino, 1 capacitor(optional but very much recommended), 12V 5A PSU(might work with a weaker one, but wont recommend it)


# How to build: 
1) Download and 3D-print the OpenScan Classic files 
you wont need all the files, only the ones that compose the structure of the stand, so: 
https://github.com/OpenScan-org/OpenScan-Design/tree/main/files/Classic/V1
from here:
Adapter1
Adapter2 gear large
Gear Small (2 worked for me, but worth trying both)
Skip all pi-realted items
Rotary arm
Stand1 and Stand2
And all the turntable attatchments you need

2) Build the circuit: 
Follow the wiring from the arduio code, and this tutorial: 
https://howtomechatronics.com/tutorials/arduino/stepper-motors-and-arduino-the-ultimate-guide/
a)for the table stepper:
    i)pin2 -direction
    ii)pin3 -step
b)for the stand stepper:
    i)pin9 -direction
    ii)pin10 -step

the code assumes both steppers are in 1/16 microstepping mode, so if you wire it differently, change the code
follow the guide provided above to see how to use the steppers with drivers and how to set them in microstepping mode.

3) Download the OpenCamera app (optional if you use a camera that you can program)
This option is decent since it keeps the image's exifdata. And can be programmed to take a selected number of photos at a given interval (which is what we need, since the code currently changes positions every 3 seconds)

4) Optional if not using phone, or using some other stand:
You will need to keep your phone steady, so I suggest you build any phone stand you deem fit for holding your phone still for roughly 10 minutes; a great example could be this: 
https://www.thingiverse.com/thing:3363730

# Software:
The pictures will be saved in your phone, from here, there are many options.
I got the best results from OpenScanCloud but I got some decent results also by using Meshroom, and ColMap, worth giving a try.

# Extras
This is a very barebones implementation, so feel free to add anything you like on it: 
maybe instead of using the OpenCamera app, use a bluetooth module and trigger the phne through an app like dabble
or replace the arduino for a HID capable device.
