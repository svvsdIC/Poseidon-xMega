/******************************************************************************
 * twiForPoseidon.h
 * This set of defines and routines is in support of the TWI interface as used 
 * for the Poseidon project: TWI i/f on Port E at 400kHz.  
 * 
 * Created: 12/29/2017 1:06:30 PM
 *  Author: craig
********************************************************************************/

/********************************************************************************
						Includes
********************************************************************************/
#include "twiForPoseidon.h"

/********************************************************************************
						Functions
********************************************************************************/

void TWIE_initialization(void) {
	// Initialize PORTE pins 0 and 1 (SDA and SDC) for output
	PORTE.DIRSET = 0x03;
	// Comment out the next two lines if you are using pull-up resistors on the circuit
	PORTE.PIN0CTRL = PORT_OPC_WIREDANDPULL_gc; //Set the pull-up resistor
	PORTE.PIN1CTRL = PORT_OPC_WIREDANDPULL_gc; //Set the pull-up resistor
	
	// Initialize TWI master.
	TWI_MasterInit(&twiMaster,
	&TWIE,
	TWI_MASTER_INTLVL_LO_gc,
	TWI_BAUDSETTING);

	// Enable LO interrupt level.
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
}