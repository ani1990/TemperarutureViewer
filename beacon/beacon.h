/*
 SparkFun Si7021 Temperature and Humidity Breakout 
 By: Giriraj Pawar
 TU Chemnitz
 Date: 22/09/2019
 */

#ifndef SparkFun_Si7021_Breakout_Library_h
#define SparkFun_Si7021_Breakout_Library_h

#include <Arduino.h>
#include "HardwareSerial.h"

/****************Si7021 & HTU21D Definitions***************************/

#define ADDRESS      0x40

#define TEMP_MEASURE_HOLD  0xE3
#define HUMD_MEASURE_HOLD  0xE5
#define TEMP_MEASURE_NOHOLD  0xF3
#define HUMD_MEASURE_NOHOLD  0xF5
#define TEMP_PREV   0xE0

#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE

#define HTRE        0x02
#define _BV(bit) (1 << (bit))

#define CRC_POLY 0x988000 // Shifted Polynomial for CRC check

// Error codes
#define I2C_TIMEOUT_LOCAL 	998
#define BAD_CRC		999


/****************Si7021 & HTU21D Class**************************************/
class Weather
{
public:
	// Constructor
	Weather();

	void  begin();

	// Si7021 & HTU21D Public Functions
	float getRH();
	float readTemp();
	float getTemp();
	float readTempF();
	float getTempF();
	void  heaterOn();
	void  heaterOff();
	void  changeResolution(uint8_t i);
	void  reset();
	uint8_t  checkID();



private:
	//Si7021 & HTU21D Private Functions
	uint16_t makeMeasurment(uint8_t command);
	void     writeReg(uint8_t value);
	uint8_t  readReg();
};

#endif
