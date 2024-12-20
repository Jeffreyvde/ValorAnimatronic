#include "Animation.h"
#include "Arduino.h"

Animation::Animation(const std::vector<TimeLine>& timelines, IAnimatable* animationComponents[], uint16_t components)
    : timelines(timelines)
    , animationComponents(animationComponents)
    , components(components)

{
    animationSteps = (AnimationElementData*)malloc(sizeof(AnimationElementData) * components);
    Reset();
}

void Animation::Play()
{
    if(started)
    {
        return;
    }
    Reset();
    started = true;
}

void Animation::Tick()
{
    if(!started)
    {
        return;
    }

    const unsigned long time = millis();
    for (uint16_t i = 0; i < components; i++)
    { 
        AnimationElementData* data = &animationSteps[i];
        switch (data->state)
        {
        case AnimationState::Active:
            if(animationComponents[i]->IsFinished() || time > data->animationEndTime)
            {
                data->step++; 
                if(AtLastStep(i))
                {
                    data->state = AnimationState::Idle;
                    animationComponents[i]->Stop();
                }
                else
                {
                    SetInstructionDelay(i);
                }
            }
            break;
        case AnimationState::Waiting:
            if(time > data->animationActivationTime)
            {
                StartComponentInstruction(i);
            }
            break;
        case AnimationState::Idle:
            // Wait
            break;
        }
    }
    
    if(!IsBusy())
    {
        started = false;
        Reset();
    }
}

void Animation::Stop()
{
    for (uint16_t i = 0; i < components; i++)
    {
        animationComponents[i]->Stop();
    }
    Reset();
}

bool Animation::IsBusy() const
{
    if(!started)
    {
        return false;
    }

    for (uint16_t i = 0; i < components; i++)
    {
        if(!AtLastStep(i) || animationSteps[i].state != AnimationState::Idle)
        {
            return true;
        }
    }
    return false;
}

void Animation::Reset()
{   
    started = false;
    for (uint16_t i = 0; i < components; i++)
    { 
        animationSteps[i] = {0, AnimationState::Waiting, millis() + timelines.at(i).at(0).delay};
    }
}

void Animation::StartComponentInstruction(uint16_t componentIndex)
{
    AnimationElementData* data = &animationSteps[componentIndex]; 
    uint16_t step = data->step;
    const TimeLineValue value = timelines.at(componentIndex).at(step);

    animationComponents[componentIndex]->Start(timelines.at(componentIndex).at(step).instruction);
    data->animationEndTime = millis() + value.maxDuration;
    data->state = AnimationState::Active;
}

void Animation::SetInstructionDelay(uint16_t componentIndex)
{
    AnimationElementData* data = &animationSteps[componentIndex]; 

    const unsigned long currentTime = millis();
    const TimeLineValue value = timelines.at(componentIndex).at(data->step);
    data->animationActivationTime = currentTime + value.delay;
    
    data->state = AnimationState::Waiting;
}

bool Animation::AtLastStep(uint16_t componentIndex) const
{
    return animationSteps[componentIndex].step >= timelines.at(componentIndex).size();
}
