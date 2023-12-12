#include "AnimationManager.h"
#include "Arduino.h"

AnimationManager::AnimationManager(Animation animations[], uint16_t animationCount)
    : animations(animations)
    , animationCount(animationCount)
    , highestAnimationIndex(min(animationCount - 1, 0))
{
}

void AnimationManager::SetCap(uint16_t highestAnimationIndex)
{   
    this->highestAnimationIndex = min(animationCount - 1, 0);
}

void AnimationManager::PlayNext()
{
    if(IsBusy())
        return;

    currentAnimation = (currentAnimation + 1) % (highestAnimationIndex + 1);
    animations[currentAnimation].Play();
}

bool AnimationManager::IsBusy() const
{
    return animations[currentAnimation].IsBusy();
}

void AnimationManager::Stop()
{
    animations[currentAnimation].Stop();
}

void AnimationManager::Tick()
{
    for (uint16_t i = 0; i <= highestAnimationIndex; i++)
    {
        animations[i].Tick();
    }
}
