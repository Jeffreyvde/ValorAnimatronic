#ifndef MOTOR_H
#define MOTOR_H

#pragma once

#include <Arduino.h>
#include "encoder/Encoder.h"
#include "controller/Controller.h"

class Motor
{
public:
    /**
     * @brief Construct a new Motor 
     *
     * @param encoder The encoder for the motor 
     * @param controller the PID controller for the Motor
     * @param pinForward The pin to forward the 
     * @param pinBackward The pin to 
     */
    Motor(const Encoder& encoder, const Controller& controller, uint8_t pinForward, uint8_t pinBackward);

    /**
     * @brief Set up the motor pins
     *
     */
    void SetUp();

    /**
     * @brief Set the Speed object
     * 
     * @param forward If the motor should go forward or backward
     * @param speed The speed of the motor from 0 (off) 255 full speed
     */
    void SetSpeed(bool forward, uint8_t speed);

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
    const Controller& controller;

    uint8_t pinForward; 
    uint8_t pinBackward;

    bool isActive = false;

};

#endif