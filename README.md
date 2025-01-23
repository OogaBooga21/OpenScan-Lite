# OpenScan-Lite  
An Arduino-based branch of the OpenScan project.  

---

## Overview  
OpenScan-Lite is a simpler, cheaper version of OpenScan Classic with fewer features.  
Its primary purpose is to program and pose the object you are scanning.  

### Key Points:  
- **It does NOT program picture-taking** (you'll need to handle this separately) (Some Options given bellow).  
- Functions as a glorified stand to automate scanning movements.  

---

## Features  
- Controlled via the Serial Monitor: (in the arduino IDE)
  - Press **1** to start scanning.  
  - Press **2** to stop scanning.  
- Designed for affordability and DIY customization.  

---

## What You Need  

### Hardware:  
1. **2 stepper motors**  
2. **2 stepper motor drivers**  
3. **1 Arduino board**  
4. **1 capacitor** *(optional but highly recommended)*  
5. **12V 5A Power Supply Unit (PSU)**  
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
Follow the wiring instructions provided in the Arduino code and use this tutorial as a reference:  
[Stepper Motors and Arduino Guide](https://howtomechatronics.com/tutorials/arduino/stepper-motors-and-arduino-the-ultimate-guide/).  

#### Wiring Overview:  
- **Table Stepper:**  
  - Pin **2** → Direction  
  - Pin **3** → Step  

- **Stand Stepper:**  
  - Pin **9** → Direction  
  - Pin **10** → Step  

The code assumes both stepper motors are set to **1/16 microstepping mode**.  
If you wire them differently, update the code accordingly.  
Refer to the tutorial above for guidance on using stepper motors with drivers and setting the microstepping mode.  
![image](https://github.com/user-attachments/assets/e0ef6379-25c7-4145-a01e-29a77cb11d9f)
should look somethign like this

---

### 3. **Install a OpenCamera App (Optional)**  
If using a programmable camera, you can skip this step. Otherwise:  
- Download the OpenCamera app on your phone.
- This app can be programmed to take photos at specific intervals.  
- The default code changes positions every **3 seconds**, so configure OpenCamera accordingly.  

---

### 4. **Optional: Build a Phone Stand**  
If using a smartphone, ensure it remains steady for around 10 minutes.  
- Use a phone stand like this:  
  [Thingiverse Phone Stand](https://www.thingiverse.com/thing:3363730).  
- Alternatively, build any stand you find suitable.  

---

## Software  

After capturing the pictures, save them on your phone or computer.  
Here are some options for processing your scanned images:  

1. **[OpenScanCloud](https://www.openscancloud.com/):**  
   - Best results with minimal effort.  

2. **[Meshroom](https://alicevision.org/#meshroom):**  
   - Great for advanced users who want more control over the process.  

3. **[ColMap](https://colmap.github.io/):**  
   - Another powerful option worth trying.  

---

## Customization Ideas  

This implementation is intentionally barebones, so feel free to experiment and enhance it:  
- Replace the **OpenCamera app** with a Bluetooth module and trigger the phone using an app like **Dabble**.  
- Upgrade the Arduino to an HID-capable device for more advanced features.  

---

Happy scanning with OpenScan-Lite! 🚀
And If you can, please support the original project.
