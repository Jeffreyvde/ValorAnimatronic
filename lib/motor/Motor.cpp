#include "Motor.h"

Motor::Motor(const Encoder &encoder, IController &speedController, IController &angleController, uint8_t pinForward, uint8_t pinBackward)
    : encoder(encoder),
      speedController(speedController),
      angleController(angleController),
      pinForward(pinForward),
      pinBackward(pinBackward)
{
}

void Motor::Tick()
{
    long long currentTime = millis();
    double deltaTime = (currentTime - lastMillis) / 1000.0;

    double speed;
    if(toAngle)
    {
        speed = HandleAngleFeedForward(deltaTime);
    }
    else
    {
        speed = HandleSpeedFeedForward(deltaTime);
    }

    SetMotorSpeed(speed);
    lastMillis = currentTime;
    lastAngle = encoder.GetAngle();
}

void Motor::SetUp()
{
    pinMode(pinForward, OUTPUT);
    pinMode(pinBackward, OUTPUT);
}

void Motor::SetSpeed(bool forward, uint8_t speed)
{
    toAngle = false;
    this->forward = forward;
    targetSpeed = (forward) ? speed : -speed;
}

void Motor::ToAngle(int angle)
{
    toAngle = true;
    targetAngle = angle;
}

void Motor::Stop()
{
    SetSpeed(true, 0);
}

bool Motor::IsActive() const
{
    return isActive;
}

double Motor::HandleAngleFeedForward(double deltaTime)
{  
    Serial.print("Target Angle: ");
    Serial.print(targetAngle);
    Serial.print(" Angle: ");
    Serial.print((int)encoder.GetAngle());
    return angleController.Calculate(targetAngle - encoder.GetAngle(), deltaTime);
}

double Motor::HandleSpeedFeedForward(double deltaTime)
{   
    double currentSpeed = (encoder.GetAngle() - lastAngle) / deltaTime; 
    return speedController.Calculate(targetSpeed - currentSpeed, deltaTime);
}

void Motor::SetMotorSpeed(double speed)
{
    const double minSpeed = 35;
    const double zeroRange = 0.1;

    if(speed < zeroRange)
    {
        speed = 0;
    }
    else if(speed < minSpeed)
    {
        speed = minSpeed;
    }

    uint8_t pwmValue = (uint8_t)abs(speed);

    analogWrite(pinForward, (speed > 0) ? pwmValue : 0);
    analogWrite(pinBackward, (speed < 0) ? pwmValue : 0);
    isActive = speed != 0;
}