#include "Animation.h"
#include "Arduino.h"

Animation::Animation(Timeline timelines[], IAnimatable* animationComponents[], uint16_t components)
    : timelines(timelines)
    , animationComponents(animationComponents)
    , components(components)

{
    animationSteps = (AnimationElementData*)malloc(sizeof(AnimationElementData) * components);
    Reset();
}

Animation::~Animation()
{
    free(animationSteps);
    animationSteps = nullptr;
}

void Animation::Play()
{
    if(started)
    {
        return;
    }
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
        animationSteps[i] = {0, AnimationState::Waiting, millis() + timelines[i].values[0].delay};
    }
}

void Animation::StartComponentInstruction(uint16_t componentIndex)
{
    uint16_t step = animationSteps[componentIndex].step;
    animationComponents[componentIndex]->Start(timelines[componentIndex].values[step].instruction);
    animationSteps[componentIndex].state = AnimationState::Active;
}

void Animation::SetInstructionDelay(uint16_t componentIndex)
{
    AnimationElementData* data = &animationSteps[componentIndex]; 

    const unsigned long currentTime = millis();
    const TimelineValue value = timelines[componentIndex].values[data->step];
    data->animationActivationTime = currentTime + value.delay;
    data->animationEndTime = currentTime + value.maxDuration;
    data->state = AnimationState::Waiting;
}

bool Animation::AtLastStep(uint16_t componentIndex) const
{
    return animationSteps[componentIndex].step >= timelines[componentIndex].length;
}
