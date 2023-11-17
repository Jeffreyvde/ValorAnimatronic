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
    if ((encoderPinState == LOW) && (currentPinState == HIGH))
    {
        if(digitalRead(encoderPinB) == HIGH)
        {
            angle++;   
            Serial.print("Right: ");
            Serial.println((int)angle);
        }
        else
        {
            angle--;
            Serial.print("Left: ");
            Serial.println((int)angle);
        }
    }
    encoderPinState = currentPinState;
}

long long Encoder::GetAngle() const
{
    return angle;
}
