#include "MotorAnimatable.h"
#include <stdlib.h>
#include <Arduino.h>

MotorAnimatable::MotorAnimatable(Servo &motor, int defaultPoint)
    : motor(motor), defaultPoint(defaultPoint)
{
}

void MotorAnimatable::Start(const char instruction[])
{
    int value = atoi(instruction);
    Serial.println(value);
    motor.write(value);
}

bool MotorAnimatable::IsFinished()
{
    // Default to false as we dont know the servo state
    return false;
}

void MotorAnimatable::Stop()
{
    motor.write(defaultPoint);
}
