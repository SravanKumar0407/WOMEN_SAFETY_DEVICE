#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS++.h>

// Pin Definitions
#define GPS_RX 8
#define GPS_TX 9
#define GSM_TX 11
#define GSM_RX 12
#define PANIC_BUTTON 10
#define BUZZER 13
#define HEARTBEAT_SENSOR A0  // Analog pin for heartbeat sensor

// LCD Connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
SoftwareSerial gsmSerial(GSM_RX, GSM_TX);

TinyGPSPlus gps;

const int heartRateThreshold = 120;
const int lowHeartRateThreshold = 40;

void setup() {
    pinMode(PANIC_BUTTON, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);
    pinMode(HEARTBEAT_SENSOR, INPUT);

    Serial.begin(9600); // For Debugging
    gpsSerial.begin(9600);
    gsmSerial.begin(9600);

    lcd.begin(16, 2);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Women Safety Device");
    delay(2000);
    lcd.clear();

    // GSM Initialization Check
    gsmSerial.println("AT");
    waitForResponse("OK");

    lcd.setCursor(0, 0);
    lcd.print("GSM Ready!");
    delay(2000);
}

void loop() {
    if (digitalRead(PANIC_BUTTON) == LOW) {
        delay(200); // Improved debounce delay
        if (digitalRead(PANIC_BUTTON) == LOW) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Emergency Alert!");
            digitalWrite(BUZZER, HIGH);
            delay(1000);
            digitalWrite(BUZZER, LOW);
            sendEmergencyMessage("Panic Button Activated!");
            delay(5000);
        }
    }

    int heartbeat = analogRead(HEARTBEAT_SENSOR);
    int bpm = map(heartbeat, 0, 1023, 0, 200);

    lcd.setCursor(0, 0);
    lcd.print("Heart Rate: " + String(bpm) + " bpm ");

    if (bpm > heartRateThreshold || bpm < lowHeartRateThreshold) {
        lcd.setCursor(0, 1);
        lcd.print("Abnormal BPM!");
        sendEmergencyMessage("Abnormal Heartbeat Detected! BPM: " + String(bpm));
        delay(5000);
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Status: Normal     ");
    }

    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());
    }

    delay(1000);
}

void sendEmergencyMessage(String alertMessage) {
    String location = getGPSLocation();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending SMS...");

    gsmSerial.println("AT+CMGF=1");
    waitForResponse("OK");

    gsmSerial.println("AT+CMGS=\"+918187060522\"");
    waitForResponse(">");

    gsmSerial.print(alertMessage + " My location: " + location);
    gsmSerial.write(26);
    waitForResponse("OK");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMS Sent");
    delay(2000);
}

String getGPSLocation() {
    unsigned long timeout = millis() + 5000;  // 5-second timeout
    while (millis() < timeout) {
        while (gpsSerial.available()) {
            gps.encode(gpsSerial.read());
            if (gps.location.isValid()) {
                String lat = String(gps.location.lat(), 6);
                String lng = String(gps.location.lng(), 6);
                return "Lat: " + lat + ", Long: " + lng;
            }
        }
    }
    return "GPS Signal Lost";
}

void waitForResponse(String expected) {
    long timeout = millis() + 5000;
    while (millis() < timeout) {
        if (gsmSerial.available()) {
            String response = gsmSerial.readString();
            if (response.indexOf(expected) != -1) {
                return;
            }
        }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GSM Error! Retry");
    
    delay(2000);
}
