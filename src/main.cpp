#include "Button.h"
#include "Motor.h"
#include "encoder/Encoder.h"
#include "controller/PidController.h"
#include "menu/Menu.h"
#include <Arduino.h>


long long minimumDeltaTime = 50;
long long tickTime = 0;

long long test = 10000;
long long test2 = 0;

int desiredAngle = 300;
bool positive = true;

Button button(2);
Encoder headEncoder(7, 5);
Encoder wingEncoder(4, 3);
PidController angleControllerHead(.2, 0, 0);
PidController speedControllerHead(.7, 0, 0);
PidController angleControllerWing(0, 0, 0);
PidController speedControllerWing(0, 0, 0);

Motor wingMotor(wingEncoder, speedControllerWing, angleControllerWing, 10, 11);
Motor headMotor(headEncoder, speedControllerHead, angleControllerHead, 6, 9);

Menu menu(button, headMotor, wingMotor, 12, 13);

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
  //wingEncoder.Tick(); 

  if(millis() > tickTime)
  {
    headMotor.Tick();
    wingMotor.Tick();
    tickTime = millis() + minimumDeltaTime;
  }

  if(millis() > test2 && !headMotor.IsActive())
  {
    headMotor.ToAngle(positive ? desiredAngle : -desiredAngle);
    Serial.println("Switch");
    positive = !positive;
    test2 = test + millis();
  }
  else if(millis() > test2 && headMotor.IsActive())
  {
    Serial.println("Increase");
    test2 = test + millis();
  }

  menu.Tick();
}