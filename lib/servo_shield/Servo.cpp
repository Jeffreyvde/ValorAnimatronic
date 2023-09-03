#include "Servo.h"
#include <Arduino.h>

Servo::Servo(int servoIndex, int minimumPulseLength, int maximumPulseLength, int stopPulseLength, Adafruit_PWMServoDriver &servoDriver):
      servoIndex(servoIndex),
      minimumPulseLength(minimumPulseLength),
      maximumPulseLength(maximumPulseLength),
      offPulseLength(stopPulseLength),
      servoDriver(servoDriver)
{
}

uint8_t Servo::SetPWM(uint16_t on, uint16_t off)
{
    return servoDriver.setPWM(servoIndex, on, off);
}

void Servo::SetSpeed(long value)
{
    int speed = map(value, maxSpeedBackwardInput, maxSpeedForwardInput, minimumPulseLength, maximumPulseLength);
    SetPWM(0, speed);
}

void Servo::Stop()
{
    servoDriver.setPin(servoIndex, offPulseLength);
}