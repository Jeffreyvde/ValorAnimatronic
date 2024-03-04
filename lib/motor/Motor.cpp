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

void PidMotor::Calibrate()
{
    minSpeed = 0;
    const long long minimumVerifiedAngle = 2;
    while (encoder.GetAngle() < minimumVerifiedAngle)
    {
        // Check if we have reached the maxSpeed
        if(++minSpeed == maxSpeed)
        {
            Serial.println("Setup failed");
            minSpeed = 0;
            break;
        }
        // Test if we move with the current minimumSpeed
        SetMotorSpeed(1);
        delay(50);
    }
    Stop();
    ToAngle(0);
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
    Serial.println((int)encoder.GetAngle());
}

void PidMotor::Stop()
{
    SetMotorSpeed(0);
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
    const double zeroRange = 0.1;
    
    bool forward = speed > 0;
    speed = constrain(abs(speed), 0, maxSpeed);
    speed = speed > zeroRange ? map(speed, 0, maxSpeed, minSpeed, maxSpeed)  : 0; 

    motor.drive(forward ? speed : -speed);
    isActive = speed != 0;
}