#include "Button.h"
#include "menu/Menu.h"
#include <Arduino.h>

Button button(2);
Menu menu(button, 12, 13);

void setup() 
{
  Serial.begin(9600);
  while(!Serial)
  {
    // Wait till Serial is ready
  }
  menu.SetUp();
}

void loop() 
{
  menu.Tick();
}