#include "Menu.h"

Menu::Menu(Button &changeStateButton, Motor &headMotor, Motor &wingMotor, uint8_t ledHeadStatePin, uint8_t ledRopeStatePin)
    : changeButton(changeStateButton),
      headMotor(headMotor),
      wingMotor(wingMotor),
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

    switch (state)
    {
    case MenuState::Animation:
        OnAnimationStateTick();
        break;
    case MenuState::Head:
        CheckMotorToggle(true, headMotor);
        break;
    case MenuState::RopeForward:
        CheckMotorToggle(true, wingMotor);
        break;
    case MenuState::RopeBackward:
        CheckMotorToggle(false, wingMotor);
        break;
    }

    const auto buttonState = changeButton.GetState();
    if (previousButtonState != buttonState)
    {
        if (buttonState == Button::ButtonState::EndPress && previousButtonState == Button::ButtonState::LongPress)
        {
            GoToNextState();
        }
        previousButtonState = buttonState;
    }
}

void Menu::SetState(MenuState newState)
{
    state = newState;

    digitalWrite(headStatePin, (state == MenuState::Head || state == MenuState::RopeBackward) ? HIGH : LOW);
    digitalWrite(ropeStatePin, (state == MenuState::RopeForward || state == MenuState::RopeBackward) ? HIGH : LOW);
    headMotor.Stop();
    wingMotor.Stop();
}

void Menu::GoToNextState()
{
    switch (state)
    {
    case MenuState::Animation:
        SetState(MenuState::Head);
        break;
    case MenuState::Head:
        SetState(MenuState::RopeForward);
        break;
    case MenuState::RopeForward:
        SetState(MenuState::RopeBackward);
        break;
    case MenuState::RopeBackward:
        SetState(MenuState::Animation);
        break;
    }
}

void Menu::OnAnimationStateTick()
{
}

void Menu::CheckMotorToggle(bool forward, Motor &motor)
{
    if (changeButton.GetState() == Button::ButtonState::EndPress)
    {
        if (motor.IsActive())
        {
            motor.Stop();
        }
        else
        {
            constexpr int slowMovementMotor = 50;
            motor.SetSpeed(forward, slowMovementMotor);
        }
    }
}