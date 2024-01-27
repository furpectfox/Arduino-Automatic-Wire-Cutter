/*
 * encoder.cpp - Library for interacting with ONE encoder.
 * Specifically designed for "Automatic Wire Cutter" project only. 
 *
 * This library uses two interrupt pins: 
 *   One for one of the encoder's ouput pins to improve reliability; One for encoder's switch to allow for emergency stop.
 *   Turning the encoder will increment/decrease the value of the "counter" (a static variable that can be accessed in main). 
 *   "counter" is int8_t by default so its value is only from -128 to 127. To have a larger range, use int16_t or int32_t
 *   
 * Created by FurbulousFox, January 13, 2024.
 */
 
 #include "Arduino.h"
 #include "encoder.h"

 static uint8_t encoder::_outputA;
 static uint8_t encoder::_outputB;
 static uint8_t encoder::_swPin;
 static int8_t encoder::counter = 0;
 static uint8_t encoder::_stateA;
 static uint8_t encoder::_prevStateA;
 static boolean encoder::state=false;

 encoder::encoder(uint8_t outputA, uint8_t outputB, uint8_t swPin)
 {
  _outputA = outputA;
  _outputB = outputB;
  _swPin = swPin;
 }

 void encoder::init()
 {  
  pinMode(_outputA, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_outputA), _rotated, CHANGE); 
  
  pinMode(_outputB, INPUT_PULLUP);
  
  pinMode(_swPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_swPin), _pressed, FALLING);
  
  _prevStateA = digitalRead(_outputA);
  counter = 0;
  state = 0;
 }

 static void encoder::_rotated()
 {
  _stateA = digitalRead(_outputA);
  
  if(_stateA != _prevStateA)
  {
    if(digitalRead(_outputB) != _stateA) 
    {
      counter--;
    }
    else
    {
      counter++;
    }
    
    _prevStateA = _stateA;
  }
 }

 static void encoder::_pressed()
 {
  if(state==false)
  {
    state=true;
  }
  else
  {
    state=false;
  }
 }

 
