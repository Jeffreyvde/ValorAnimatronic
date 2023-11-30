#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#pragma once

#include "Animation.h"
#include <stdint.h>

class AnimationManager
{
public:
    /**
     * @brief Construct a new Animation Manager object
     * 
     * @param animations The animations it can play
     * @param animationCount The animation count
     */
    AnimationManager(Animation animations[], uint16_t animationCount);

    /**
     * @brief Set a cap for what animations we allow. The default is animationCount -1.
     * 
     * @param highestAnimationIndex The maximum index (inclusive) starting at zero
     */
    void SetCap(uint16_t highestAnimationIndex);

    /**
     * @brief Play the next animation. When an animation is already running it 
     * 
     */
    void PlayNext();
    
    /**
     * @brief 
     * 
     * @return true when an animation is playing
     * @return false when nothing is playing
     */
    bool IsBusy() const;

    /**
     * @brief Stop the current animation
     * 
     */
    void Stop();

    /**
     * @brief To instruct underlying animations
     * 
     */
    void Tick();
private:
    Animation* animations;
    uint16_t animationCount;
    uint16_t highestAnimationIndex;
    uint16_t currentAnimation = 0; 
};

#endif