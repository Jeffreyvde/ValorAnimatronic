#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#pragma once

#include "IController.h"

/**
 * @brief Basic PID controller
 * 
 */
class PidController : public IController
{
public:
    /**
     * @brief Construct a new Pid Controller object
     * 
     * @param pWeight 
     * @param iWeight 
     * @param dWeight 
     */
    PidController(double pWeight, double iWeight, double dWeight);

    /**
     * @brief Calculate the PID value
     * 
     * @param error The error from the desired value
     * @param deltaTime The time since last call
     * @return double The calculated PID value
     */
    double Calculate(double error, double deltaTime) override;

    /**
     * @brief Reset the controller
     * 
     */
    void Reset();

    /**
     * @brief Set the new proportional weight
     * 
     * @param value The new weight value
     */
    void SetPWeight(double value);

    /**
     * @brief Set the new integral weight
     * 
     * @param value The new weight value
     */
    void SetIWeight(double value);

    /**
     * @brief Set a new derivative weight
     * 
     * @param value The new weight value
     */
    void SetDWeight(double value);

private:
    double pWeight;
    double iWeight;
    double dWeight;

    double integralValue;
    double lastError;
};

#endif