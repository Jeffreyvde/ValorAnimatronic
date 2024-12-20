#ifndef TIMELINEVALUE_H
#define TIMELINEVALUE_H

#pragma once

#define TIMELINE_BUFFER_SIZE 16

/**
 * @brief A value on the timeline
 * 
 */
struct TimelineValue
{
    char instruction[TIMELINE_BUFFER_SIZE]; // Instruction of max length 16 characters
    unsigned long delay; // Delay in milliseconds
    unsigned long maxDuration; // How long can the timeline value take
};

#endif