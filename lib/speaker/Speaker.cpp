#include "Speaker.h"
#include <Arduino.h>

Speaker::Speaker(HardwareSerial &serial, uint8_t volume) : 
                 serial(serial), 
                 volume(volume)
{
}

void Speaker::SendBasicMessage(int8_t command)
{
  SendBuffer[0] = startingByte;
  SendBuffer[1] = 0x02; 
  SendBuffer[2] = command;
  SendBuffer[3] = endByte;
  SendBytes(4);
}

void Speaker::SendOneBytedataMessage(int8_t command, uint8_t dat)
{
  SendBuffer[0] = startingByte;
  SendBuffer[1] = 0x03; 
  SendBuffer[2] = command;
  SendBuffer[3] = dat;  
  SendBuffer[4] = endByte; 
  SendBytes(5);
}

void Speaker::SendTwoBytedataMessage(int8_t command, int16_t dat)
{
  SendBuffer[0] = startingByte; 
  SendBuffer[1] = 0x04; 
  SendBuffer[2] = command;
  SendBuffer[3] = (int8_t)(dat >> 8); 
  SendBuffer[4] = (int8_t)(dat);     
  SendBuffer[5] = endByte; 
  SendBytes(6);
}

void Speaker::SendBytes(uint8_t nbytes)
{
  for (uint8_t i = 0; i < nbytes; i++) 
  {
    serial.write(SendBuffer[i]);
  }
}

void Speaker::Play(uint8_t data)
{
  uint16_t mesage = volume << 8  | data; // Message is formatetted like: 0xvvtt where vv is volume and tt is track
  SendTwoBytedataMessage(volumeCommands, mesage); 
}