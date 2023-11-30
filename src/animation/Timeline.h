#ifndef TIMELINE_H
#define TIMELINE_H

#pragma once

#include <stdint.h>

#define TIMELINE_BUFFER_SIZE = 16;

struct TimelineValue
{
    char instruction[TIMELINE_BUFFER_SIZE];
    long long ticksDelay;
};

struct Timeline
{
    int length;
    TimelineValue* values;    
};
#endif