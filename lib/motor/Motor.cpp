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

    //Serial.print(" Angle: ");
    //Serial.print((int)encoder.GetAngle());
    //Serial.print(" POS: ");
    //Serial.print(encoder.GetAngle() > 0);

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
    moveForward = forward;
    targetSpeed = (forward) ? (int)speed : -(int)speed;
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
    //Serial.print(" Target: ");
    //Serial.print(targetAngle);

    //Serial.print(" Error: ");
    //Serial.print((double)(targetAngle - encoder.GetAngle()));
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
    const double maxSpeed = 255;

    //Serial.print(" Speed: ");
    //Serial.print(speed);

    bool forward = speed > 0;
    speed = constrain(abs(speed), 0, maxSpeed);
    speed = speed > zeroRange ? map(speed, 0, maxSpeed, minSpeed, maxSpeed)  : 0; 
    //Serial.print(" Forward: ");
    //Serial.print(forward);

    Serial.print(" Speed: ");
    Serial.print(speed);

    uint8_t pwmValue = (uint8_t)speed;

    //Serial.print(" Pinforward: ");
    //Serial.print((forward) ? pwmValue : 0);
    
    //Serial.print(" Pinbackward: ");
    //Serial.println( (!forward) ? pwmValue : 0);

    analogWrite(pinForward, (forward) ? pwmValue : 0);
    analogWrite(pinBackward, (!forward) ? pwmValue : 0);
    isActive = speed != 0;
}