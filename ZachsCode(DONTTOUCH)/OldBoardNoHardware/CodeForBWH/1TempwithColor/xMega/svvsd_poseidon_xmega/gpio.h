/******************************************************************************
 * gpio.h
 * This set of routines sets up all of the IO pins on the POSEIDON xmega.
 * This code will be needed on the submarine.  
 * 
 * Created: 12/29/2017 12:47:33 PM
 *  Author: Daniel Torres-Hernandez
********************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

/********************************************************************************
						Includes
********************************************************************************/
#include "poseidon.h"
#include <avr/io.h>

/********************************************************************************
						Macros and Defines
********************************************************************************/
#define xplained_yellow_LED_port PORTR_OUT
#define xplained_yellow_LED_0 0
#define xplained_yellow_LED_1 1
#define xplained_red_LED_port PORTD_OUT
#define xplained_red_LED 4

/********************************************************************************
						Function Prototypes
********************************************************************************/
void GPIO_init(void);

#endif /* GPIO_H_ */