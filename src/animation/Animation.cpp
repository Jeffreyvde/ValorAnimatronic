#include "Animation.h"
#include "Arduino.h"

Animation::Animation(Timeline timelines[], IAnimatable animationComponents[], uint16_t components)
{
}

void Animation::Play()
{
    if(IsBusy)
    {
        return;
    }



}

void Animation::Tick()
{
    for (uint16_t i = 0; i < components; i++)
    { 
        if()
    
    }

}

void Animation::Stop()
{
    for (uint16_t i = 0; i < components; i++)
    {
        animationComponents[i].Stop();
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
        if(timelines[i].length != currentSteps[i] || !animationComponents[i].IsFinished())
        {
            return false;
        }
    }
    return true;
}

void Animation::Reset()
{   
    for (uint16_t i = 0; i < components; i++)
    {
        currentSteps[i] = 0;
    }
}

void Animation::SetComponentDelay(uint16_t componentIndex)
{
    currentDelays[componentIndex] = millis() + timelines[componentIndex].values[currentSteps[componentIndex]].ticksDelay;
}

void Animation::NextComponentInstruction(uint16_t componentIndex)
{
    currentSteps[componentIndex]++;
}
