#ifndef TIMELINE_H
#define TIMELINE_H

#pragma once

#include <stdint.h>
#include "TimeLineValue.h"

/**
 * @brief A timeline of values for an animation to follow
 * 
 */
struct Timeline
{
    uint16_t length;
    TimelineValue* values;    
};
#endif