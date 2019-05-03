/******************************************************************************
 * colorSensor.h
 * This set of defines and routines is in support of the TCS3472 color light
 * sensor, specifically the breakout board from AdaFruit.  This code will be 
 * needed for the Poseidon project (surface board and submarine) and the
 * upcoming St Vrain Valley Light Projects.
 * 
 * Created: 12/29/2017 12:47:33 PM
 *  Author: craig
********************************************************************************/
#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

/********************************************************************************
						Includes
********************************************************************************/
#include "twi_master_driver.h"

/********************************************************************************
						Macros and Defines
********************************************************************************/
// =========== TCS34725 RGB SENSOR DEFINES =====================
#define TEMPERATURE_REGISTER 0x00
#define CONFIG_REGISTER 0x01
#define T_LOW_REGISTER 0x02
#define T_HIGH_REGISTER 0x03

/********************************************************************************
						Global Variables
********************************************************************************/
uint16_t raw_clear, raw_red, raw_green, raw_blue;

/********************************************************************************
						Function Prototypes
********************************************************************************/
void xmega_TEMPsensor_init(void);
unsigned char xmega_read_TEMP_values(void);

#endif /* COLORSENSOR_H_ */