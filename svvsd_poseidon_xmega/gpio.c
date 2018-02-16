/******************************************************************************
 * gpio.c
 * This set of routines sets up all of the IO pins on the POSEIDON xmega.
 * This code will be needed on the submarine.  
 * 
 * Created: 12/29/2017 12:47:33 PM
 *  Author: Daniel Torres-Hernandez
********************************************************************************/

/********************************************************************************
						Includes
********************************************************************************/
#include "poseidon.h"
#include "gpio.h"

/********************************************************************************
						Local variables
********************************************************************************/


/********************************************************************************
						Functions
********************************************************************************/

void GPIO_init(void) {
	// Needs to set up Photogrammetry lasers, Leak Detectors, Status LEDs
	// Leak Detectors are on Port A, pins 0-5 ================
	// Set up Leak Detector Pins as inputs
	PORTA_DIR = 0b00000000;
	// Enable the interrupt on the Leak Detector Pins
	PORTA_INT1MASK = 0b00111111;
	// DO we need to enable the low level interrupt for these pins?*********************************************
	
	// Photogrammetry Lasers are on Port B pins 0-2 ============
	// Set up Photogrammetry pins as outputs
	PORTB_DIR = 0b00000111;
	
	// Status LEDS are on portB pin 3 and Port C pins 6 & 7
	// Set up LED status pins as output
	PORTB_DIR |= 0b00001000;
	PORTC_DIR |= 0b11000000;
	
	// For debug purposes in the development environment,, there are three LEDs 
	// on the Xmega xplained board at PortR0, PortR1 (both yellow), and PortD4 (red)
	// One additional LED is used to indicate power (PortD5 (green)).
	PORTR_DIR |= 0b00000011;
	PORTD_DIR |= 0b00010000;
	// For these LEDs, it appears a logic 1 turns them off...
	// Set the pins to ensure the LEDs are off initially..
	PORTR_OUT |= 0b00000011;
	PORTD_OUT |= 0b00010000;
}

