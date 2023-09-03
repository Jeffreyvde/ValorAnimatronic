#pragma once

#ifndef Button_H
#define Button_H

#include <Arduino.h>

/**
 * @brief Class representation of a basic Arduino Button
 * 
 */
class Button
{
public:
 /**
 * @brief The possible states of the button
 * 
 */
  enum class ButtonState
  {
    NoPress,
    StartPress,
    Press,
    LongPress,
    EndPress
  };


  /**
   * @brief Initialize a button and the corresponding pin
   *  
   * @param buttonPin The pin that has to be checked 
   */
  Button(uint8_t buttonPin);

  /**
   * @brief Set Up the button pin mode 
   * 
   */
  void SetUp();

  /*
  * Update the internal state for the button.
  */
  void Tick();

  /**
   * @brief Get the State of the button
   * 
   * @return The current state of the button
   */
  Button::ButtonState GetState() const;

private:


  /**
   * @brief Set the State the button
   * 
   * @param state What the state should now be
   */
  void SetState(ButtonState state);

/**
 * @brief Set the Debounce Time that we should not check for a different state
 * 
 */
  void SetDebounceTime();  

  /**
   * @brief Check if the debouncing is over
   * 
   * @return true If debounce is over
   * @return false If it is still going on
   */
  bool IsDebounceOver() const;

  /**
   * @brief Check if the button is no longer pressed and handle it if no longer pressed
   */
  void CheckPressEnded(int pinState);

  // State ticks
  void TickNoPressState(int pinState);
  void TickStartPressState(int pinState);
  void TickPressState(int pinState);
  void TickLongPressState(int pinState);
  void TickEndPressState(int pinState);

  uint8_t pin;
  ButtonState state = ButtonState::NoPress;

  unsigned long bounceOverTime = 0;
  const unsigned long debounceDelay = 50;

  unsigned long longPressTime = 0;
  const unsigned long longPressDelay = 1000;
};
#endif