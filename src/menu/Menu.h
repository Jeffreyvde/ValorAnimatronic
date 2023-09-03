#pragma once

#ifndef MENU_H
#define MENU_H

#include "Button.h"

class Menu
{
public:
    /**
     * @brief Construct a new Menu object
     *
     * @param changeStateButton Button to change the state
     * @param ledHeadStatePin Led pin that indicates the head state
     * @param ledRopeStatePin Led pin that indicates the rope state
     */
    Menu(Button& changeStateButton, uint8_t ledHeadStatePin, uint8_t ledRopeStatePin);

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
        Rope
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

    // State machine methods
    void OnAnimationStateTick();
    void OnHeadStateTick();
    void OnRopeStateTick();


    Button& changeButton;
    Button::ButtonState previousButtonState;

    MenuState state;

    uint8_t headStatePin;
    uint8_t ropeStatePin;


};

#endif