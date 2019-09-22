/******************************************************************************
  SparkFun Si7021 Breakout Example 
  Joel Bartlett @ SparkFun Electronics
  Original Creation Date: May 18, 2015
  Updated May 4, 2016
  This sketch prints the temperature and humidity the Serial port.

  The library used in this example can be found here:
  https://github.com/sparkfun/Si7021_Breakout/tree/master/Libraries

  Hardware Connections:
      HTU21D ------------- Photon
      (-) ------------------- GND
      (+) ------------------- 3.3V (VCC)
       CL ------------------- D1/SCL
       DA ------------------- D0/SDA

  Development environment specifics:
  	IDE: Particle Dev
  	Hardware Platform: SparkFun RedBoard
                       Arduino IDE 1.6.5

  This code is beerware; if you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful,
  please buy us a round!
  Distributed as-is; no warranty is given.
*******************************************************************************/
#include "SparkFun_Si7021_Breakout_Library.h"
#include "HardwareSerial.h"
#include <Wire.h>

#define RFCHANNEL        0       // Let's use channel 0
#define SYNCWORD1        0xB5    // Synchronization word, high byte
#define SYNCWORD0        0x47    // Synchronization word, low byte
#define SOURCE_ADDR      5       // Device address

float humidity = 0;
float tempC = 0;


int power = A3;
int GND = A2;

//Create Instance of HTU21D or SI7021 temp and humidity sensor and MPL3115A2 barrometric sensor
Weather sensor;

CCPACKET packet;

//---------------------------------------------------------------
void setup()
{
    Serial.begin(9600);   // open serial over USB at 9600 baud

    pinMode(power, OUTPUT);
    pinMode(GND, OUTPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(power, HIGH);
    digitalWrite(GND, LOW);

    

    //Initialize the I2C sensors and ping them
    sensor.begin();

    panstamp.radio.setChannel(RFCHANNEL);
  panstamp.radio.setSyncWord(SYNCWORD1, SYNCWORD0);
  panstamp.radio.setDevAddress(SOURCE_ADDR);
  panstamp.radio.setCCregs();
  panstamp.setHighTxPower();

  
  packet.length = 3;

}
//---------------------------------------------------------------
void loop()
{
    
    digitalWrite(LED, HIGH);
    //Get readings from all sensors
    getWeather();

    packet.data[0]= 21;
    packet.data[1]= 13;
    packet.data[2]= tempC; //read Temperature in celsius


    panstamp.radio.sendData(packet);

    digitalWrite(LED, LOW);
    printInfo();
    delay(1000);

}
//---------------------------------------------------------------
void getWeather()
{
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  tempC = sensor.getTemp();
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()
}
//---------------------------------------------------------------
void printInfo()
{
//This function prints the weather data out to the default Serial Port

  Serial.print("Temp:");
  Serial.print(tempC);
  Serial.print("C, ");
  Serial.print("\n");

  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println("%");
}
