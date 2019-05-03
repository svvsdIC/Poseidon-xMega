/******************************************************************************
 * twiForPoseidon.h
 * This set of defines and routines is in support of the TWI interface as used 
 * for the Poseidon project: TWI i/f on Port E at 400kHz.  
 * 
 * Created: 12/29/2017 12:47:33 PM
 *  Author: craig
********************************************************************************/

#ifndef TWIFORPOSEIDON_H_
#define TWIFORPOSEIDON_H_

/********************************************************************************
						Includes
********************************************************************************/
#include "twi_master_driver.h"

/********************************************************************************
						Macros and Defines
********************************************************************************/
// Number of bytes in TWI E transmit/receive buffer
#define TWIE_BUFFER_SIZE        8

// CPU speed 32MHz, BAUDRATE 400kHz and Baudrate Register Settings 
#define BAUDRATE 400000
#define TWI_BAUDSETTING TWI_BAUD(F_CPU, BAUDRATE)

/********************************************************************************
						Global Variables
********************************************************************************/
TWI_Master_t twiMaster;   // TWI master module. 
// Buffer with test data to send.
uint8_t TWIEsendBuffer[TWIE_BUFFER_SIZE];
volatile unsigned char TWI_XFER_STATUS;

/********************************************************************************
						Function Prototypes
********************************************************************************/
void TWIE_initialization(void);

#endif /* TWIFORPOSEIDON_H_ */