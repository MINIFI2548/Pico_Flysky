#include <sys/_stdint.h>
#include "SerialUSB.h"
#include<Arduino.h>
#include"Pico_Flysky.h"
#include "RPi_Pico_TimerInterrupt.h"

void Pico_Flysky :: begin(HardwareSerial &serial) { 
  this -> stream = &serial;
  serial.begin(115200); 
}

void Pico_Flysky :: test(){
  byte buffer = stream -> read(); 
  if(buffer == PROTOCOL_LENGTH) { 
    Serial.println(buffer);
  }
}

void Pico_Flysky :: update(){ 
  uint32_t now = millis();
  // if (now - last >= PROTOCOL_TIMEGAP){
    byte buf = stream -> read(); 
    if(buf == PROTOCOL_LENGTH) { 
      len = buf - PROTOCOL_OVERHEAD;
      // Serial.println(buf, HEX);
      for(uint8_t ptr = 0 ; ptr < len ; ptr +=1){
        byte buf = stream -> read(); 
        buffer[ptr] = buf;
      }
      for (uint8_t i = 1; i < PROTOCOL_CHANNELS * 2 + 1; i += 2) {
        channel[i / 2] = buffer[i] | (buffer[i + 1] << 8);
        if ((channel[i / 2] > 990) && (channel[i / 2] < 2010)){
          channelLastValue[i / 2] = channel[i / 2];
        }
        else {
          channel[i / 2] = channelLastValue[i / 2];
        }
        // Serial.println(channel[i / 2]);
      }
      // Serial.println();
    }
    last = now;
  // }
}

int Pico_Flysky :: readChannel(uint8_t channelNr){
  if ((channelNr < PROTOCOL_CHANNELS) && (channel[channelNr] > 990) && (channel[channelNr] < 2010)) {
    return channel[channelNr];
  } else {
    return 0;
  }
}

int Pico_Flysky :: readChannel(uint8_t channelNr, int minValue, int maxValue){
  if ((channelNr < PROTOCOL_CHANNELS) && (channel[channelNr] > 990) && (channel[channelNr] < 2010)) {
    return map(channel[channelNr], 1000, 2000, minValue, maxValue);
  } else {
    return 0;
  }
}
