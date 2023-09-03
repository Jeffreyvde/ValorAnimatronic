#include "Button.h"
#include "Motor.h"
#include "menu/Menu.h"
#include <Arduino.h>

Button button(2);
Motor headMotor(6, 9);
Motor wingMotor(10, 11);
Menu menu(button, headMotor, wingMotor, 12, 13);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    // Wait till Serial is ready
  }
  menu.SetUp();
}

void loop()
{
  menu.Tick();
}