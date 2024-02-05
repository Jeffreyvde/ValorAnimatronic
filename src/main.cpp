#include "Button.h"
#include "Motor.h"
#include "encoder/Encoder.h"
#include "controller/PidController.h"
#include "menu/Menu.h"
#include "animation/AnimationManager.h"
#include "animation/MotorAnimatable.h"
#include "animation/Animation.h"
#include "animation/IAnimatable.h"
#include <Arduino.h>
                                                                                                                                                                                                    
long long minimumDeltaTime = 20;
long long tickTime = 0;

constexpr uint8_t headEncoderPin = 3;
constexpr uint8_t wingEncoderPin = 2;
constexpr uint8_t buttonPin = 4;

Button button(buttonPin);
Encoder headEncoder(headEncoderPin, 5);
Encoder wingEncoder(wingEncoderPin, 7);
PidController angleControllerHead(.4, 0, .005);
PidController speedControllerHead(0, 0, 0);
PidController angleControllerWing(.5, 0, .005);
PidController speedControllerWing(0, 0, 0);

Motor wingMotor(wingEncoder, speedControllerWing, angleControllerWing, 10, 11);
Motor headMotor(headEncoder, speedControllerHead, angleControllerHead, 6, 9);

MotorAnimatable wingAnimatable(wingMotor);
MotorAnimatable headAnimatable(headMotor);

IAnimatable* animationComponents[] = {&headAnimatable, &wingAnimatable};

TimelineValue baseAnimationValuesHead[] = {{"1200", 0, 1000}, {"-1200", 0, 1000}, {"0", 0, 1000}};
TimelineValue baseAnimationValuesWing[] = {{"-250", 2000, 1000}, {"-40", 500, 1000}, {"0", 0, 1000}, {"-250", 500, 1000}, {"-40", 500, 1000}, {"0", 0, 1000}};
Timeline baseAnimationTimelineWing = {6, baseAnimationValuesWing};
Timeline baseAnimationTimelineHead = {3, baseAnimationValuesHead};
Timeline baseAnimationTimeline[] = {baseAnimationTimelineHead, baseAnimationTimelineWing};
Animation baseAnimation(baseAnimationTimeline, animationComponents, 2);

TimelineValue secondAnimationValuesHead[] = {{"2400", 0, 1000}, {"-2400", 0, 1000}, {"0", 0, 1000}};
TimelineValue secondAnimationValuesWing[] = {{"-250", 0, 1000}, {"0", 50, 1000}, {"-250", 500, 1000}, {"0", 0, 1000}, {"-250", 50, 1000}, {"0", 0, 1000}};
Timeline secondAnimationTimelineWing = {6, secondAnimationValuesWing};
Timeline secondAnimationTimelineHead = {3, secondAnimationValuesHead};
Timeline secondAnimationTimeline[] = {secondAnimationTimelineHead, secondAnimationTimelineWing};
Animation secondAnimation(secondAnimationTimeline, animationComponents, 2);

Animation animations[] = {baseAnimation, secondAnimation};
AnimationManager animationManager(animations, 2);

Menu menu(button, animationManager, headMotor, wingMotor, 12, 13);

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
  if (millis() > tickTime)
  {
    headMotor.Tick();
    wingMotor.Tick();
    tickTime = millis() + minimumDeltaTime;
  }

  menu.Tick();
}