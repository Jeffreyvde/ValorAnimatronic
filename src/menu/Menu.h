#ifndef MENU_H
#define MENU_H

#pragma once

#include "Button.h"
#include "Motor.h"
#include "animation/AnimationManager.h"

/**
 * @brief The menu for the Valor animatronic
 * 
 */
class Menu
{
public:
    /**
     * @brief Construct a new Menu object
     *
     * @param changeStateButton Button to change the state
     * @param animationManager The animation manager that holds the animations
     * @param headMotor The motor that controls the head mechanism
     * @param wingMotor The motor that controls the wing mechanism 
     * @param ledHeadStatePin Led pin that indicates the head state
     * @param ledRopeStatePin Led pin that indicates the rope state
     */
    Menu(Button& changeStateButton, AnimationManager& animationManager, Motor& headMotor, Motor& wingMotor, uint8_t ledHeadStatePin, uint8_t ledRopeStatePin);

    /**
     * @brief Set the Up for the Arduino
     *
     */
    void SetUp();

    /**
     * @brief Tick event for the menu
     *
     */
    void Tick();

private:
    /**
     * @brief The possible states of the menu
     *
     */
    enum class MenuState
    {
        Animation,
        Head,
        RopeForward,
        RopeBackward
    };

    /**
     * @brief Change the menu state
     * 
     * @param newState What state the menu should have
     */
    void SetState(MenuState newState);
    
    /**
     * @brief Get the next state
     * 
     */
    void GoToNextState();

    /**
     * @brief Handle the tick event for the animation state
     */
    void OnAnimationStateTick();

    /**
     * @brief Check if we should toggle the motor. Meant for either Rope state or Head state
     * 
     * @param forward Should the motor move forward or backward?
     * @param motor Which of the motors can toggle
     */
    void CheckMotorToggle(bool forward, Motor& motor);

    Button& changeButton;
    Button::ButtonState previousButtonState;

    AnimationManager& animationManager;

    Motor& headMotor; 
    Motor& wingMotor;

    MenuState state;

    uint8_t headStatePin;
    uint8_t ropeStatePin;

    bool active;
};

#endif