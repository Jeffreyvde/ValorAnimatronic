#include "Button.h"
#include "encoder/Encoder.h"
#include "controller/PidController.h"
#include "animation/AnimationManager.h"
#include "animation/MotorAnimatable.h"
#include "animation/Animation.h"
#include "animation/IAnimatable.h"
#include "Speaker.h"
#include "animation/SpeakerAnimatable.h"
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
Speaker speaker(Serial1, 15);

MotorAnimatable wingAnimatable(wingServo, 180);
MotorAnimatable headAnimatable(headServo, 90);
SpeakerAnimatable speakerAnimatable(speaker);

IAnimatable* animationComponents[] = {&headAnimatable, &wingAnimatable, &speakerAnimatable};

TimelineValue baseAnimationValuesHead[] = {{"0", 3000, 0}, {"180", 3000, 0}, {"90", 3000, 0}};
Timeline baseAnimationTimelineHead = {sizeof(baseAnimationValuesHead) / sizeof(TimelineValue), baseAnimationValuesHead};

TimelineValue baseAnimationValuesWing[] =  {{"110", 0, 0}, {"140", 2000, 0}, {"180", 500, 0}, {"110", 3000, 0}, {"140", 100, 0}, {"180", 500, 0}};
Timeline baseAnimationTimelineWing = {sizeof(baseAnimationValuesWing) / sizeof(TimelineValue), baseAnimationValuesWing};

TimelineValue baseAnimationValuesSpeaker[] =  {{"1", 0, 0}, {"1", 5000, 0}};
Timeline baseAnimationTimelineSpeaker = {sizeof(baseAnimationValuesSpeaker) / sizeof(TimelineValue), baseAnimationValuesSpeaker};


Timeline baseAnimationTimeline[] = {baseAnimationTimelineHead, baseAnimationTimelineWing, baseAnimationTimelineSpeaker};
Animation baseAnimation(baseAnimationTimeline, animationComponents, 3);

Animation animations[] = {baseAnimation};
AnimationManager animationManager(animations, sizeof(animations) / sizeof(Animation));

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
  Serial1.begin(9600);

  wingServo.attach(10);
  headServo.attach(11);

  // Set to default positions
  wingServo.write(180);
  headServo.write(90);

  delay(1000);
  animationManager.PlayNext();
}

void loop()
{
  animationManager.Tick();
}