#include "encoder.h"
#include "Display.h"
#include "stepperMotor.h"

/*
 * Global variables:
 */
uint8_t wire_length=0;  //length of wire to cut
uint8_t quantity=0;     //quantity to cut
boolean prevEncState;   //track last state of enc
boolean busy = false;   //busy="True" means machine is cutting
String menu[] = 
{
  "LEN: " + (String)wire_length,
  "QTY: " + (String)quantity,
  "START"
};
uint8_t len = sizeof(menu)/sizeof(menu[0]);
uint16_t delayTime = 500;
 
#define stepsPerMm 6.3
#define stepsPerStrip 125
#define stepsPerCut 160


/*
 * Create objects
 */
stepperMotor cutter = stepperMotor(8, 9, 7, 1, 5);  //step pin, direction pin, enable pin, positive direction value
stepperMotor feeder = stepperMotor(11, 12, 10, 1);  //step pin, direction pin, enable pin, positive direction value
encoder ENC = encoder(2, 4, 3);
Display LCD = Display();



void setup()
{
  Serial.begin(9600);
  ENC.init();
  feeder.init();
  cutter.init();
  prevEncState = ENC.state;
  
  LCD.init();
  LCD.displayMainMenu(menu, len);
}



void loop()
{
  while(!busy)
  {
    if(ENC.counter!=0 || ENC.state!=prevEncState) //encoder is either rotated or pressed
    {
      if(ENC.counter!=0)  //encoder is rotated
      {  
        if(!LCD.cursorON) 
        {
          LCD.curYCoord = LCD.curYCoord + ENC.counter;
        }
        else
        {
          if(LCD.curYCoord==0)  
          {
            wire_length = wire_length + ENC.counter; //change wire_length
            menu[0] = "LEN: " + (String)wire_length;
          }
          else if(LCD.curYCoord==1) 
          {
            quantity = quantity + encoder::counter; //change quantity
            menu[1] = "QTY: " + (String)quantity;
          }
        }

        ENC.counter = 0;
      }

      else  //encoder is pressed
      {
        if(menu[LCD.curYCoord]!="START")
        {
          if(LCD.cursorON) LCD.cursorON=false;
          else             LCD.cursorON=true; 
        }
        else
        {
          busy = true;
        }

        prevEncState=ENC.state;  //set last encoder state to current state
      }

      LCD.displayMainMenu(menu, len);  //Refresh Display after any interation with encoder
    }
  }


  while(busy)
  {
    cutter.enable(true);
    feeder.enable(true);
    LCD.displayProgress(quantity, 0);

    /*
     * Initial Homing and Cut (so that the end of wire is flush with the cutter blade)
     */
    cutter.home();
    delay(delayTime);
    
    feeder.move(feeder.mmToSteps(10, stepsPerMm), 1, 2000);
    delay(delayTime);

    cutter.move(stepsPerCut, 0, 2000);
    delay(delayTime);
    cutter.home();
    delay(delayTime);
    
    /*
     * After each loop, a wire is cut
     */
    for(uint8_t i=0; i<quantity; i++)
    {
      task();
      LCD.displayProgress(quantity, i+1);
    }

    cutter.enable(false);
    feeder.enable(false);
    busy=false;
    ENC.counter = 0;
    prevEncState=ENC.state;
    LCD.displayMainMenu(menu, len);
  }
}



void task()
{ 
  feeder.move(feeder.mmToSteps(7, stepsPerMm), 1, 2000);
  delay(delayTime);
  
  cutter.move(stepsPerStrip, 0, 2000);
  delay(delayTime);
  cutter.home();
  delay(delayTime);
  
  feeder.move(feeder.mmToSteps(wire_length, stepsPerMm), 1, 2000);
  delay(delayTime);
  
  cutter.move(stepsPerStrip, 0, 2000);
  delay(delayTime);
  cutter.home();  
  delay(delayTime);

  feeder.move(feeder.mmToSteps(7, stepsPerMm), 1, 2000);
  delay(delayTime);

  cutter.move(stepsPerCut, 0, 2000);
  delay(delayTime);
  cutter.home();  
  delay(delayTime);
}
