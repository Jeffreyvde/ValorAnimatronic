#ifndef TIMELINES_H
#define TIMELINES_H

#pragma once

#include "animation/TimeLineValue.h"
#include "animation/TimeLine.h"
#include <vector>

std::vector<TimeLineValue> baseAnimationValuesHead = {{"0", 3000, 0}, {"180", 3000, 0}, {"90", 3000, 0}};
std::vector<TimeLineValue> baseAnimationValuesWing =  {{"110", 0, 0}, {"140", 2000, 0}, {"180", 500, 0}, {"110", 3000, 0}, {"140", 2000, 0}, {"180", 500, 0}};
std::vector<TimeLineValue> baseAnimationValuesSpeaker =  {{"1", 0, 0}, {"1", 5000, 0}};

std::vector<TimeLine> baseAnimationTimeline = {baseAnimationValuesHead, baseAnimationValuesWing, baseAnimationValuesSpeaker};

std::vector<TimeLineValue> secondAnimationValuesHead = {{"45", 0, 2000}, {"135", 0, 2000}, {"45", 0, 500}, {"135", 0, 500}, {"45", 0, 500}, {"135", 0, 500}};
std::vector<TimeLineValue> secondAnimationValuesWing =  {{"110", 4000, 2000}, {"180", 500, 2000}};
std::vector<TimeLineValue> secondAnimationValuesSpeaker =  {{"1", 3500, 0}, {"1", 1500, 0}};

std::vector<TimeLine> secondAnimationTimeline = {secondAnimationValuesHead, secondAnimationValuesWing, secondAnimationValuesSpeaker};

std::vector<TimeLineValue> thirdAnimationValuesHead = {{"180", 4000, 500}, {"135", 0, 500}, {"90", 0, 500}, {"45", 0, 500}, {"45", 0, 500}, {"135", 0, 500}};
std::vector<TimeLineValue> thirdAnimationValuesWing =  {{"110", 0, 2000}, {"180", 500, 2000}, {"110", 0, 2000}, {"180", 500, 2000}};
std::vector<TimeLineValue> thirdAnimationValuesSpeaker =  {{"1", 0, 0}, {"1", 4000, 0}, {"1", 1000, 0}};

std::vector<TimeLine> thirdAnimationTimeline = {thirdAnimationValuesHead, thirdAnimationValuesWing, thirdAnimationValuesSpeaker};

#endif