#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#pragma once

/**
 * @brief Controller interface
 * 
 */
class IController
{
    public:
        virtual ~IController() = default;

        /**
         * @brief Calculate the controller value
         * 
         * @param error The error from desired target
         * @param deltaTime The time since last call
         * @return double The calculator controller value
         */
        virtual double Calculate(double error, double deltaTime) = 0;

        /**
         * @brief Reset the controller
         * 
         */
        virtual void Reset() = 0;
};

#endif