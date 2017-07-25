/********************************************************************************
 * Sample_main.c
 *
 * Created: 2/5/2017 7:20:50 PM
 * Author : Snoopy Brown
********************************************************************************/
 
// #define        F_CPU        1000000UL;                // set CPU variable so delays are correct
/********************************************************************************
Includes
********************************************************************************/
#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <stdbool.h>
//#include <avr/eeprom.h>
//#include <stdio.h>
//#include <string.h>
//#include <avr/pgmspace.h>
//#include <asf.h>
//#include <util/twi.h>
 
/********************************************************************************
Macros and Defines
********************************************************************************/
#define SetBit(port,bit)        port |= (1<<bit)        // macro to set a register bit to 1
#define ClearBit(port,bit)        port &= ~(1<<bit)        // macro to set a register bit to 0
#define ToggleBit(port,bit)        port ^= (1<<bit)        // macro to toggle a register bit
#define BitIsSet(port, bit) (port & (1 << bit)) //tests a bit
#define BitIsClear(port, bit) (!(port & (1 << bit)))  //tests a bit
 
/********************************************************************************
Global Variables
********************************************************************************/
 
/********************************************************************************
Function Prototypes
********************************************************************************/
 
/********************************************************************************
Functions
********************************************************************************/
void GPIO_init() {
	//FOR MOTOR SERVO TESTBED
	// Needs to set up Photogrammetry lasers, Leak Detectors, Status LEDs
	// Leak Detectors are on Port A pins 0-5
	// Photogrammetry Lasers are on Port B pins 0-2
	// Status LEDS are on portB pin 3(B) and Port C pins 6(R) & 7(G)
	//ESC Power Switch Port D pin 3
	// Set up Leak Detector Pins as inputs
	PORTA_DIR = 0b00000000;
	// Enable the interrupt on the Leak Detector Pins
	PORTA_INT1MASK = 0b00111111;
	// Set up Photogrammetry pins as outputs
	PORTB_DIR = 0b00000111;
	// Set up LED status pins as output
	PORTC_DIR = 0b11000000;
	PORTB_DIR |= 0b00001000;
	//Set up ESC Power Switch
	PORTD_DIR = 0b00001000;
}
 

/********************************************************************************
Main
********************************************************************************/
 
int main(void) {
// *************************************************************************
//    	Initialization code & device configuration
// *************************************************************************
 
 
// *************************************************************************
// main loop
// *************************************************************************
while (1) {
}
return(0);
}
 
/********************************************************************************
*********************************************************************************
Interrupt Service Routines
*********************************************************************************
********************************************************************************/