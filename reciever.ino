/*  Program to pick up UDP multicast packet and print output to 16x2LCD over i2c
 *  uses a esp8266 (Wemos D1 mini).
 *  
 *  See Github for code to transmit packet.
 *  
 *  GND ----- > mcu GND
 *  VCC ----- > mcu 5v
 *  SDA ----- > mcu D2
 *  SCL ----- > mcu D1
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
   
// Set WiFi credentials
#define WIFI_SSID "Wi-FiSSIDhere"
#define WIFI_PASS "Wi-FiPasswordhere"
#define UDP_PORT 5669

LiquidCrystal_I2C lcd(0x27,16,2);

WiFiUDP UDP;
char packet[255];
   
void setup() {
  lcd.init();
  
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
   
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
   
  // Connecting to WiFi...
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Connecting To:");
  lcd.setCursor(0,1);
  lcd.print(WIFI_SSID);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.print("Connected");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  UDP.begin(UDP_PORT);
  delay(3000);
   
}
   
void loop() {
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Rec. Packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.println(packet);
    String temp = String(packet[0]) + String(packet[1] + String(packet[2]) + String(packet[3]) + String(packet[4]) + " c");
    Serial.println(temp);
    String pressure = String(packet[5]) + String(packet[6]) + String(packet[7]) + String(packet[8]) + " hPa";
    Serial.println (pressure);
    String humidity = String(packet[9]) + String(packet[10]) + String(packet[11]) + String(packet[12]) + String(packet[13]) + "%";
    Serial.println (humidity);
    lcd.clear();
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print(temp);
    delay(5000);
    lcd.clear();
    lcd.print("Pressure:");
    lcd.setCursor(0,1);
    lcd.print(pressure);
    delay(5000);
    lcd.clear();
    lcd.print("Humidity:");
    lcd.setCursor(0,1);
    lcd.print(humidity);
    delay(5000);
  }
  else {
    lcd.clear();
    lcd.print("Error with Pkt");
    delay(5000);
  }
   
}
