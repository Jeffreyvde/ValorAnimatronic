#include "MotorAnimatable.h"

MotorAnimatable::MotorAnimatable(PidMotor &motor)
    : motor(motor)
{
}

void MotorAnimatable::Start(const char instruction[])
{
    motor.ToAngle(atoi(instruction));
}

bool MotorAnimatable::IsFinished()
{
    return !motor.IsActive();
}

void MotorAnimatable::Stop()
{
    motor.ToAngle(0);
}
