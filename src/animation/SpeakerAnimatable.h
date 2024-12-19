#ifndef SPEAKER_ANIMATABLE_H
#define SPEAKER_ANIMATABLE_H

#pragma once

#include "IAnimatable.h"
#include "Speaker.h"

/**
 * @brief An animation component to start a speaker
 * 
 */
class SpeakerAnimatable : public IAnimatable
{
public:

    /**
     * @brief Construct a new Motor Animatable object
     * @param speaker the speaker to play on
     */
    SpeakerAnimatable(Speaker& speaker);

    /**
     * @brief Instruct the speaker to do a specific action
     * 
     * @param instruction The instruction are "Play" to play the current song and ""
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
    Speaker& speaker;
};

#endif