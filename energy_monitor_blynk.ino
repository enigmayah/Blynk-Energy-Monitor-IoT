 #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27, 20, 4);
 #include "EmonLib.h"
 #include <EEPROM.h>
 #define BLYNK_PRINT Serial
 #define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
 #define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
 #define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
 #include <WiFi.h>
 #include <WiFiClient.h>
 #include <BlynkSimpleEsp32.h>
 EnergyMonitor emon;
 #define vCalibration 83.3
 #define currCalibration 0.50
 BlynkTimer timer;
 char auth[] = BLYNK_AUTH_TOKEN;

// Change the Values here
 char ssid[] = "YOUR_SSID_WIFI"; 
 char pass[] = "YOUR_PASS"; 


 float kWh = 0;
 unsigned long lastmillis = millis();
 void myTimerEvent()
 {
 emon.calcVI(20, 2000);
 kWh = kWh + emon.apparentPower * (millis()- lastmillis) / 3600000000.0;
 yield();
 Serial.print("Vrms: ");
 Serial.print(emon.Vrms, 2);
 Serial.print("V");
 EEPROM.put(0, emon.Vrms);
 delay(100);
 Serial.print("\tIrms: ");
Serial.print(emon.Irms, 4);
 Serial.print("A");
 EEPROM.put(4, emon.Irms);
 delay(100);
 Serial.print("\tPower: ");
 Serial.print(emon.apparentPower, 4);
 Serial.print("W");
 EEPROM.put(8, emon.apparentPower);
 delay(100);
 Serial.print("\tkWh: ");
 Serial.print(kWh, 5);
 Serial.println("kWh");
 EEPROM.put(12, kWh);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Vrms:");
 lcd.print(emon.Vrms, 2);
 lcd.print("V");
 lcd.setCursor(0, 1);
 lcd.print("Irms:");
 lcd.print(emon.Irms, 4);
 lcd.print("A");
 lcd.setCursor(0, 2);
 lcd.print("Power:");
 lcd.print(emon.apparentPower, 4);
 lcd.print("W");
 lcd.setCursor(0, 3);
 lcd.print("kWh:");
 lcd.print(kWh, 4);
 lcd.print("W");
 lastmillis = millis();
 Blynk.virtualWrite(V0, emon.Vrms);
 Blynk.virtualWrite(V1, emon.Irms);
 Blynk.virtualWrite(V2, emon.apparentPower);
 Blynk.virtualWrite(V4, kWh);
 }
 void setup()
 {
 Serial.begin(1200); // 115200, 1200
Serial.println("Starting up...");
 // Try WiFi connection first
 Serial.printf("Connecting to %s ", ssid);
 WiFi.begin(ssid, pass);
 int attempts = 0;
 while (WiFi.status() != WL_CONNECTED && attempts < 20) {
 delay(500);
 Serial.print(".");
 attempts++;
 }
 if(WiFi.status() == WL_CONNECTED) {
 Serial.println("\nWiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 // Only try to connect to Blynk after WiFi is connected
 Blynk.begin(auth, ssid, pass);
 } else {
 Serial.println("\nWiFi connection failed!");
 }
 // Blynk.begin(auth, ssid, pass);
 lcd.init();
 lcd.backlight();
 emon.voltage(35, vCalibration, 1.7); // Voltage: input pin, calibration,
 phase_shift
 emon.current(34, currCalibration);
 // Current: input pin, calibration.
 // Test LCD Display
 lcd.setCursor(0, 0);
 lcd.print("Welcome!!");
 delay(5000); // Wait 5 seconds to observe the display
 lcd.clear(); // Clear the display for the rest of the setup
 timer.setInterval(5000L, myTimerEvent);
 lcd.setCursor(3, 0);
 lcd.print("IoT Energy");
 lcd.setCursor(5, 1);
 lcd.print("Meter");
 delay(3000);
lcd.clear();
 }
 void loop()
 {
 Blynk.run();
 timer.run();
 }