#ifndef MOTOR_H
#define MOTOR_H

#pragma once

#include <Arduino.h>
#include "encoder/Encoder.h"
#include "controller/IController.h"
#include <SparkFun_TB6612.h>

class PidMotor
{
public:
    /**
     * @brief Construct a new Motor 
     *
     * @param encoder The encoder for the motor 
     * @param speedController the PID controller for the speed of the Motor
     * @param angleController the PID controller for the angle of the Motor
     * @param motor The motor driver controller
     */
    PidMotor(const Encoder& encoder, IController& speedController, IController& angleController, Motor& motor);


    /**
     * @brief Controller tick
     * 
     */
    void Tick();

    /**
     * @brief Calibrates the minimum speed for the motor
     *
     */
    void Calibrate();

    /**
     * @brief Set the Speed object
     * 
     * @param forward If the motor should go forward or backward
     * @param speed The speed of the motor from 0 (off) 255 full speed
     */
    void SetSpeed(bool forward, uint8_t speed);

    /**
     * @brief Set the desired angle
     * 
     * @param angle The desired Angle
     */
    void ToAngle(int angle);

    /**
     * @brief Stop the motor
     * 
     */
    void Stop();

    /**
     * @brief Check if the motor is currently active
     * 
     * @return true If the motor is currently spinning
     * @return false If the motor is current inactive 
     */
    bool IsActive() const;

private:
    const Encoder& encoder;
    IController& speedController;
    IController& angleController;

    Motor motor; 

    bool isActive = false;
    bool toAngle = false;

    int targetSpeed = 0;
    bool moveForward = false;

    int targetAngle = 0;

    long long lastMillis = 0;
    long long lastAngle = 0;

    double minSpeed = 27;
    const double maxSpeed = 255;


    /**
     * @brief Handle the calculations for angle controlling
     * 
     * @param deltaTime The time since the last call
     * @return double The calculator controller value
     */
    double HandleAngleFeedForward(double deltaTime);

    /**
     * @brief Handle the calculations for speed controlling
     * @param deltaTime The time since the last call
     * @return double The calculator controller value
     */
    double HandleSpeedFeedForward(double deltaTime);

    /**
     * @brief Instruct the motor to have a specific speed
     * @param speed The speed of the motor from 0 (off) 255 full speed
     */
    void SetMotorSpeed(double speed);
};

#endif