/*
 * stepperMotor.h - Library for controlling basics movements of stepper motor.
 * Specifically designed for "Automatic Wire Cutter" project.
 * 
 * Created by FurbulousFox, January 12, 2024.
 */

 #ifndef stepperMotor_h
 #define stepperMotor_h

 #include "Arduino.h"

 class stepperMotor
 {
  public:
    /*Constructors:
     *stepperMotor(step pin, direction pin, enable pin, foward direction(1 or 0)) - motor NOT required homing
     *stepperMotor(step pin, direction pin, enable pin, foward direction(1 or 0), switch's signal pin) - motor required homing
     */
    stepperMotor(uint8_t stepPin, uint8_t dirPin, uint8_t enaPin, uint8_t positiveDir);
    stepperMotor(uint8_t stepPin, uint8_t dirPin, uint8_t enaPin, uint8_t positiveDir, int8_t swPin);   
    
    /* void init() - Initialize motor. Handle hardware configuration (called from the setup() function of the main sketch)
     * void home() - Home motor
     * void move(number_of_steps_required, diection, time(us)_between_steps) - Move motor a certain number of steps in a certain direction
     * uint16_t mmToStep(distance in milimeters) - Convert distance in mm to number of steps
     * void dirTest(direction(1_or_0)) - Tell motor takes 5 steps, slowly, for testing the direction of motor (by choosing value of 1 or 0 for positiveDir variable)
     * void enable(true or false) - enable driver
     */
    void init(); 
    void move(uint16_t steps, uint8_t dir, uint16_t period);
    uint16_t mmToSteps(float mm, float stepsPerMm);
    void home();
    void dirTest(uint8_t dir);
    void enable(boolean b);

    
  private:  //underscore before variable to indicate a private variable
    uint8_t _stepPin;
    uint8_t _dirPin;
    uint8_t _enaPin;
    uint8_t _positiveDir;
    int8_t _swPin = -1;  //no pin is selected by default
 };

 #endif
