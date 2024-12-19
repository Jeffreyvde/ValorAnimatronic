#include "SpeakerAnimatable.h"

SpeakerAnimatable::SpeakerAnimatable(Speaker& speaker): speaker(speaker)
{
}

void SpeakerAnimatable::Start(const char instruction[])
{
    int value = atoi(instruction);
    speaker.Play(value);
}

bool SpeakerAnimatable::IsFinished()
{
    // Default to false as we dont know the servo state
    return false;
}

void SpeakerAnimatable::Stop()
{
    // Not supported for speaker currently
}
