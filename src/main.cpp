#include "Button.h"
#include <Arduino.h>

Button button(2);
Button::ButtonState state;

void setup() 
{
  Serial.begin(9600);
  while(!Serial)
  {
    // Wait till Serial is ready
  }
  button.SetUp();
}

void loop() 
{
  button.Tick();

  const auto currentState = button.GetState();
  if(state != currentState)
  {
    state = currentState;
    Serial.println((int)state);
  }
}