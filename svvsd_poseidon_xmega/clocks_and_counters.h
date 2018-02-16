/******************************************************************************
 * clocks_and_counters.h
 * 
 * The functions in this file perform several functions:
 *   1) Set the 256A3BU clock for high accuracy 32MHz
 *   2) Set the Timer/counters on PORT C to PWM periods and pulse widths
 *         to control Electronic Speed Controllers (ESCs) or Servos.
 * 
 * Created: 8/17/2017 2:20:05 PM
 * Author : Craig
 *
********************************************************************************/
#ifndef CLOCKS_AND_COUNTERS_H_
#define CLOCKS_AND_COUNTERS_H_

/********************************************************************************
						Includes
********************************************************************************/
#include "poseidon.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

/********************************************************************************
						Macros and Defines
********************************************************************************/
// The next lines identify the desired ESC freq, prescaler, and TOP count needed
// to operate the timer counter in support of the ESCs.
#define ESC_FREQ 50UL		// The Electronic Speed Controllers want a 50Hz freq.
#define ESC_PRESCALER 64UL	// Prescaler=64 to maximize counter resolution
#define ESC_TOP_COUNT F_CPU/(ESC_FREQ*ESC_PRESCALER)-1  //See eqn. on pg 172/173

/********************************************************************************
						Function Prototypes
********************************************************************************/
void system_clock_init(void); 
void timer_counter_C0_C1_D0_init(uint16_t topcount);
void timer_counter_F0_init(uint16_t topcount);

#endif /* CLOCKS_AND_COUNTERS_H_ */