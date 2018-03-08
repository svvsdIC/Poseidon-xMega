/******************************************************************************
 * FakeSensor1.c
 * 
 * This routine creates and returns a string value corresponding to a typical
 * water quality sensor.  This first one simulates the Dissolved Oxygen sensor.
 * Each call updates the current value.  Suggest calling this routine once per 
 * second.
 *
 * Created:3/8/2018 2:50:50 PM
 * Author : Craig / Zach
********************************************************************************/
#ifndef FAKESENSOR1_H_
#define FAKESENSOR1_H_
/********************************************************************************
						Includes
********************************************************************************/
#include <avr/io.h>
#include "poseidon.h"
//#include <avr/interrupt.h>
//#include <stdio.h>
//#include <string.h>

/********************************************************************************
						Macros and Defines
********************************************************************************/

/********************************************************************************
						Global Variables
********************************************************************************/

/********************************************************************************
						Function Prototypes
********************************************************************************/
//  Initialize the fake sensor initial readings and slope
void DO_init(void);
// Return a string for each sensor reading.  The string should be 32 characters.
void DO_read(char* DO_string);

#endif /* FAKESENSOR1_H_ */