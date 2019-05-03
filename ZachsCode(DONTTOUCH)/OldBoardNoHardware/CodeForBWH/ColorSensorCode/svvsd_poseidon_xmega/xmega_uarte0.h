/********************************************************************************
 * xmega_uarte0.h
 *
 * This set of functions implements an interrupt driven UART interface on
 * USARTE0 in an Atmel atxmega256A3BU.  It has been tested @38400 baud, 
 * 8 data bits,  1 stop bits, no parity, and no flow control on an Xmega 
 * Xplained board running at 32MHz w/ a frequency locked loop for a stable
 * clock.  
 * These routines are set up for the USART on Port E, pins 2(Rx) and 3 (Tx).
 * Note: for production version, we'll be using USARTD1, pins D6 & D7
 *
 * Based on Atmel's series "Getting Started with AVR" on Youtube.
 * Created: 8/16/2017 10:18:27 AM
 * Author: Craig R
 *******************************************************************************/ 

#ifndef XMEGA_UARTE0_H_
#define XMEGA_UARTE0_H_
/********************************************************************************
						Includes
********************************************************************************/
#include <avr/interrupt.h>
#include <stdio.h>

/********************************************************************************
						Macros and Defines
********************************************************************************/
/* UART Buffer Defines - make them long enough for the GPS messages */
#define UARTE0_RX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define UARTE0_TX_BUFFER_SIZE 128
#define UARTE0_RX_BUFFER_MASK (UARTE0_RX_BUFFER_SIZE - 1)
#if (UARTE0_RX_BUFFER_SIZE & UARTE0_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif

#define UARTE0_TX_BUFFER_MASK (UARTE0_TX_BUFFER_SIZE - 1)
#if (UARTE0_TX_BUFFER_SIZE & UARTE0_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

// ---------BAUD RATE SETTINGS ---------------------------------------------
// From Table 23-5 in the XMEGA manual, for 9600Hz, we want
// BSEL = 12 and BSCALE = +4
//#define MyBSEL 12
//#define MyBSCALE 4

// From Table 23-5 in the XMEGA manual, for 38400Hz, we want
// BSEL = 12 and BSCALE = +2
#define MyBSEL 12
#define MyBSCALE 2

// From Table 23-5 in the XMEGA manual, for 115.2kHz, we want
// BSEL = 135 and BSCALE = -2
//#define MyBSEL 135
//#define MyBSCALE -2


/********************************************************************************
						Function Prototypes
********************************************************************************/
void USARTE0_init(uint16_t BaudSel, uint8_t BaudScale);
unsigned char USARTE0_simple_receive_byte(void);
void USARTE0_simple_send_byte(unsigned char data);
unsigned char USARTE0_ReceiveByte(void);
void USARTE0_TransmitByte(unsigned char data);
void USARTE0_putstring(char* StringPtr);
int USARTE0_Transmit_IO(char data, FILE *stream);

#endif /* XMEGA_UARTE0_H_ */