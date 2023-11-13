#include "Button.h"
#include "Motor.h"
#include "encoder/Encoder.h"
#include "menu/Menu.h"
#include <Arduino.h>

Button button(2);
Motor headMotor(6, 9);
Encoder headEncoder(7, 5);
Motor wingMotor(10, 11);
Encoder wingEncoder(4, 3);
Menu menu(button, headMotor, wingMotor, 12, 13);

long long test = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    // Wait till Serial is ready
  }
  menu.SetUp();


  headEncoder.SetUp();
  wingEncoder.SetUp();

}

void loop()
{
  headEncoder.Tick();
  wingEncoder.Tick(); 
  
  menu.Tick();
}