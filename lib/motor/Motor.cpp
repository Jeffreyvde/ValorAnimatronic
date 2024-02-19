#include "Motor.h"

PidMotor::PidMotor(const Encoder &encoder, IController &speedController, IController &angleController, Motor& motor)
    : encoder(encoder),
      speedController(speedController),
      angleController(angleController),
      motor(motor)
{
}

void PidMotor::Tick()
{
    if(!isActive)
    {
        return;
    }

    long long currentTime = millis();
    double deltaTime = (currentTime - lastMillis) / 1000.0;

    double speed;
    if(toAngle)
    {
        speed = HandleAngleFeedForward(deltaTime);
    }
    else
    {
        speed = targetSpeed;  //HandleSpeedFeedForward(deltaTime);
        
    }

    SetMotorSpeed(speed);
    lastMillis = currentTime;
    lastAngle = encoder.GetAngle();
}

void PidMotor::SetUp()
{
}

void PidMotor::SetSpeed(bool forward, uint8_t speed)
{
    toAngle = false;
    moveForward = forward;
    targetSpeed = (forward) ? (int)speed : -(int)speed;
    SetMotorSpeed(targetSpeed);
}

void PidMotor::ToAngle(int angle)
{
    toAngle = true;
    targetAngle = angle;
    isActive = true;
    angleController.Reset();
}

void PidMotor::Stop()
{
    SetSpeed(true, 0);
}

bool PidMotor::IsActive() const
{
    return isActive;
}

double PidMotor::HandleAngleFeedForward(double deltaTime)
{  
    return angleController.Calculate(targetAngle - encoder.GetAngle(), deltaTime);
}

double PidMotor::HandleSpeedFeedForward(double deltaTime)
{   
    double currentSpeed = (encoder.GetAngle() - lastAngle) / deltaTime; 
    return speedController.Calculate(targetSpeed - currentSpeed, deltaTime);
}

void PidMotor::SetMotorSpeed(double speed)
{
    const double minSpeed = 35;
    const double zeroRange = 0.1;
    const double maxSpeed = 255;
    
    bool forward = speed > 0;
    speed = constrain(abs(speed), 0, maxSpeed);
    speed = speed > zeroRange ? map(speed, 0, maxSpeed, minSpeed, maxSpeed)  : 0; 

    motor.drive(forward ? speed : -speed);
    isActive = speed != 0;
}