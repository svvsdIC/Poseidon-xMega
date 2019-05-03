/*******************************************************************************
* ADC.c
*
* Analog to digital routines for the Poseidon submarine project
*
* Created: 4/7/2017 10:11:16 PM
* Author : Lindsey Hamblin
*
********************************************************************************/

/********************************************************************************
						Includes
********************************************************************************/
#include "ADC.h"

/********************************************************************************
						Macros and Defines
********************************************************************************/
 
 
/********************************************************************************
						Global Variables
********************************************************************************/


/********************************************************************************
						Functions
********************************************************************************/


void ADC_init(){

	//Enables the ADC
	SetBit(ADCA_CTRLA, ADC_ENABLE_bp);
	//Set DMA request selection to off
	ADCA_CTRLA |= ADC_DMASEL_OFF_gc;

	//Set ADC prescaler to 32
	ADCA_PRESCALER = ADC_PRESCALER_DIV32_gc;

	//Set ADC to unsigned mode
	ClearBit(ADCA_CTRLB, ADC_CONMODE_bp);
	//Disable free running mode
	ClearBit(ADCA_CTRLB, ADC_FREERUN_bp);
	//Set ADC to 12 bit right adjusted
	ADCA_CTRLB |= ADC_RESOLUTION_12BIT_gc;

	//Set reference selection to external reference pin on port B
	ADCA_REFCTRL = ADC_REFSEL_AREFB_gc;

	/*ADCA_PRESCALER = 0b00000011;
	ADCA_CTRLA = 0b00000001;
	ADCA_CTRLA |= 0b00000000;
	// Set to unsigned mode and no free run mode and also sets 12 bit right adjusted
	ADCA_CTRLB = 0b00000000;
	ADCA_CH0_CTRL.ADC_CH_GAIN_gp = 0b000; //Sets to no gain; ATMEL doesn't recognize the register. Gain factor to x1
	PORTA_DIR = 0; //Set all of port A as input pins
	PORTB_DIR &= 0b11110000; //Set PORT B pins 0-3 as input pins, which includes gthe analog reference pin (0).
	ADCA_REFCTRL = 0b00110000; // Setting reference selection to AREF on port B.
	// For initial test purposes, we'll only use ADC channel 0
	ADCA_CH0_INTCTRL.ADC_CH_INTMODE_gm = ADC_CH_INTMODE_COMPLETE_gc; //Set interrupt mode to conversion complete, but ATMEL doesn't recognize it INCORRECT
	ADCA_CH0_CTRL |= 0b00000001; //Single ended mode for unsigned
	// NEED HELP WITH SETTING PORT A AND PINS ON PORT B TO ANALOG*/

}
