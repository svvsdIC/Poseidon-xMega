/********************************************************************************
 * poseidon.h
 *
 * This header file contains some global definitions
 * 
 * Created: 8/16/2017 11:15:27 AM
 * Author: Craig R
 *******************************************************************************/ 
#ifndef POSEIDON_H_
#define POSEIDON_H_

/********************************************************************************
						Includes
********************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "twi_master_driver.h"
#include "twiForPoseidon.h"
#include "colorSensor.h"
#include "clocks_and_counters.h"
#include "xmega_uarte0.h"
#include "gpio.h"
#include "FakeSensor1.h"
//#include "motors.h"
#include "ADC.h"

/********************************************************************************
						Macros and Defines
********************************************************************************/
#define SetBit(port,bit)	port |= (1<<bit)	// macro to set a register bit to 1
#define ClearBit(port,bit)	port &= ~(1<<bit)	// macro to set a register bit to 0
#define ToggleBit(port,bit)	port ^= (1<<bit)	// macro to toggle a register bit
#define BitIsSet(port, bit) (port & (1 << bit)) //tests a bit
#define BitIsClear(port, bit) (!(port & (1 << bit)))  //tests a bit



#endif /* POSEIDON_H_ */