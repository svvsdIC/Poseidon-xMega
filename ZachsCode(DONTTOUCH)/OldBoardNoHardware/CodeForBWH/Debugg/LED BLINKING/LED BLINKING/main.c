/*
 * LED BLINKING.c
 *
 * Created: 11/07/2017 19:23:09
 * Author : Jonathan
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define ToggleBit(port, pin) port ^= (1<<pin)

int main(void)
{
    /* Replace with your application code */
	PORTC_DIRSET = PIN7_bm;
	
    while (1) 
    {
		ToggleBit(PORTC, PIN7_bm);
		_delay_ms(500);
    }
}

