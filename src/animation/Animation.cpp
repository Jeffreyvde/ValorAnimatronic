#include "Animation.h"
#include "Arduino.h"

Animation::Animation(const std::vector<TimeLine> &timelines,
                     std::vector<std::reference_wrapper<IAnimatable>> animationComponents)
    : timelines(timelines), 
      animationComponents(animationComponents), 
      components(animationComponents.size()), 
      animationSteps(components)

{
    Reset();
}

void Animation::Play()
{
    if (started)
    {
        return;
    }
    Reset();
    started = true;
}

void Animation::Tick()
{
    if (!started)
    {
        return;
    }

    const unsigned long time = millis();
    for (uint16_t i = 0; i < components; i++)
    {
        AnimationElementData *data = &animationSteps.at(i);
        switch (data->state)
        {
        case AnimationState::Active:
            if (animationComponents.at(i).get().IsFinished() || time > data->animationEndTime)
            {
                data->step++;
                if (AtLastStep(i))
                {
                    data->state = AnimationState::Idle;
                    animationComponents.at(i).get().Stop();
                }
                else
                {
                    SetInstructionDelay(i);
                }
            }
            break;
        case AnimationState::Waiting:
            if (time > data->animationActivationTime)
            {
                StartComponentInstruction(i);
            }
            break;
        case AnimationState::Idle:
            // Wait
            break;
        }
    }

    if (!IsBusy())
    {
        started = false;
        Reset();
    }
}

void Animation::Stop()
{
    for (uint16_t i = 0; i < components; i++)
    {
        animationComponents.at(i).get().Stop();
    }
    Reset();
}

bool Animation::IsBusy() const
{
    if (!started)
    {
        return false;
    }

    for (uint16_t i = 0; i < components; i++)
    {
        if (!AtLastStep(i) || animationSteps.at(i).state != AnimationState::Idle)
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
        animationSteps.at(i) = {0, AnimationState::Waiting, millis() + timelines.at(i).at(0).delay};
    }
}

void Animation::StartComponentInstruction(uint16_t componentIndex)
{
    AnimationElementData *data = &animationSteps.at(componentIndex);
    uint16_t step = data->step;
    const TimeLineValue value = timelines.at(componentIndex).at(step);

    animationComponents.at(componentIndex).get().Start(timelines.at(componentIndex).at(step).instruction);
    data->animationEndTime = millis() + value.maxDuration;
    data->state = AnimationState::Active;
}

void Animation::SetInstructionDelay(uint16_t componentIndex)
{
    AnimationElementData *data = &animationSteps.at(componentIndex);

    const unsigned long currentTime = millis();
    const TimeLineValue value = timelines.at(componentIndex).at(data->step);
    data->animationActivationTime = currentTime + value.delay;

    data->state = AnimationState::Waiting;
}

bool Animation::AtLastStep(uint16_t componentIndex) const
{
    return animationSteps.at(componentIndex).step >= timelines.at(componentIndex).size();
}
