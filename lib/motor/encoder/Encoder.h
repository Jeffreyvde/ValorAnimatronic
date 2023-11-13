#ifndef ENCODER_H
#define ENCODER_H

#pragma once

#include <Arduino.h>

/**
 * @brief Wrapper class to handle the angle calculation for an Encoder
 * 
 */
class Encoder
{
public:
    /**
     * @brief Construct a wrapper for an Encoder
     * 
     * @param encoderPinA Pin A for the encoder
     * @param encoderPinB Pin B for the encoder
     */
    Encoder(uint8_t encoderPinA, uint8_t encoderPinB);

    /**
     * @brief Set up the pins for the Encoder
     * 
     */
    void SetUp();

    /**
     * @brief One update for the Encoder 
     * 
     */
    void Tick();

    /**
     * @brief Get the current relative Angle of the encoder
     * 
     * @return long long The Angle itself
     */
    long long GetAngle() const;


private:
    uint8_t encoderPinA; 
    uint8_t encoderPinB;

    volatile int encoderPinState;
    volatile long long angle;
};

#endif