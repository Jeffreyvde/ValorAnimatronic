
#ifndef TIMELINE_VALUE_H
#define TIMELINE_VALUE_H

# pragma once

#include <string>

/**
 * @brief A value on the timeline
 * 
 */
struct TimelineValue
{
    const std::string& instruction; // Instruction
    unsigned long delay; // Delay in milliseconds
    unsigned long maxDuration; // How long can the timeline value take

    /**
     * Initialize a time line value
     * @param instruction the instruction for the robot
     * @param delay the delay in milliseconds
     * @param maxDuration the maximum duration of the animation in milliseconds
     */
    TimelineValue(const std::string& instruction, unsigned long delay, unsigned long maxDuration) 
         : instruction(instruction), delay(delay), maxDuration(maxDuration)
    {

    }
};
#endif