/*
 * modem.ino
 *
 * Copyright (c) 2019 Giriraj Pawar <giriraj.pawar2012@gmail.com>
 * 
 * This file is part of the project embedded system lab. 
 * 
 * Author: Giriraj Pawar
 * Creation date: 22/09/2019
 *
 * Device:
 * Serial gateway or modem
 *
 */

#include "modem.h"


/**
 * LED pin
 */
#define LEDPIN  4



/**
 * This function is called whenever a wireless packet is received
 */
void rfPacketReceived(CCPACKET *packet)
{
  if (packet->length > 0)
  {
   // Serial.println("Actual Packet \n");
   // Serial.println(packet->data[2]);
    rxPacket = packet;
    packetAvailable = true;
  }
}

/**
 * setup
 * Arduino setup function
 */
void setup()
{
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  
  Serial.begin(9600);
  Serial.flush();
  Serial.println("");
  
  // Default mode is COMMAND 
  // Serial.println("Modem ready!");

  // Disable address check from the RF IC
  // panstamp.radio.disableAddressCheck();
     
  panstamp.radio.setDevAddress(21);
  
  // Declare RF callback function
  panstamp.attachInterrupt(rfPacketReceived);
  
  digitalWrite(LEDPIN, LOW);
}

/**
 * loop
 *
 * Arduino main loop
 */

void loop()
{
  // Read wireless packet 
  if (packetAvailable)
  {
    digitalWrite(LEDPIN, HIGH);
    // Disable wireless reception
    panstamp.rxOff();

    byte i; 
    packetAvailable = false;

    if (serMode == SERMODE_DATA)
    {
    
     // Serial.println("Data in the packet\n");
      for(i=0 ; i<rxPacket->length ; i++)
      {
        if (rxPacket->data[i] < 10)
        {
          Serial.print(0, DEC);    // Leading zero
        }
        Serial.print(rxPacket->data[i], DEC);  
      }
      Serial.print("\n");
      Serial.flush();
      panstamp.sleepSec(1);
    }

    // Enable wireless reception
    panstamp.rxOn();
    digitalWrite(LEDPIN, LOW);
  }

}
