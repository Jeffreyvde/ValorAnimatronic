#include "AnimationManager.h"
#include "Arduino.h"

AnimationManager::AnimationManager(std::vector<Animation>& animations)
    : animations(animations)
    , animationCount(animations.size())
    , highestAnimationIndex(max(animationCount - 1, 0))
{
}

void AnimationManager::SetCap(uint16_t highestAnimationIndex)
{   
    this->highestAnimationIndex = min(animationCount - 1, 0);
}

void AnimationManager::PlayNext()
{
    if(IsBusy())
    {
        return;
    }
    
    animations.at(currentAnimation).Play();
    currentAnimation = (currentAnimation + 1) % (highestAnimationIndex + 1);
}

bool AnimationManager::IsBusy() const
{
    return animations[currentAnimation].IsBusy();
}

void AnimationManager::Stop()
{
    animations.at(currentAnimation).Stop();
}

void AnimationManager::Tick()
{
    for (uint16_t i = 0; i <= highestAnimationIndex; i++)
    {
        animations.at(i).Tick();
    }
}
