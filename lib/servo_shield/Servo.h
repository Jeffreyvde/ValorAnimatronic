#ifndef SERVO_H
#define SERVO_H

#include <Adafruit_PWMServoDriver.h>

#pragma once

/**
 * @brief Helper class to control individual servos for the PWM servo shield
 * 
 */
class Servo
{
public:
    /**
     * @brief Construct a new Servo object
     * 
     * @param servoIndex The index of the servo shield we want to 
     * @param minimumPulseLength The servo fastest backward pulse length
     * @param maximumPulseLength The servo fastest forward pulse length
     * @param stopPulseLength At what pulse does the servo stop length
     * @param servoDriver The servo driver we want to set the values to
     */
    Servo(int servoIndex, int minimumPulseLength, int maximumPulseLength, int stopPulseLength,  Adafruit_PWMServoDriver& servoDriver);
    ~Servo() = default;

    /**
     * @brief Sets the PWM output of one of the PCA9685 pins
     * 
     *  @param on – At what point in the 4096-part cycle to turn the PWM output ON
     *  @param off – At what point in the 4096-part cycle to turn the PWM output OFF
     *  @return result from endTransmission
     */
    uint8_t SetPWM(uint16_t on, uint16_t off);

    /**
     * @brief Set the Speed servo 
     * 
     * @param value A value between -1000(Max backward) and 1000 (Max forward)
     *  
     */
    void SetSpeed(long value);

    /**
     * @brief Stop the servo
     */
    void Stop();

private:
    int servoIndex;
    
    int minimumPulseLength;
    int maximumPulseLength;
    int offPulseLength;

    Adafruit_PWMServoDriver& servoDriver;

    const int maxSpeedForwardInput = 1000;
    const int maxSpeedBackwardInput = -1000;
};

#endif