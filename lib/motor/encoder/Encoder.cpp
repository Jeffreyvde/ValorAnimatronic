#include "Encoder.h"

Encoder::Encoder(uint8_t encoderPinA, uint8_t encoderPinB)
    : encoderPinA(encoderPinA),
      encoderPinB(encoderPinB),
      encoderPinState(0),
      angle(0)
{
}

void Encoder::SetUp()
{
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
}

void Encoder::Tick()
{
    int currentPinState = digitalRead(encoderPinA);
    if ((encoderPinState == LOW) && (currentPinState == HIGH))
    {
        if(digitalRead(encoderPinB) == HIGH)
        {
            angle++;
        }
        else
        {
            angle--;
        }
    }
    encoderPinState = currentPinState;
}

long long Encoder::GetAngle() const
{
    return angle;
}
