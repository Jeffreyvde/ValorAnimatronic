#ifndef SPEAKER_H
#define SPEAKER_H

#pragma once

#include <cstdint>
#include <Arduino.h>

/**
 * @brief A class to control a speaker device via serial communication.
 */
class Speaker
{
public:
    /**
     * @brief Construct a new Speaker object
     * 
     * @param serial Reference to a HardwareSerial object for communication to the speaker
     * @param volume Initial volume level for the speaker
     */
    Speaker(HardwareSerial& serial, uint8_t volume);

    /**
     * @brief Plays a sound with the specified volume
     * 
     * @param data The sound data or identifier to play
     */
    void Play(uint8_t data);

private:
    /**
     * @brief Sends a basic message with a single command
     * 
     * @param command The command byte to send
     */
    void SendBasicMessage(int8_t command);

    /**
     * @brief Sends a message with a command and one byte of data
     * 
     * @param command The command byte to send
     * @param dat The data byte to include in the message
     */
    void SendOneBytedataMessage(int8_t command, uint8_t dat);

    /**
     * @brief Sends a message with a command and two bytes of data
     * 
     * @param command The command byte to send
     * @param dat The two-byte data to include in the message
     */
    void SendTwoBytedataMessage(int8_t command, int16_t dat);

    /**
     * @brief Sends a message with the specified number of bytes
     * 
     * @param numberOfBytes The number of bytes in the message to send
     */
    void SendBytes(uint8_t numberOfBytes);

private:
    HardwareSerial& serial;
    uint8_t volume;         

    int8_t SendBuffer[6] = {0}; 

    static constexpr int8_t startingByte = 0x7e; 
    static constexpr int8_t endByte = 0xef;    

    static constexpr int8_t volumeCommands = 0X31; 
};

#endif
