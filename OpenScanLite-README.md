# OpenScan-Lite
An ESP32-based branch of the OpenScan project.  

---

## Overview  
OpenScan-Lite is a simpler, cheaper version of OpenScan Classic with fewer features. Automates the posing and photographing of the object

### MENU:
left, right, and select buttons; left right changes the current focused section, and the select button will rotate through the current setting's options
  - START: Starts the scanning process using the current settings (if nothing changed, using the presets)
  - Layers: How many extra rotations (at different angles) the scanners will do of the object (default 2: so apart from the 0* tilt, it will do 2 more)
  - Tilt Angle: How may degrees the stand will tilt the object after each full rotation (default 30: so after the first rotation, the stand will tilt by 30*, after the second another 30*, etc)
  - P360: The ammount of pictures taken/ full object rotation (default 60: so one picture every 6* of rotation)
  - Spiral: Tries to offset the pictures on different "layers", to try and have more overlap between more pictures (experimental) (default: N)
  - Shrinking: Decreseases the ammount of pictures/ full rotation, as a percentage, to try and reduce the ammount of pictures necesary for a scan (experimental) (default 10%, so for P:360, and Tilt 30*, the pictures will be 60 for the first layer, 54 for the second and 49 for the last) 

---

## Features 
Controlled via 3 buttons and a oled display. Allows for some basic presets and customisation:
Designed for affordability and DIY customization.

---

### Hardware:  
1. **2 stepper motors**  
2. **2 stepper motor drivers DRV8825**  
3. **1 ESP32 WEMOS LOIN32 board** (if using a different esp32 break-out you might need to change the wiring a bit)  
4. **2 100uf capacitors** *(optional but highly recommended)*
5. **4 buttons** (3 for navigating the menu, one optional for manual stepper dissengaging)
6. **1 0.96 I2C Oled (the one with 4) (128x32 was used but other sizez can be used as well, with little or no changes necesary)**  
7. **12V 5A Power Supply Unit (PSU)**  
   - A weaker PSU might work, but it is not recommended.

---

## How to Build 

### 1. **Download and 3D-Print the Structure**  
You’ll need only the structural files from the OpenScan Classic project.  
Get the files from this link:  
[OpenScan Classic Files](https://github.com/OpenScan-org/OpenScan-Design/tree/main/files/Classic/V1).  

Required parts:  
- **Adapter1**  
- **Adapter2 gear large**  
- **Gear Small** *(2 versions available; try both to see which works best)*  
- **Rotary arm**  
- **Stand1** and **Stand2**  
- Any required turntable attachments.  

**Skip any files related to Raspberry Pi.**

---

### 2. **Build the Circuit**  
Follow the guide here for adjusting drivers AND IF YOU ARE USING A DIFFERENT DRIVER OTHER THAN DRV8825:  
[Stepper Motors and Arduino Guide](https://howtomechatronics.com/tutorials/arduino/stepper-motors-and-arduino-the-ultimate-guide/).  


The code assumes both stepper motors are set to **1/16 microstepping mode**.  
If you wire them differently, update the code accordingly.  
Refer to the tutorial above for guidance on using stepper motors with drivers and setting the microstepping mode.
The 4rth button is used to dissengage the steppers so the stand and object can be positioned manually.

![image](https://github.com/user-attachments/assets/c86b2f25-340e-4a2b-93e3-5f4c3b4e1717)

this is the general wiring, 2 gnds are used one for logic GND (the esp32's gnd, and the other GND is from the PSU)
pin16 is left, pint 17 is right, and pin 25 is select, all should be wired to logic gnd, and to those pins 

if you plan to use other pins, make sure the pins support input/ouput (most do, unless specified otherwise)


---

### 3. **Software**

Copy the code into your arduino IDE, and install these libraries from the library manager: 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

the keyboard.h one you can get from: https://github.com/T-vK/ESP32-BLE-Keyboard
import this into your project, if you get errors from this library, make usre its installed, and then you might need to downgrade some things; these worked for me: 
![image](https://github.com/user-attachments/assets/b7554db4-3ac2-4f6f-9f7d-75cd9dc39868)

---

### 4. **Optional: Build a Phone Stand**  
If using a smartphone, ensure it remains steady for around 3-4 minutes.  
- Use a phone stand like this:  
  [Thingiverse Phone Stand](https://www.thingiverse.com/thing:3363730).  
- Alternatively, build any stand you find suitable.  

---

## IMAGE - MODEL Software

After capturing the pictures, save them on your phone or computer.  
Here are some options for processing your scanned images:  

1. **[OpenScanCloud](https://www.openscancloud.com/):**  
   - Best results with minimal effort.  

2. **[Meshroom](https://alicevision.org/#meshroom):**  
   - Great for advanced users who want more control over the process.  

3. **[ColMap](https://colmap.github.io/):**  
   - Another powerful option worth trying.  
---

## CUSTOMISING VARIABLES:

#define BUTTON_LEFT 16
#define BUTTON_RIGHT 17
#define BUTTON_SEL 25

// Driver config
const int table_dirPin = 23;
const int table_stepPin = 12; // for tilting (big "table")
const int stand_dirPin = 27;
const int stand_stepPin = 14; // for rotation (small "stand")

// Timings
const int step_delay_us = 350; // how fast the steppers rotate
const int pose_delay_ms = 750; // delay between poses and photos (If camera focuses fast, decrease, if slow, increase)

const int steps_per_revolution = 200 * 16; // using 1/16 microstepping
const float ratio = 5.33333; // gear ratio between the stepper spock and the big arm spock

//if (bleKeyboard.isConnected()) bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
change KEY_MEDIA_VOLUME_UP with any other key (from the keyboard.h library), if you think it might work better

Default settings:
  uint8_t tilt_changes = 2;    // Number of layers (0,1,2,3)
  uint8_t tilt_angle = 30;     // Layer angle increment (20,30,40 degrees)
  uint8_t p360 = 60;           // Pictures per full rotation (40,50,60,80)
  bool spiral = false;         // Spiral mode
  uint8_t shrink = 10;         // Layer shrink percentage
  


Happy scanning with OpenScan-LITE! 🚀
And If you can, please support the original project.
