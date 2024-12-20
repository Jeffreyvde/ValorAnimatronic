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

TimelineValue secondAnimationValuesHead[] = {{"45", 0, 2000}, {"135", 0, 2000}, {"45", 0, 500}, {"135", 0, 500}, {"45", 0, 500}, {"135", 0, 500}};
TimelineValue secondAnimationValuesWing[] =  {{"110", 4000, 2000}, {"180", 500, 2000}};
TimelineValue secondAnimationValuesSpeaker[] =  {{"1", 3500, 0}, {"1", 1500, 0}};

Timeline secondAnimationTimelineHead = {sizeof(secondAnimationValuesHead) / sizeof(TimelineValue), secondAnimationValuesHead};
Timeline secondAnimationTimelineWing = {sizeof(secondAnimationValuesWing) / sizeof(TimelineValue), secondAnimationValuesWing};
Timeline secondAnimationTimelineSpeaker = {sizeof(secondAnimationValuesSpeaker) / sizeof(TimelineValue), secondAnimationValuesSpeaker};
Timeline secondAnimationTimeline[] = {secondAnimationTimelineHead, secondAnimationTimelineWing, secondAnimationTimelineSpeaker};

TimelineValue thirdAnimationValuesHead[] = {{"180", 4000, 500}, {"135", 0, 500}, {"90", 0, 500}, {"45", 0, 500}, {"45", 0, 500}, {"135", 0, 500}};
TimelineValue thirdAnimationValuesWing[] =  {{"110", 0, 2000}, {"180", 500, 2000}, {"110", 0, 2000}, {"180", 500, 2000}};
TimelineValue thirdAnimationValuesSpeaker[] =  {{"1", 0, 0}, {"1", 4000, 0}, {"1", 1000, 0}};

Timeline thirdAnimationTimelineHead = {sizeof(thirdAnimationValuesHead) / sizeof(TimelineValue), thirdAnimationValuesHead};
Timeline thirdAnimationTimelineWing = {sizeof(thirdAnimationValuesWing) / sizeof(TimelineValue), thirdAnimationValuesWing};
Timeline thirdAnimationTimelineSpeaker = {sizeof(thirdAnimationValuesSpeaker) / sizeof(TimelineValue), thirdAnimationValuesSpeaker};
Timeline thirdAnimationTimeline[] = {thirdAnimationTimelineHead, thirdAnimationTimelineWing, thirdAnimationTimelineSpeaker};

#endif