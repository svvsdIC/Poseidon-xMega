/********************************************************************************
 * xmega_uart.c
 *
 * This set of functions implements an interrupt driven UART interface on
 * USARTE0 in an Atmel atxmega256A3BU.  It has been tested @38400 baud,
 * 8 data bits,  1 stop bits, no parity, and no flow control on an Xmega
 * Xplained board running at 32MHz w/ a frequency locked loop for a stable
 * clock.
 * These routines are set up for the USART on Port E, pins 2(Rx) and 3 (Tx).
 * Based on Atmel's series "Getting Started with AVR" on Youtube.
 *
 * Created: 8/16/2017 10:18:27 AM
 * Author: Craig R
 *******************************************************************************/ 

/********************************************************************************
						Includes
********************************************************************************/
#include "xmega_uarte0.h"
#include "poseidon.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

/********************************************************************************
						Global Variables
********************************************************************************/
static unsigned char UARTE0_RxBuf[UARTE0_RX_BUFFER_SIZE];
static volatile unsigned char UARTE0_RxHead;
static volatile unsigned char UARTE0_RxTail;
static unsigned char UARTE0_TxBuf[UARTE0_TX_BUFFER_SIZE];
static volatile unsigned char UARTE0_TxHead;
static volatile unsigned char UARTE0_TxTail;

/********************************************************************************
*********************************************************************************
						Functions
*********************************************************************************
********************************************************************************/

/* Initialize UARTD */
void USARTE0_init(uint16_t BaudSel, uint8_t BaudScale)
{
	static unsigned char x;
	// Set the PORTE GPIO pins 2 and 3 for input and output----------------
	ClearBit(PORTE_DIR, PIN2_bp);
	SetBit(PORTE_DIR, PIN3_bp);
	//  Note: for production version, we'll be using USARTD1, pins D6 & D7
	// Set baud rate registers-------------------------------------------------
	x = BaudSel; //get the lower 8 bits of BaudSel
	USARTE0_BAUDCTRLA = x;
	// Put BaudSel in the upper nibble of BAUDCTRLB and the high nibble
	// of BaudSel in the lower nibble of BAUDCTRLB
	x = ((BaudScale & 255)<<4) | (BaudSel>>8);
	USARTE0_BAUDCTRLB = x;
	// Set the mode and frame format registers -------------------------------
	// We want comm mode ASYNC (0b00), parity disabled (0b00), 1 stop bit
	// (0b0), and 8 data bots (0b011).  CTRLC = 0b00000011. 
	USARTE0_CTRLC = 0b00000011;
	// Set the interrupt levels -------------------------------------------------
	// We want the interrupt levels all set to low, which is 0b01.
	// Only enable the receive interrupt, transmit will be enabled when sending
	USARTE0_CTRLA = (USART_RXCINTLVL_LO_gc);
	// Enable the transmit and receive hardware ----------------------------
	USARTE0_CTRLB = USART_TXEN_bm | USART_RXEN_bm;
	
	/* Flush receive buffer */
	x = 0;
	UARTE0_RxTail = x;
	UARTE0_RxHead = x;
	UARTE0_TxTail = x;
	UARTE0_TxHead = x;
}

// The following routine works without interrupts.  Do not use when interrupts are enabled
unsigned char USARTE0_simple_receive_byte(void)
{
	while ( !(USARTE0_STATUS & USART_RXCIF_bm)); //wait for incoming data
	return USARTE0_DATA;
}

// The following routine works without interrupts.  Do not use when interrupts are enabled
void USARTE0_simple_send_byte(unsigned char data)
{
	while ( !(USARTE0_STATUS & USART_DREIF_bm)); //wait for empty xmit buffer
	USARTE0_DATA = data;
}

unsigned char USARTE0_ReceiveByte(void)
{
	unsigned char tmptail;
	// Wait for incoming data
	while (UARTE0_RxHead == UARTE0_RxTail);
	// Calculate buffer index
	tmptail = (UARTE0_RxTail + 1) & UARTE0_RX_BUFFER_MASK;
	// Store new index
	UARTE0_RxTail = tmptail;
	// Return data
	return UARTE0_RxBuf[tmptail];
}


void USARTE0_TransmitByte(unsigned char data)
{
	unsigned char tmphead;
	// Calculate buffer index
	tmphead = (UARTE0_TxHead + 1) & UARTE0_TX_BUFFER_MASK;
	// Wait for free space in buffer
	while (tmphead == UARTE0_TxTail);
	// Store data in buffer 
	UARTE0_TxBuf[tmphead] = data;
	// Store new index 
	UARTE0_TxHead = tmphead;
	// Enable UDRE interrupt 
	USARTE0_CTRLA |= (USART_DREINTLVL_LO_gc);
}

//This version is used to send formatted strings...
int USARTE0_Transmit_IO(char data, FILE *stream)
{
	unsigned char tmphead;
	// Calculate buffer index
	tmphead = (UARTE0_TxHead + 1) & UARTE0_TX_BUFFER_MASK;
	// Wait for free space in buffer
	while (tmphead == UARTE0_TxTail);
	// Store data in buffer
	UARTE0_TxBuf[tmphead] = data;
	// Store new index
	UARTE0_TxHead = tmphead;
	// Enable UDRE interrupt
	USARTE0_CTRLA |= (USART_DREINTLVL_LO_gc);
	return(0); //Is this needed?  What's the int for?
}

// This put string function stops when it reaches the end of a string, which is
// always a null character (0x00) in c.
void USARTE0_putstring(char* StringPtr) {
	while(*StringPtr != 0x00) {
		USARTE0_TransmitByte(*StringPtr);
		StringPtr++;
	}
}



/********************************************************************************
*********************************************************************************
						Interrupt Service Routines
*********************************************************************************
********************************************************************************/


ISR(USARTE0_RXC_vect)
{
	unsigned char data;
	unsigned char tmphead;
	
	// Read the received data 
	data = USARTE0_DATA;
	// Calculate buffer index 
	tmphead = (UARTE0_RxHead + 1) & UARTE0_RX_BUFFER_MASK;
	// Store new index 
	UARTE0_RxHead = tmphead;

	if (tmphead == UARTE0_RxTail) {
		// ERROR! Receive buffer overflow 
	}
	// Store received data in buffer 
	UARTE0_RxBuf[tmphead] = data;
}

ISR(USARTE0_DRE_vect)
{
	unsigned char tmptail;
	// Check if all data is transmitted 
	if (UARTE0_TxHead != UARTE0_TxTail) {//All data not yet transmitted...
		// Calculate buffer index
		tmptail = ( UARTE0_TxTail + 1 ) & UARTE0_TX_BUFFER_MASK;
		// Store new index 
		UARTE0_TxTail = tmptail;
		// Start transmission 
		USARTE0_DATA = UARTE0_TxBuf[tmptail];
	} else { // All data was transmitted...
		// Disable UDRE interrupt 
		USARTE0_CTRLA &= ~USART_DREINTLVL_gm;
	}
}