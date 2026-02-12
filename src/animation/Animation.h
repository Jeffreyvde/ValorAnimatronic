#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include "IAnimatable.h"
#include "TimeLineValue.h"
#include "TimeLine.h"
#include <vector>
#include <functional>

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
     */
    Animation(const std::vector<TimeLine>& timelines, 
              std::vector<std::reference_wrapper<IAnimatable>> animationComponents);

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
     * @brief The state of animation element
     * 
     */
    enum class AnimationState
    {
        /**
         * @brief Waiting for the animation to start
         * 
         */
        Waiting,

        /**
         * @brief The animation element is currently getting to the location
         * 
         */
        Active,
        /**
         * @brief The animation element is finished and ready for a new instruction
         * 
         */
        Idle
    };


    /**
     * @brief What Animation element is this step on
     * 
     */
    struct AnimationElementData
    {
        uint16_t step;
        AnimationState state;
        unsigned long animationActivationTime;
        unsigned long animationEndTime;
    };
    
    /**
     * @brief Reset the state of the animation to zero.
     * 
     */
    void Reset();

    /**
     * @brief Set the next instruction for a component
     * 
     * @param componentIndex Which component to set the instruction for
     */
    void StartComponentInstruction(uint16_t componentIndex);

    /**
     * @brief Set the instructions delay
     * 
     * @param componentIndex Which to set the delay for
     */
    void SetInstructionDelay(uint16_t componentIndex);

    /**
     * @brief Is a component at the last step
     * 
     * @param componentIndex Which component to check
     * @return true The component is at its last step
     * @return false The component has steps left
     */
    bool AtLastStep(uint16_t componentIndex) const;

    const std::vector<TimeLine>& timelines;
    std::vector<std::reference_wrapper<IAnimatable>> animationComponents; 
    uint16_t components;
    std::vector<AnimationElementData> animationSteps;
    
    bool started = false;
};

#endif