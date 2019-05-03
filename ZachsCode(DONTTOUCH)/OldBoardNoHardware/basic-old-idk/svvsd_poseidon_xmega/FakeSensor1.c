/******************************************************************************
 * FakeSensor1.c
 * 
 * This routine creates and returns a string value corresponding to a typical
 * water quality sensor.  This first one simulates the Dissolved Oxygen sensor.
 * Each call updates the current value.  Suggest calling this routine once per 
 * second.
 *
 * Created:3/8/2018 7:20:50 PM
 * Author : Craig / Zach
********************************************************************************/

/********************************************************************************
						Includes
********************************************************************************/
#include <avr/io.h>
#include "poseidon.h"
//#include <avr/interrupt.h>
//#include <stdio.h>
//#include <string.h>

/********************************************************************************
						Macros and Defines
********************************************************************************/

/********************************************************************************
						Global Variables
********************************************************************************/
float WQDO, WQDOP, delta;
char DO_string[32];

/********************************************************************************
						Function Prototypes
********************************************************************************/

/********************************************************************************
						Functions
********************************************************************************/

void DO_init(void) {
	WQDO = 6.0;
	WQDOP = 100.0 * WQDO / 9.0;
	delta = -0.3;
}

void DO_read(char* DO_string) {
	// if we're beyond our chosen boundaries, switch direction
	if (WQDO > 8.0) {
			delta = -0.13;
		} else if (WQDO < 4) {
			delta = +0.17;
		} else {}
	// update our data
	WQDO = WQDO + delta;
	WQDOP = 100.0 * WQDO / 9.0;
	int wqdo = WQDO * 1000;
	int wqdop = WQDOP * 1000;
	// write our data to an output string...
	// String: "DO, x.xx mg/L, yy.y%"
	//sprintf(DO_string, "DO %4.1f mg/L, %4.1f%% Sat", WQDO, WQDOP);
	sprintf(DO_string, "DO %i mg/L, %i%% Sat\n", wqdo, wqdop);
	// and return
}


/********************************************************************************
*********************************************************************************
						Interrupt Service Routines
*********************************************************************************
********************************************************************************/

