/*
 * stepperMotor.cpp - Library for controlling basics movements of stepper motor.
 * Specifically designed for "Automatic Wire Cutter" project.
 * 
 * Created by FurbulousFox, January 12, 2024.
 */

 #include "Arduino.h"
 #include "stepperMotor.h"

 stepperMotor::stepperMotor(uint8_t stepPin, uint8_t dirPin, uint8_t enaPin, uint8_t positiveDir)  //motor without microswitch
 {
  _stepPin = stepPin;
  _dirPin = dirPin;
  _enaPin = enaPin;
  _positiveDir = positiveDir;
 }


 stepperMotor::stepperMotor(uint8_t stepPin, uint8_t dirPin, uint8_t enaPin, uint8_t positiveDir, int8_t swPin)  //motor with microswitch
 {
  _stepPin = stepPin;
  _dirPin = dirPin;
  _enaPin = enaPin;
  _positiveDir = positiveDir;
  _swPin = swPin;
 }


 void stepperMotor::init()
 {
  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
  pinMode(_enaPin, OUTPUT);
  digitalWrite(_enaPin, HIGH);  //disable stepper motor when microcontroller is powered up/programmed - prevent motor from vibrating
  if(_swPin != -1)  //if homing switch pin is declared
  {
    pinMode(_swPin, INPUT_PULLUP); //no external pull-up resistor is required
  }
 }


 void stepperMotor::move(uint16_t steps, uint8_t dir, uint16_t period)
 {
  digitalWrite(_dirPin, dir);
   
  for(uint16_t i=0; i<steps; i++) {
    digitalWrite(_stepPin, HIGH); //HIGH pulse
    delayMicroseconds(1);
    digitalWrite(_stepPin, LOW);  //LOW pulse
    delayMicroseconds(period - 1); //minus 1 because HIGH pulse is 1us
  }
 }


 void stepperMotor::home()
 {
  if(digitalRead(_swPin) == 0)
  {
    while(digitalRead(_swPin) == 0) 
    { 
      move(1, 1-_positiveDir, 2000);  //in case sw is already being pressed, move motor away from switch (1 step per loop)
    } 
    delay(500);
  }

  while(digitalRead(_swPin) == 1) {
    move(1, _positiveDir, 2000);
  }
 }


void stepperMotor::dirTest(uint8_t dir)
{
  digitalWrite(_enaPin, LOW);
  for(int i=0; i<5; i++)
  {
    move(1, dir, 2000);
    delay(1000);
  }
  digitalWrite(_enaPin, HIGH);
}


uint16_t stepperMotor::mmToSteps(float mm, float stepsPerMm)
{
  return stepsPerMm * mm;
}

 
void stepperMotor::enable(boolean b)
{
  if(b) digitalWrite(_enaPin, LOW);
  else  digitalWrite(_enaPin, HIGH);
}
