/*
Source Code for Dissolved Oxygen Sensor
Project: Innovation Center's Project Poseidon
Created: 1/25/18
*/
	
/********************************************************************************
						Includes
********************************************************************************/
#include "DO_sensor.h"
#include "twiForPoseidon.h"
#include "twi_master_driver.h"

/********************************************************************************
						Local variables
********************************************************************************/

/********************************************************************************
						Functions
********************************************************************************/
void DO_calibration(void)
{
	// a. Factory reset
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],7,0);
	// b. Check device info to verify communication
	// c. Check device status and verify correct voltage
	// d. Calibrate (w/ 60s wait)
	// e. IF REQUIRED Cal,0 procedure
	// f. Read cal. parameters
}
	
void DO_initialization(void){}
void DO_compensation(void){}
void DO_read(void){}