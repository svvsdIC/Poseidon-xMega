/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA TWI driver example source.
 *
 *      This file contains an example application that demonstrates the TWI
 *      master and slave driver. It shows how to set up one TWI module as both
 *      master and slave, and communicate with itself.
 *
 *      The recommended test setup for this application is to connect 10K
 *      pull-up resistors on PC0 (SDA) and PC1 (SCL). Connect a 10-pin cable
 *      between the PORTD and SWITCHES, and PORTE and LEDS.
 *
 * \par Application note:
 *      AVR1308: Using the XMEGA TWI
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 *****************************************************************************/

// DISSOLVED OXYGEN SENSOR
/*
- Initialize necessary ports
- Set up buffer array (is it going to be specific to the DO sensor?) YES
- Use the functions provided in master driver code to read and write in while(1)
*/

// Source files in project from Atmel
#include "avr_compiler.h"
#include "twi_master_driver.h"

// Macros
#define SetBit(port,bit)	port |= (1<<bit) // Set register bit to 1
#define ClearBit(port,bit)	port &= ~(1<<bit) // Set register bit to 0
#define ToggleBit(port,bit) port ^= (1<<bit) // Toggles register bit

/*! Defining number of bytes in buffer. */
#define NUM_BYTES        8

/*! CPU speed 2MHz, BAUDRATE 100kHz and Baudrate Register Settings */ 
#define CPU_SPEED       2000000 // Do I need to edit these values to match the others code we've written? 32MHz; 32000000UL
#define BAUDRATE	100000
#define TWI_BAUDSETTING TWI_BAUD(CPU_SPEED, BAUDRATE)

// Define Slave Address: Data sheet says 97 or (0x61)
#define SLAVE_ADDRESS	0x61

/* Global variables */
TWI_Master_t twiMaster;    /*!< TWI master module. */

/*! Buffer with test data to send. This is the transmitted data*/
// Order of bytes: (Start, Address, R/W, acknowledge, 
// data, acknowledge, data, acknowledge/not acknowledge, stop)
// uint8_t sendBuffer[NUM_BYTES] = {0x55, 0x61, 0xF0, 0x0F, 0xB0, 0x0B, 0xDE, 0xAD};
	
// Read buffer (reading sensor)
uint8_t readBuffer[NUM_BYTES];
// Write buffer (sending commands)
uint8_t writeBuffer[NUM_BYTES];
//writeBuffer[0] = 

/*! /brief Example code
 *
 *  Example code that reads the key pressed and show a value from the buffer,
 *  sends the value to the slave and read back the processed value which will
 *  be inverted and displayed after key release.
 */
int main(void)
{
	// Set port direction of Bus Clock and Bus Data to output (P0 and P1)
	PORTE_DIR = 0b00000011; // Bus data = input?
	
	// PINS I THINK ARE NECESSARY
	// Enable TWI Master
	SetBit(TWIE_MASTER_CTRLA, TWI_MASTER_ENABLE_bp);
	
	// Enable acknowledge action (not sure if this is necessary)
	SetBit(TWIE_MASTER_CTRLC, TWI_MASTER_ACKACT_bp);
	
	// Status register
	SetBit(TWIE_MASTER_STATUS, TWI_MASTER_RXACK_bp); // Receive acknowledge from slave
	
	
	// Data register
	
	/*
	PORTC.DIRSET = 0xFF; //TWIC.CTRLA.ENABLE;
	PORTD.DIRCLR = 0xFF; 
	*/
	
// PORTCFG.MPCMASK = 0xFF;
// PORTD.PIN0CTRL |= PORT_INVEN_bm;
//      PORTCFG.MPCMASK = 0xFF;
//      PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc;
	
	// Enable internal pull-up on PC0, PC1.. Uncomment if you don't have external pullups
//	PORTCFG.MPCMASK = 0x03; // Configure several PINxCTRL registers at the same time
//	PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc; //Enable pull-up to get a defined level on the switches

	/* Initialize TWI master. */
	TWI_MasterInit(&twiMaster,
	               &TWIE,
	               TWI_MASTER_INTLVL_LO_gc,
	               TWI_BAUDSETTING);

	/* Enable LO interrupt level. */
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	sei();

	uint8_t BufPos = 0;
	
	while (1) {
		
		// SEND AND READ DATA FROM THE D.O. SENSOR
		// If Master is ready, read and write data
		TWI_MasterWriteRead(&twiMaster,
		SLAVE_ADDRESS,
		&sendBuffer[BufPos],
		1,
		1);
	/*
        while(!PORTD.IN); /* Wait for user to press button      

		/* Show the byte to send while holding down the key.
		while(PORTD.IN != 0x00){
			PORTE.OUT = sendBuffer[BufPos];
		}

		TWI_MasterWriteRead(&twiMaster,
		                    SLAVE_ADDRESS,
		                    &sendBuffer[BufPos],
		                    1,
		                    1);


		while (twiMaster.status != TWIM_STATUS_READY) {
			/* Wait until transaction is complete. */
		}

		/* Show the sent byte received and processed on LEDs.
		PORTE.OUT = (twiMaster.readData[0]);
                
                while(PORTD.IN); /* Wait for user to release button
		*/
	}
}

/*! TWIC Master Interrupt vector. */
ISR(TWIE_TWIM_vect)
{
	TWI_MasterInterruptHandler(&twiMaster);
}
