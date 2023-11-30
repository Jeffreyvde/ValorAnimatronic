#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include <stdint.h>
#include "Timeline.h"
#include "IAnimatable.h"

/**
 * @brief A class that represents an animation
 * 
 */
class Animation
{
public:
    /**
     * @brief Construct a new Animation object
     * 
     * @param timelines The timelines for the animation components
     * @param animationComponents The components for the timeline
     * @param components The amount of components. Should be the length of both arrays.
     */
    Animation(Timeline timelines[], IAnimatable animationComponents[], uint16_t components);

    /**
     * @brief Play the animation. If the animation is already playing this is ignored.
     * 
     */
    void Play(); 

    /**
     * @brief Tick so that it can be checked if our delay has been reached
     * 
     */
    void Tick();

    /**
     * @brief Stop the animation. The animation is reset.
     * 
     */
    void Stop();

    /**
     * @brief Is the animation still playing?
     * 
     * @return true Yes it is 
     * @return false No it is not
     */
    bool IsBusy() const;
private:
    
    /**
     * @brief Reset the state of the animation to zero.
     * 
     */
    void Reset();

    /**
     * @brief Set the Component Delay object delay
     * 
     * @param componentIndex Which component to set the array for
     */
    void SetComponentDelay(uint16_t componentIndex);

    /**
     * @brief Set the next instruction for a component
     * 
     * @param componentIndex Which component to set the array for
     */
    void NextComponentInstruction(uint16_t componentIndex);

    Timeline* timelines;
    IAnimatable* animationComponents; 
    uint16_t components;

    uint16_t* currentSteps;
    bool started = false;
};

#endif