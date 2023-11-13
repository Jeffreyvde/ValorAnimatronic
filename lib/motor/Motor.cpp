#include "Motor.h"

Motor::Motor(const Encoder &encoder, const Controller &controller, uint8_t pinForward, uint8_t pinBackward)
    : encoder(encoder),
      controller(controller),
      pinForward(pinForward),
      pinBackward(pinBackward)
{
}

void Motor::SetUp()
{
    pinMode(pinForward, OUTPUT);
    pinMode(pinBackward, OUTPUT);
}

void Motor::SetSpeed(bool forward, uint8_t speed)
{
    analogWrite(pinForward, (forward) ? speed : 0);
    analogWrite(pinBackward, (!forward) ? speed : 0);
    isActive = speed != 0;
}

bool Motor::IsActive() const
{
    return isActive;
}

void Motor::Stop()
{
    SetSpeed(true, 0);
}
