/*
 * Display.h - Library for displaying a custom menu for Automatic_Wire_Cutter on Liquid Crystal 16x2.
 * Specifically designed for "Automatic Wire Cutter" project only.
 * 
 * Created by FurbulousFox, January 14, 2024.
 */

 #ifndef Display_h
 #define Display_h

 #include "Arduino.h"
 #include <LiquidCrystal_I2C.h>

 class Display
 {
  public:

    Display();

    /*static void init() - initialize display and print welcoming message (called from the setup() function of the main sketch)
     *static void display()
     */
    static boolean cursorON;  
    static int8_t curYCoord; //y_coordinate of cursor
    void init();
    void displayMainMenu(String items[], uint8_t len);
    void displayProgress(uint8_t total, uint8_t counter);


  private:
    static LiquidCrystal_I2C _lcd;
    static byte _customChar[8];
 };

 #endif
