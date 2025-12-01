# arduinor4wifi
Arduino UNO R4 WiFi + ESP32-S3 | Real-Time Message &amp; Emoji Display
# WiFi-Controlled LED Matrix Display (Arduino UNO R4 WiFi) 🚀

![Project Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Platform-Arduino_UNO_R4-blue)
![Connectivity](https://img.shields.io/badge/Connectivity-WiFi%20%7C%20ESP32--S3-green)

## 📜 Project Overview
[cite_start]This project implements an interactive **WiFi-controlled message and emoji display system** using the **Arduino UNO R4 WiFi**[cite: 21]. [cite_start]By leveraging the board's dual-chip architecture (Renesas RA4M1 + ESP32-S3), the system allows users to wirelessly send scrolling text and animations to the LED matrix via a smartphone browser[cite: 22].

[cite_start]It operates without an internet connection by hosting its own local Access Point (AP), making it perfect for educational demonstrations, IoT learning, and portable signage[cite: 23].

---

## ✨ Features
* [cite_start]**Web-Based Control:** Host a local web server to control the display from any phone or PC[cite: 66].
* [cite_start]**Real-Time Messaging:** Send text updates instantly to the LED matrix[cite: 64].
* [cite_start]**Emoji Support:** Display animated emojis like Happy, Cry, and Heart loops[cite: 103].
* [cite_start]**Adjustable Speed:** Control the text scrolling speed via a slider on the web interface[cite: 106].
* [cite_start]**Standalone Operation:** Works via the ESP32-S3 Access Point mode (No router required)[cite: 61].

---

## 🛠️ Hardware Architecture
The system utilizes the unique "2-in-1" architecture of the Arduino UNO R4 WiFi:

1.  **Main Processor (Renesas RA4M1):**
    * [cite_start]Arm Cortex-M4 running at 48 MHz[cite: 59].
    * Handles the display logic, matrix rendering, and animation loops.
2.  **Wireless Module (ESP32-S3):**
    * [cite_start]Dual-core, 240 MHz WiFi & Bluetooth module[cite: 90].
    * [cite_start]Operates in Access Point (AP) mode to host the web interface[cite: 61].
    * [cite_start]Communicates with the RA4M1 via the onboard logic level shifter (TXB0108DQSR)[cite: 92].
3.  **Display:**
    * [cite_start]Onboard 12x8 LED Matrix (or external 8x32 matrix via GPIO)[cite: 64].

---

## 💻 Software & Libraries
[cite_start]To run this project, you need the **Arduino IDE** and the following libraries[cite: 98]:

* **`WiFiS3`**: For configuring the ESP32-S3 AP and server.
* **`ArduinoGraphics`**: For bitmap rendering.
* **`Arduino_LED_Matrix`**: For controlling the R4's onboard matrix.

---

## 🚀 Getting Started

### 1. Installation
1.  Clone this repository.
2.  Open the `.ino` file in Arduino IDE.
3.  Install the required libraries via the Library Manager.
4.  Select **Arduino UNO R4 WiFi** as your board.
5.  Upload the code.

### 2. Usage
1.  Power on the Arduino UNO R4 WiFi.
2.  On your phone/laptop, search for WiFi networks.
3.  [cite_start]Connect to the SSID: **`UNO_Matrix`**[cite: 66].
4.  Open a web browser and navigate to:
    ```
    [http://192.168.4.1](http://192.168.4.1)
    ```
    [cite_start]*[cite: 121]*
5.  Use the interface to:
    * Type a message and click **Send**.
    * Click emoji buttons to trigger animations.
    * Adjust the slider to change scroll speed.

---

## 📊 System Flow
1.  **Initialization:** RA4M1 initializes the Matrix; [cite_start]ESP32-S3 starts the Access Point[cite: 67, 68].
2.  [cite_start]**Connection:** User connects to WiFi and requests the web page[cite: 74].
3.  [cite_start]**Input Parsing:** The web server parses GET requests (Message, Speed, Emoji)[cite: 100].
4.  [cite_start]**Display Update:** Data is sent to the RA4M1, which updates the LED Matrix in a non-blocking loop[cite: 101, 138].

---

## 📷 Gallery
*Visuals of the Web Interface and Hardware setup.*

| [cite_start]Web Interface [cite: 122] | [cite_start]Hardware Output [cite: 147] |
|:---:|:---:|
| <img src="path_to_screenshot_of_phone_ui.jpg" width="250"> | <img src="path_to_photo_of_board.jpg" width="250"> |

---

## 🔮 Future Scope
* [cite_start]**Cloud Integration:** Remote updates via IoT cloud platforms[cite: 169].
* [cite_start]**Custom Animations:** Library expansion for more complex emojis[cite: 170].
* [cite_start]**Security:** Adding password authentication to the Web Interface[cite: 171].

---

---

## 📄 License
This project is open-source. Feel free to use and modify!
