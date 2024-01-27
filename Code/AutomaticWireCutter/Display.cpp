/*
 * Display.cpp - Library for displaying a custom menu for Automatic_Wire_Cutter on Liquid Crystal 16x2.
 * Specifically designed for "Automatic Wire Cutter" project only.
 * 
 * Created by FurbulousFox, January 14, 2024.
 */

 #include "Arduino.h"
 #include "Display.h"

 static boolean Display::cursorON=false;
 static int8_t Display::curYCoord=0;
 static LiquidCrystal_I2C Display::_lcd(0x27, 16, 2);
 static byte Display::_customChar[8]={  //represent cursor
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
 };

 
 Display::Display()
 {
  
 }
 
 void Display::init()
 {
  _lcd.init();
  _lcd.backlight();
  _lcd.createChar(0, _customChar);

  _lcd.clear();
  _lcd.setCursor(3,0);
  _lcd.print("Automatic");
  _lcd.setCursor(2,1);
  _lcd.print("Wire Cutter");
  delay(2000);
  _lcd.clear();
 }

 void Display::displayMainMenu(String items[], uint8_t len)
 {
  //Serial.println(curYCoord);
  _lcd.clear(); //clear stuffs from previous screen

  if(curYCoord>(len-1) || curYCoord<0)
  {
    if(curYCoord>(len-1)) curYCoord=(len-1);
    else                  curYCoord=0;
  }
  
  if(curYCoord<2) 
  {
    _lcd.setCursor(1,0);
    _lcd.print(items[0]);
    _lcd.setCursor(1,1);
    _lcd.print(items[1]);
    
    _lcd.setCursor(0,curYCoord);

  }
  else 
  {
    _lcd.setCursor(1,0);
    _lcd.print(items[curYCoord-1]);
    _lcd.setCursor(1,1);
    _lcd.print(items[curYCoord-0]);
    _lcd.setCursor(0,1);
  }

  if(cursorON) _lcd.blink();
  else 
  {
    _lcd.noBlink();
    _lcd.write((byte)0);
  }
 }

 static void Display::displayProgress(uint8_t total, uint8_t counter)
 {
  _lcd.clear(); //clear stuffs from previous screen
  _lcd.setCursor(1,0);
  _lcd.print("In Progress...");
  _lcd.setCursor(5,1);
  _lcd.print(counter);
  _lcd.print("/");
  _lcd.print(total);
 }
