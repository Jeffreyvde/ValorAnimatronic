#ifndef TIMELINES_H
#define TIMELINES_H

#pragma once

#include "animation/TimeLIneValue.h"
#include <vector>

std::vector<TimelineValue> baseAnimationValuesHead = {{"0", 3000, 0}, {"180", 3000, 0}, {"90", 3000, 0}};
std::vector<TimelineValue> baseAnimationValuesWing =  {{"110", 0, 0}, {"140", 2000, 0}, {"180", 500, 0}, {"110", 3000, 0}, {"140", 2000, 0}, {"180", 500, 0}};
std::vector<TimelineValue> baseAnimationValuesSpeaker =  {{"1", 0, 0}, {"1", 5000, 0}};

std::vector<const std::vector<TimelineValue>&> baseAnimationTimeline = {baseAnimationValuesHead, baseAnimationValuesWing, baseAnimationValuesSpeaker};

std::vector<TimelineValue> secondAnimationValuesHead = {{"45", 0, 2000}, {"135", 0, 2000}, {"45", 0, 500}, {"135", 0, 500}, {"45", 0, 500}, {"135", 0, 500}};
std::vector<TimelineValue> secondAnimationValuesWing =  {{"110", 4000, 2000}, {"180", 500, 2000}};
std::vector<TimelineValue> secondAnimationValuesSpeaker =  {{"1", 3500, 0}, {"1", 1500, 0}};

std::vector<const std::vector<TimelineValue>&> secondAnimationTimeline = {secondAnimationValuesHead, secondAnimationValuesWing, secondAnimationValuesSpeaker};

std::vector<TimelineValue> thirdAnimationValuesHead = {{"180", 4000, 500}, {"135", 0, 500}, {"90", 0, 500}, {"45", 0, 500}, {"45", 0, 500}, {"135", 0, 500}};
std::vector<TimelineValue> thirdAnimationValuesWing =  {{"110", 0, 2000}, {"180", 500, 2000}, {"110", 0, 2000}, {"180", 500, 2000}};
std::vector<TimelineValue> thirdAnimationValuesSpeaker =  {{"1", 0, 0}, {"1", 4000, 0}, {"1", 1000, 0}};

std::vector<const std::vector<TimelineValue>&> thirdAnimationTimeline = {thirdAnimationValuesHead, thirdAnimationValuesWing, thirdAnimationValuesSpeaker};

#endif