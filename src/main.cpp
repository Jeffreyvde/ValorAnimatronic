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

#define AIN1 A3
#define STBY A4
#define BIN1 A5
#define BIN2 6
#define PWMB 9
#define AIN2 10
#define PWMA 11

const int offsetA = -1;
const int offsetB = 1;

Motor motor1 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
Motor motor2 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

long long minimumDeltaTime = 20;
long long tickTime = 0;

constexpr uint8_t headEncoderPin = 3;
constexpr uint8_t wingEncoderPin = 2;
constexpr uint8_t buttonPin = 4;

Button button(buttonPin);
Encoder headEncoder(headEncoderPin, 5);
Encoder wingEncoder(wingEncoderPin, 8);
PidController angleControllerHead(.4, 0, .01);
PidController speedControllerHead(0, 0, 0);
PidController angleControllerWing(.4, 0, .005);
PidController speedControllerWing(0, 0, 0);

PidMotor wingMotor(wingEncoder, speedControllerWing, angleControllerWing, motor1);
PidMotor headMotor(headEncoder, speedControllerHead, angleControllerHead, motor2);

MotorAnimatable wingAnimatable(wingMotor);
MotorAnimatable headAnimatable(headMotor);

IAnimatable* animationComponents[] = {&headAnimatable, &wingAnimatable};

TimelineValue baseAnimationValuesHead[] = {{"1200", 0, 5000}, {"-1200", 0, 5000}, {"0", 0, 5000}};
Timeline baseAnimationTimelineHead = {sizeof(baseAnimationValuesHead) / sizeof(TimelineValue), baseAnimationValuesHead};

TimelineValue baseAnimationValuesWing[] =  {{"-250", 2000, 1000}, {"-40", 500, 1000}, {"0", 0, 1000}, {"-250", 500, 1000}, {"-40", 500, 1000}, {"0", 0, 1000}};
Timeline baseAnimationTimelineWing = {sizeof(baseAnimationValuesWing) / sizeof(TimelineValue), baseAnimationValuesWing};

Timeline baseAnimationTimeline[] = {baseAnimationTimelineHead, baseAnimationTimelineWing};
Animation baseAnimation(baseAnimationTimeline, animationComponents, 2);

TimelineValue secondAnimationValuesHead[] = {{"2400", 0, 2000}, {"-2400", 0, 2000}, {"0", 0, 2000}};
Timeline secondAnimationTimelineHead = {sizeof(secondAnimationValuesHead) / sizeof(TimelineValue), secondAnimationValuesHead};



TimelineValue secondAnimationValuesWing[]  = {{"-250", 0, 1000}, {"0", 50, 1000}, {"-250", 500, 1000}, {"0", 0, 1000}, {"-250", 50, 1000}, {"0", 0, 1000}};
Timeline secondAnimationTimelineWing = {sizeof(secondAnimationValuesWing) / sizeof(TimelineValue), secondAnimationValuesWing};

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

  attachInterrupt(digitalPinToInterrupt(headEncoderPin), HandleHeadEncoderTick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(wingEncoderPin), HandleWingEncoderTick, CHANGE);

  headMotor.Calibrate();
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