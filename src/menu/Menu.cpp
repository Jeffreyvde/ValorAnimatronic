#include "Menu.h"

Menu::Menu(Button &changeStateButton, uint8_t ledHeadStatePin, uint8_t ledRopeStatePin)
    : changeButton(changeStateButton),
      headStatePin(ledHeadStatePin),
      ropeStatePin(ledRopeStatePin)

{
}

void Menu::SetUp()
{
    changeButton.SetUp();
    pinMode(headStatePin, OUTPUT);
    pinMode(ropeStatePin, OUTPUT);
}

void Menu::Tick()
{
    changeButton.Tick();
    const auto buttonState = changeButton.GetState();
    if (previousButtonState != buttonState)
    {
        Serial.println((int)buttonState);
        if (buttonState == Button::ButtonState::LongPress)
        {
            GoToNextState();
        }
        previousButtonState = buttonState;
    }

    switch (state)
    {
    case MenuState::Animation:
        OnAnimationStateTick();
        break;
    case MenuState::Head:
        OnHeadStateTick();
        break;
    case MenuState::Rope:
        OnRopeStateTick();
        break;
    }
}

void Menu::SetState(MenuState newState)
{
    state = newState;

    digitalWrite(headStatePin, (state == MenuState::Head) ? HIGH : LOW);
    digitalWrite(ropeStatePin, (state == MenuState::Rope) ? HIGH : LOW);
    Serial.println((int)state);
}

void Menu::GoToNextState()
{
    switch (state)
    {
    case MenuState::Animation:
        SetState(MenuState::Head);
        break;
    case MenuState::Head:
        SetState(MenuState::Rope);
        break;
    case MenuState::Rope:
        SetState(MenuState::Animation);
        break;
    }
}

void Menu::OnAnimationStateTick()
{
}

void Menu::OnHeadStateTick()
{
}

void Menu::OnRopeStateTick()
{
}
