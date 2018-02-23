/**********************************************************************
 *
 * XMEGA TWI driver example applied to the TCS34725 RGB Sensor.
 * This file was derived from the XMEGA TWI_Master software from Atmel
 * application note AVR1308: Using the XMEGA TWI.  This file uses only
 * TWI Master driver as a prototype for the Poseidon Project at SVVSD
 * Innovation Center.
 *
 * Original code is Copyright (c) 2008, Atmel Corporation All rights reserved.
 * The Atmel code is found in twi_master_driver.h and twi_master_driver.c
 * Created: 2/5/2017 7:20:50 PM
 * Author : Snoopy Brown
 *
 *****************************************************************************/
#define F_CPU 32000000UL		// set CPU variable so delays are correct
/********************************************************************************
						Includes
********************************************************************************/
#include "avr_compiler.h"
#include "twi_master_driver.h"
#include "twiForPoseidon.h"
#include "colorSensor.h"
#include "DO_sensor.h"

/********************************************************************************
						Macros and Defines
********************************************************************************/
#define SetBit(port,bit)	port |= (1<<bit)	// macro to set a register bit to 1
#define ClearBit(port,bit)	port &= ~(1<<bit)	// macro to set a register bit to 0
#define ToggleBit(port,bit)	port ^= (1<<bit)	// macro to toggle a register bit
#define BitIsSet(port, bit) (port & (1 << bit)) //tests a bit
#define BitIsClear(port, bit) (!(port & (1 << bit)))  //tests a bit

/********************************************************************************
						Global Variables
********************************************************************************/
volatile unsigned char temp1;

/********************************************************************************
						Functions
********************************************************************************/


/********************************************************************************
						Main
********************************************************************************/
int main(void)
{
	// *************************************************************************
	//        Initialization code & device configuration
	// *************************************************************************
	// Configure the hardware, pins, and interrupt levels for the TWI I/F on Port E
	TWIE_initialization();
	// Initialize DO sensor
	DO_initialization();
	// enable global interrupts
	sei();
	// Now set up the RGB sensor
	//xmega_RGBsensor_init();
	// If we survived that, we're ready for the main loop
	// *************************************************************************
	// main loop
	// *************************************************************************
	while (1) 
	{
		// RGB Sensor read:
		//TWI_XFER_STATUS = xmega_read_RGB_values();
		// This next line provides a breakpoint for watching the RGB values
		temp1 = temp1+1;
	}
	return(0);
}

/********************************************************************************
*********************************************************************************
						Interrupt Service Routines
*********************************************************************************
********************************************************************************/

ISR(TWIE_TWIM_vect)  // TWIE Master Interrupt vector.
{
	TWI_MasterInterruptHandler(&twiMaster);
}

