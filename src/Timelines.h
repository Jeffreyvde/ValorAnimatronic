#ifndef TIMELINES_H
#define TIMELINES_H

#pragma once

#include "animation/Animation.h"

TimelineValue baseAnimationValuesHead[] = {{"0", 3000, 0}, {"180", 3000, 0}, {"90", 3000, 0}};
TimelineValue baseAnimationValuesWing[] =  {{"110", 0, 0}, {"140", 2000, 0}, {"180", 500, 0}, {"110", 3000, 0}, {"140", 2000, 0}, {"180", 500, 0}};
TimelineValue baseAnimationValuesSpeaker[] =  {{"1", 0, 0}, {"1", 5000, 0}};

Timeline baseAnimationTimelineHead = {sizeof(baseAnimationValuesHead) / sizeof(TimelineValue), baseAnimationValuesHead};
Timeline baseAnimationTimelineWing = {sizeof(baseAnimationValuesWing) / sizeof(TimelineValue), baseAnimationValuesWing};
Timeline baseAnimationTimelineSpeaker = {sizeof(baseAnimationValuesSpeaker) / sizeof(TimelineValue), baseAnimationValuesSpeaker};
Timeline baseAnimationTimeline[] = {baseAnimationTimelineHead, baseAnimationTimelineWing, baseAnimationTimelineSpeaker};


TimelineValue secondAnimationValuesHead[] = {{"80", 1000, 2000},{"70", 0, 2000},{"60", 0, 2000},{"50", 0, 2000},{"40", 0, 2000}, {"30", 0, 2000}, {"20", 0, 2000}, {"10", 0, 2000}, {"0", 0, 2000}};
TimelineValue secondAnimationValuesWing[] =  {{"110", 1000, 2000}, {"140", 2000, 0}, {"180", 500, 0}, {"110", 3000, 0}, {"140", 2000, 0}, {"180", 500, 0}};
TimelineValue secondAnimationValuesSpeaker[] =  {{"1", 0, 0}, {"1", 5000, 0}};


Timeline secondAnimationTimelineHead = {sizeof(secondAnimationValuesHead) / sizeof(TimelineValue), secondAnimationValuesHead};
Timeline secondAnimationTimelineWing = {sizeof(secondAnimationValuesWing) / sizeof(TimelineValue), secondAnimationValuesWing};
Timeline secondAnimationTimelineSpeaker = {sizeof(secondAnimationValuesSpeaker) / sizeof(TimelineValue), secondAnimationValuesSpeaker};
Timeline secondAnimationTimeline[] = {secondAnimationTimelineHead, secondAnimationTimelineWing, secondAnimationTimelineSpeaker};

#endif