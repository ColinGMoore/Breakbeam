# Breakbeam
Arduino C++ code to manage data storage from breakbeam sensor
/*
Code for recording time of infra red breakbeam hits taking
time from DS3231 RTC module and sending to 16 x 2 line display,
a file on micro SD card module (called "switch.txt") and to 
the Arduino IDE serial monitor.  Hits also sound a passive
buzzer.  LCD and RTC on I2C bus at addresses 0x27 and 0x68
respectively.  SD card module on SPI bus with CS on pin D4
and MOSI, MISO and SCK on pins 11, 12 and 13 respectively.

Code written for Arduino Uno and tested successfully on Uno 
R4 wifi.
*/
