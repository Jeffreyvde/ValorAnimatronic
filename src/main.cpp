#include "Button.h"
#include "encoder/Encoder.h"
#include "controller/PidController.h"
#include "animation/AnimationManager.h"
#include "animation/MotorAnimatable.h"
#include "animation/Animation.h"
#include "animation/IAnimatable.h"
#include <Arduino.h>

#include <Servo.h>

#define AIN1 A3
#define STBY A4
#define BIN1 A5
#define BIN2 6
#define PWMB 9
#define AIN2 10
#define PWMA 11

const int offsetA = -1;
const int offsetB = 1;

long long minimumDeltaTime = 20;
long long tickTime = 0;

constexpr uint8_t headEncoderPin = 3;
constexpr uint8_t wingEncoderPin = 2;
constexpr uint8_t buttonPin = 4;

Button button(buttonPin);
Servo headServo;
Servo wingServo;

MotorAnimatable wingAnimatable(wingServo, 180);
MotorAnimatable headAnimatable(headServo, 90);

IAnimatable* animationComponents[] = {&headAnimatable, &wingAnimatable};

TimelineValue baseAnimationValuesHead[] = {{"0", 5000, 0}, {"180", 5000, 0}, {"90", 5000, 0}};
Timeline baseAnimationTimelineHead = {sizeof(baseAnimationValuesHead) / sizeof(TimelineValue), baseAnimationValuesHead};

TimelineValue baseAnimationValuesWing[] =  {{"80", 500, 0}, {"140", 5000, 0}, {"180", 500, 0}, {"110", 500, 0}, {"140", 100, 0}, {"180", 500, 0}};
Timeline baseAnimationTimelineWing = {sizeof(baseAnimationValuesWing) / sizeof(TimelineValue), baseAnimationValuesWing};

Timeline baseAnimationTimeline[] = {baseAnimationTimelineHead, baseAnimationTimelineWing};
Animation baseAnimation(baseAnimationTimeline, animationComponents, 2);

Animation animations[] = {baseAnimation};
AnimationManager animationManager(animations, sizeof(animations) / sizeof(Animation));

void setup()
{
  Serial.begin(9600);

  wingServo.attach(10);
  headServo.attach(11);
  wingServo.write(180);
  headServo.write(90);
  delay(500);
  animationManager.PlayNext();
}

void loop()
{
  animationManager.Tick();
}