/*
 * encoder.h - Library for interacting with ONE encoder.
 * Specifically designed for "Automatic Wire Cutter" project only. 
 *
 * This library uses two interrupt pins: 
 *   One for one of the encoder's ouput pins to improve reliability; One for encoder's switch to allow for emergency stop.
 *   Turning the encoder will increment/decrease the value of the "counter" (a static variable that can be accessed in main). 
 *   "counter" is int8_t by default so its value is only from -128 to 127. To have a larger range, use int16_t or int32_t
 *   
 * Created by FurbulousFox, January 13, 2024.
 */

 #ifndef encoder_h
 #define encoder_h

 #include "Arduino.h"

 class encoder
 {
  public:
    encoder(uint8_t outputA, uint8_t outputB, uint8_t swPin);

    /*
     *direction - tell the direction of encoder: 0=stand still; -1=counter clockwise; 1=clockwise 
     *state - change from 0 to 1 and vice versa when encoder is pressed
     *static void init() - initialize encoder. Handle hardware configuration (called from the setup() function of the main sketch) 
     */
    static int8_t counter;
    static boolean state;
    void init();


  private:
    static uint8_t _outputA;
    static uint8_t _outputB;
    static uint8_t _swPin;
    static uint8_t _stateA;
    static uint8_t _prevStateA;
    static void _rotated();
    static void _pressed();
 };


 #endif
