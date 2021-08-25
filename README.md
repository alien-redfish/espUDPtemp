# espUDPtemp

BME688 sensor attached to an esp8266 (NodeMCU), creates a UDP multicast packet and broadcasts this over the network.
Receiver takes UDP packet, parses it and displays on a 16x2 LCD.

# Sender

Board: Nodemcu esp8266

Wiring:

BME688 ----> NodeMCU

2-6v -----> 3v

GND  -----> G

SDA  -----> D2

DCL  -----> D1

Don't forget to change the WiFi SSID and Password in the code.
The packet is a string consisting of temperature,pressure,humidity. Temp is four characters long, pressure is the next four and humidity the next five.

# Receiver

Board: Wemos D1 Mini

Wiring:

D1 Mini -----> 16x2 i2c LCD

VCC  ----->  5v

GND  ----->  GCC

SDA  ----->  D2

SCL  ----->  D1

Don't forget to change the WiFi SSID and Password in the code.
