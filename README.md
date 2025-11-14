
# **Women Safety Device Using GSM, GPS & Heart Rate Monitoring**

This project is an **IoT-based Women Safety Device** built using an Arduino microcontroller, GSM module, GPS module, and heartbeat sensor. The system provides **real-time location tracking**, **emergency alerts**, and **health monitoring** to ensure the safety of women in critical situations.

---

## **📌 Project Overview**

The Women Safety Device provides emergency support by detecting distress signals such as:

* Panic button press
* Abnormal heart rate (too high or too low)
* Manual emergency activation

When triggered, the device:

1. **Obtains real-time GPS coordinates**
2. **Sends an SMS alert** to a predefined mobile number using a GSM module
3. **Displays status** on the LCD screen
4. **Activates a buzzer** as an immediate local alert

This project integrates **health monitoring + personal safety + IoT technologies** in one compact system.

---

## **✨ Features**

### 🔹 **1. Panic Button Alert**

A single press on the panic button immediately triggers:

* Buzzer beep
* Emergency SMS
* Location sharing

### 🔹 **2. Heartbeat Monitoring**

The heartbeat sensor continuously monitors BPM:

* **Normal Range:** 40 – 120 BPM
* If BPM is beyond limits → SMS alert is sent
* LCD displays “Abnormal BPM”

### 🔹 **3. Real-Time GPS Tracking**

* Fetches live latitude and longitude
* Includes location link in SMS
* Automatically handles GPS signal loss

### 🔹 **4. GSM Messaging System**

Automatically sends emergency SMS like:

* “Panic Button Activated!”
* “Abnormal Heartbeat Detected!”
  With real-time location.

### 🔹 **5. LCD Status Display**

Shows:

* Heart rate
* System status
* GSM status
* Alerts

---

## **🧰 Hardware Components Used**

| Component                            | Description                 |
| ------------------------------------ | --------------------------- |
| **Arduino Uno/Nano**                 | Main controller             |
| **SIM800L/SIM900 GSM module**        | Sends SMS alerts            |
| **Neo-6M GPS Module**                | Real-time location tracking |
| **Heart Rate Sensor (Pulse Sensor)** | Measures BPM                |
| **16x2 LCD Display**                 | Shows status information    |
| **Panic Button**                     | Emergency trigger           |
| **Buzzer**                           | Alert tone                  |
| **Connecting wires**                 | Internal connections        |

---

## **🧩 Working Principle**

1. **Power ON** → Device initializes GSM, GPS, LCD
2. **Continuous Monitoring**

   * Heart rate is read from analog pin
   * BPM is mapped and displayed
3. **GPS Updates**

   * Reads longitude & latitude
4. **Emergency Trigger**

   * Button press OR abnormal heart rate
   * Buzzer activates
   * SMS is sent with alert message and location
5. **System Resumes Monitoring**

---

## **📡 SMS Format Example**

```
Panic Button Activated! My location: 
Lat: 17.406500, Long: 78.477200
```

Or:

```
Abnormal Heartbeat Detected! BPM: 150
Lat: 17.406500, Long: 78.477200
```

---

## **🧾 Code Functionality Summary**

* **sendEmergencyMessage()**
  Sends SMS with custom alert + GPS coordinates.

* **getGPSLocation()**
  Reads NMEA data and extracts latitude/longitude.

* **waitForResponse()**
  Waits for GSM module acknowledgments.

* **Heartbeat Monitoring**
  Converts analog reading → BPM and detects abnormalities.

---

## **📑 Use Cases**

✔ Women safety
✔ Children tracking
✔ Elderly health + safety monitoring
✔ Heart patient emergency alerts
✔ Personal security for night workers

---

## **🛠 How to Upload and Run**

1. Install Arduino IDE
2. Add TinyGPS++ library
3. Select correct Arduino board
4. Upload code
5. Insert SIM (SMS pack recommended)
6. Power using 9V/12V adapter or battery

---

## **📷 Future Improvements**

* Add **IoT cloud dashboard** (Firebase or Thingspeak)
* Add **fall detection (accelerometer)**
* Add **SOS call feature**
* Add **rechargeable Li-Ion battery + charging circuit**
* Add **mobile app integration**

---

