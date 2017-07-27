
/*

 * XMEGA_PWM.c

 *

 * Created: 4/7/2017 10:11:16 PM

 * Author : craig

 */

#define F_CPU 32000000UL    //This is set via environment variable

// Make certain the internal 32MHz clock is selected!!


/********************************************************************************

                       Includes

********************************************************************************/

#include <avr/io.h>

#include <avr/interrupt.h>

//#include <stdbool.h>

//#include <avr/eeprom.h>

//#include <stdio.h>

//#include <string.h>

//#include <avr/pgmspace.h>

//#include <asf.h>

//#include <util/twi.h>

#include <util/delay.h>



/********************************************************************************

                        Macros and Defines

********************************************************************************/

#define SetBit(port,bit)    port |= (1<<bit)    // macro to set a register bit to 1

#define ClearBit(port,bit)    port &= ~(1<<bit)    // macro to set a register bit to 0

#define ToggleBit(port,bit)    port ^= (1<<bit)    // macro to toggle a register bit

#define BitIsSet(port,bit)    (port & (1<<bit))    // macro test - see if bit is set

#define BitIsClear(port,bit)     (!(port & (1<<bit)))    // macro test - see if bit is set

/********************************************************************************
                       Global Variables
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


void system_clock_init(void) {


}

/********************************************************************************
                        Main
********************************************************************************/



int main(void) {
    // *************************************************************************
    // initialization code & device configuration

    // *************************************************************************
    //
    system_clock_init();
    //
    // Blink an LED to make certain we are running..
    PORTR_DIR = 1; //Set port pins 0 (LED pins) to output
    for (char i=0;i<8;i++)
    {
    ToggleBit(PORTR_OUT,0);
    _delay_ms(100);

    }

    //    
    // *************************************************************************

    // main loop

    // *************************************************************************


    while (1)
    {
        ///Run Ben's code...
        ToggleBit(PORTR_OUT,0);
        _delay_ms(500);
    }
    return(0);


}


/********************************************************************************
*********************************************************************************

                        Interrupt Service Routines

********************************************************************************
********************************************************************************/
