# culturelab
Creations with kids for sounding images with ESP32 as touch sensors

Download complete package for starting ESP 32 programming. 

1. Install ble-final-3x.ino on your ESP32 Board (ESP32 Dev Module) and connect port. Open Serial monitor for checking.
2. In case you want to connect various boards, please change board-name in the ino-file, e.g. BLEDevice::init("ESP32-01"); and then also change it in the HTML-file accordingly, e.g. filters: [{ name: "ESP32-Wald-1" }] in the Java-Script part.

  In case of any difficulty, you can run various test-files: 
  
   - touch-test.ino tests touchability of your board
   - touch-3x-test.ino checks 3 pins: GPIO 27, 32 and 33
   - touch-3x-threshold.ino helps you setup the threshold and sensitivity of the pins. Change if necessary. Set a value clear beyond
     standard sending and clearly wide enough from touched value to trigger intelligently.
   - ble-text.ino checks and establishes connection via Bluetooth to website / repository. Please correct thresholds if necessary.

2. Change sample-files in "/sounds" and put your own sound-files into the folder. Check naming accordance in HTML and sound-files.

3. run website skript and connect ESP (in case of various boards, choose the right one!).

4. Touch the pins.

5. Have fun playing around with them! :-) 

