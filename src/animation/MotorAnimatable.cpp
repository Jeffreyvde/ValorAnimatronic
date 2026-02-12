#include "MotorAnimatable.h"

MotorAnimatable::MotorAnimatable(Servo &motor, int defaultPoint)
    : motor(motor), defaultPoint(defaultPoint)
{
}

void MotorAnimatable::Start(const std::string& instruction)
{
    int value = std::stoi(instruction);
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
