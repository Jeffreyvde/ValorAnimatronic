#include "Encoder.h"

Encoder::Encoder(uint8_t encoderPinA, uint8_t encoderPinB)
    : encoderPinA(encoderPinA),
      encoderPinB(encoderPinB)
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
    if (encoderPinState != currentPinState)
    {
        if(digitalRead(encoderPinB) == currentPinState)
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
