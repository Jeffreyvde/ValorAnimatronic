#ifndef MOTORANIMATABLE_H
#define MOTORANIMATABLE_H

#pragma once

#include "IAnimatable.h"
#include <Servo.h>

/**
 * @brief An animation component to move motors
 * 
 */
class MotorAnimatable : public IAnimatable
{
public:

    /**
     * @brief Construct a new Motor Animatable object
     * 
     */
    MotorAnimatable(Servo& motor, int defaultPoint);

    /**
     * @brief Instruct the motor to go to a specific angle position.
     * 
     * @param instruction The instruction for what the animatable object should do. The value is only the Angle that it should go to.
     */
    void Start(const char instruction[]) override;

    /**
     * @brief Check wether the motor is at that angle position
     * 
     * @return true If it is at the position
     * @return false If it is not yet at that position
     */
    bool IsFinished() override;

    /**
     * @brief Cancel the animation
     * 
     */
    void Stop() override;
private:
    Servo& motor;
    int defaultPoint;
};

#endif