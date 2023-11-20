#include "Button.h"
#include "Motor.h"
#include "encoder/Encoder.h"
#include "controller/PidController.h"
#include "menu/Menu.h"
#include <Arduino.h>


long long minimumDeltaTime = 50;
long long tickTime = 0;

constexpr uint8_t headEncoderPin = 3;
constexpr uint8_t wingEncoderPin = 2;

Button button(4);
Encoder headEncoder(headEncoderPin, 5);
Encoder wingEncoder(wingEncoderPin, 7);
PidController angleControllerHead(.2, 0, 0);
PidController speedControllerHead(.7, 0, 0);
PidController angleControllerWing(0, 0, 0);
PidController speedControllerWing(0, 0, 0);

Motor wingMotor(wingEncoder, speedControllerWing, angleControllerWing, 10, 11);
Motor headMotor(headEncoder, speedControllerHead, angleControllerHead, 6, 9);

Menu menu(button, headMotor, wingMotor, 12, 13);

void HandleHeadEncoderTick()
{
  headEncoder.Tick();
}

void HandleWingEncoderTick()
{
  wingEncoder.Tick();
}

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

  wingMotor.SetUp();
  headMotor.SetUp();

  attachInterrupt(digitalPinToInterrupt(headEncoderPin), HandleHeadEncoderTick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(wingEncoderPin), HandleWingEncoderTick, CHANGE);
}

void loop()
{
  if(millis() > tickTime)
  {
    headMotor.Tick();
    wingMotor.Tick();
    tickTime = millis() + minimumDeltaTime;
  }
  menu.Tick();
}