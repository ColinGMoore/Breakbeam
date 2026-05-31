/*
Code for recording time of infra red breakbeam hits taking
time from DS3231 RTC module and sending to 16 x 2 line display,
a file on micro SD card module (called "switch.txt") and to 
the Arduino IDE serial monitor.  Hits also sound a passive
buzzer.  LCD and RTC on I2C bus at addresses 0x27 and 0x68
respectively.  SD card module on SPI bus with CS on pin D4
and MOSI, MISO and SCK on pins 11, 12 and 13 respectively.
*/

#include "Arduino.h"
#include <SPI.h>
#include "uRTCLib.h"
#include <Wire.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const int chipSelect = 4;
int status = 0;
int oldstatus = 0;
int inputpin = 8;
int buzpin = 7;
File myfile;
uRTCLib rtc(0x68);

int $year;
int $month;
int $day;
int $hour;
int $minute;
int $second;

void setup() {
  Serial.begin(9600);
  delay(3000);  // wait for console opening
  pinMode(inputpin, INPUT);
  pinMode(buzpin, OUTPUT);
  URTCLIB_WIRE.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true)
      ;
  }

}

void loop() {
  rtc.refresh();

  oldstatus = status;
  status = digitalRead(inputpin);

  if (status == 1) {
    if (status > oldstatus) {

      Serial.print("20");
      Serial.print(rtc.year());
      Serial.print('-');
      if (rtc.month() < 10) {
        Serial.print("0");
        Serial.print(rtc.month());
      } else {
        Serial.print(rtc.month());
      }
      Serial.print('-');
      if (rtc.day() < 10) {
        Serial.print("0");
        Serial.print(rtc.day());
      } else {
        Serial.print(rtc.day());
      }
      Serial.print(" ");
      if (rtc.hour() < 10) {
        Serial.print("0");
        Serial.print(rtc.hour());
      } else {
        Serial.print(rtc.hour());
      }
      Serial.print(':');
      if (rtc.minute() < 10) {
        Serial.print("0");
        Serial.print(rtc.minute());
      } else {
        Serial.print(rtc.minute());
      }
      Serial.print(':');
      if (rtc.second() < 10) {
        Serial.print("0");
        Serial.println(rtc.second());
      } else {
        Serial.println(rtc.second());
      }

      $year = rtc.year();
      $month = rtc.month();
      $day = rtc.day();
      $hour = rtc.hour();
      $minute = rtc.minute();
      $second = rtc.second();


      //PRINT CURRENT TIME to file
      myfile = SD.open("switch.txt", FILE_WRITE);
      // if the file opened okay, write to it:
      if (myfile) {
        myfile.print("20");
        myfile.print($year);
        myfile.print('-');
        if ($month < 10) {
          myfile.print("0");
          myfile.print($month);
        } else {
          myfile.print($month);
        }
        myfile.print('-');
        
        if ($day < 10) {
          myfile.print("0");
          myfile.print($day);
        } else {
          myfile.print($day);
        }
        
        myfile.print(" ");
        lcd.clear();
        if ($hour < 10) {
          myfile.print("0");
          lcd.print("0");
          myfile.print($hour);
          lcd.print($hour);
        } else {
          myfile.print($hour);
          lcd.print($hour);
        }

        myfile.print(':');
        lcd.print(':');

        if ($minute < 10) {
          myfile.print("0");
          lcd.print("0");
          myfile.print($minute);
          lcd.print($minute);
        } else {
          myfile.print($minute);
          lcd.print($minute);
        }

        myfile.print(':');
        lcd.print(':');

        if ($second < 10) {
          myfile.print("0");
          lcd.print("0");
          myfile.print($second);
          lcd.print($second);
        } else {
          myfile.print($second);
          lcd.print($second);
        }
        
        tone(7, 1000, 500);
        delay(500);

        myfile.print("\n");


        myfile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening switch.txt");
      }

      delay(500);
    }
    
  }
}
