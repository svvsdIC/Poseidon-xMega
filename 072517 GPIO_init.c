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
	// Needs to set up Photogrammetry lasers, Leak Detectors, Status LEDs
	// Leak Detectors are on Port D pins 4-5 and Port F 3,4,6,7
	// Photogrammetry Lasers are on Port E pins 3-5
	// Status LEDS are on portE pin 2(B) and Port C pins 6(R) & 7(G)
	//ESC Power Switch Port R pin 0
	// Set up Leak Detector Pins as inputs
	PORTD_DIR = 0b00000000;
	PORTF_DIR = 0b00000000;
	// Enable the interrupt on the Leak Detector Pins
	PORTD_INT1MASK = 0b00110000;
	PORTF_INT1MASK = 0b11011000;
	// Set up Photogrammetry pins as outputs
	PORTE_DIR = 0b00111000;
	// Set up LED status pins as output
	PORTC_DIR = 0b11000000;
	PORTE_DIR |= 0b00000100;
	//Set up ESC Power Switch
	PORTR_DIR = 0b00000001;
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