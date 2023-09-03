#include "Button.h"

Button::Button(const uint8_t buttonPin)
{
    pin = buttonPin;
}

void Button::SetUp()
{
    pinMode(pin, INPUT_PULLUP);
}

void Button::Tick()
{
    int pinState = digitalRead(pin);
    switch (state)
    {
    case ButtonState::NoPress:
        TickNoPressState(pinState);
        break;
    case ButtonState::StartPress:
        TickStartPressState(pinState);
        break;
    case ButtonState::Press:
        TickPressState(pinState);
        break;
    case ButtonState::LongPress:
        TickLongPressState(pinState);
        break;
    case ButtonState::EndPress:
        TickEndPressState(pinState);
        break;
    }
}

Button::ButtonState Button::GetState() const
{
    return state;
}

void Button::SetState(const ButtonState newState)
{
    state = newState;
}

void Button::SetDebounceTime()
{
    bounceOverTime = millis() + debounceDelay;
}

bool Button::IsDebounceOver() const
{
    return millis() > bounceOverTime;
}

void Button::CheckPressEnded(const int pinState)
{
    if (IsDebounceOver() && pinState == HIGH)
    {
        SetState(ButtonState::EndPress);
        SetDebounceTime();
    }
}

void Button::TickNoPressState(const int pinState)
{   
    if (IsDebounceOver() && pinState == LOW)
    {
        SetState(ButtonState::StartPress);
        SetDebounceTime();  
    }
}

void Button::TickStartPressState(const int pinState)
{
    SetState(ButtonState::Press);
    longPressTime = millis() + longPressDelay;
}

void Button::TickPressState(const int pinState)
{
    if(millis() > longPressTime)
    {
        SetState(ButtonState::LongPress);
    }
    CheckPressEnded(pinState);
}

void Button::TickLongPressState(const int pinState)
{
    CheckPressEnded(pinState);
}

void Button::TickEndPressState(const int pinState)
{
    SetState(ButtonState::NoPress);
}
