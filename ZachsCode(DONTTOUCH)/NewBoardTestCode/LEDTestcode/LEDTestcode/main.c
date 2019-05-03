/*
 * LEDTestcode.c
 *
 * Created: 3/7/2019 5:57:55 PM
 * Author : shutes_zachery
 */ 
#define F_CPU 2000000UL
#include <avr/io.h>
#include "util/delay.h"
//#define 

#define NUM_PADS 64
typedef enum{
	PORTA_e = 0x00,
	PORTB_e, PORTC_e, PORTD_e, PORTE_e, PORTF_e, PORTR_e, PORT_NUM_e,
}XMEGA_A3BU_Ports_e;
uint8_t pad2port[NUM_PADS] {
	PORTA_e, PORTA_e, PORTA_e, PORTA_e, PORTA_e, 
	PORTB_e, PORTB_e, PORTB_e, PORTB_e, PORTB_e, PORTB_e, PORTB_e, PORTB_e, 
	PORT_NUM_e, PORT_NUM_e, 
	PORTC_e, PORTC_e, PORTC_e, PORTC_e, PORTC_e, PORTC_e, PORTC_e, PORTC_e, 
	PORT_NUM_e, PORT_NUM_e, 
	PORTD_e, PORTD_e, PORTD_e, PORTD_e, PORTD_e, PORTD_e, PORTD_e, PORTD_e, 
	PORT_NUM_e, PORT_NUM_e, 
	PORTE_e, PORTE_e, PORTE_e, PORTE_e, PORTE_e, PORTE_e, 
	PORT_NUM_e, PORT_NUM_e, PORT_NUM_e, PORT_NUM_e, 
	PORTF_e, PORTF_e, PORTF_e, PORTF_e, PORTF_e, 
	PORT_NUM_e, PORT_NUM_e, PORT_NUM_e, 
	PORTF_e, PORTF_e, 
	PORT_NUM_e, PORT_NUM_e, 
	PORTR_e, PORTR_e, 
	PORT_NUM_e, PORT_NUM_e, 
	PORTA_e, PORTA_e, PORTA_e, 
};
#define PADNOTPIN 0xFF
uint8_t pad2pin[NUM_PADS] {
PIN3_bm, 
PIN4_bm,
PIN5_bm,
PIN6_bm,
PIN7_bm,
PIN0_bm,
PIN1_bm,
PIN2_bm,
PIN3_bm,
PIN4_bm,
PIN5_bm,
PIN6_bm,
PIN7_bm,
PADNOTPIN,
PADNOTPIN,
PIN0_bm,
PIN1_bm,
PIN2_bm,
PIN3_bm,
PIN4_bm,
PIN5_bm,
PIN6_bm,
PIN7_bm,
PADNOTPIN,
PADNOTPIN,
PIN0_bm,
PIN1_bm,
PIN2_bm,
PIN3_bm,
PIN4_bm,
PIN5_bm,
PIN6_bm,
PIN7_bm,
PADNOTPIN,
PADNOTPIN,
PIN0_bm,
PIN1_bm,
PIN2_bm,
PIN3_bm,
PIN4_bm,
PIN5_bm,
PADNOTPIN,
PADNOTPIN,
PADNOTPIN,
PADNOTPIN,
PIN0_bm,
PIN1_bm,
PIN2_bm,
PIN3_bm,
PIN4_bm,
PADNOTPIN,
PADNOTPIN,
PADNOTPIN,
PIN6_bm,
PIN7_bm,
PADNOTPIN,
PADNOTPIN,
PIN0_bm,
PIN1_bm,
PADNOTPIN,
PADNOTPIN,
PIN0_bm,
PIN1_bm,
PIN2_bm,
};

void Pinmode(int pad) {
	if(pad == 0 || pad > 64) {
		return;
	}
	pad--;
	XMEGA_A3BU_Ports_e port = pad2port[pad];
	if( port == PORT_NUM_e ){
		return;
	}
	
	// now set the direction of the right pin
	
}
//PORTC_OUTSET

int main(void)
{
    /* Replace with your application code */
	PORTC_DIRSET = PIN7_bm;
	PORTR_DIRSET = PIN1_bm;
    while (1) 
    {
		//PORTC_OUTTGL = PIN7_bm;
		
		*((uint8_t*)(0x0647)) = PIN7_bm;
		PORTR_OUTTGL = PIN1_bm;
		_delay_ms(1000);
    }
}

