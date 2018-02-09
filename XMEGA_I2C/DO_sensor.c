/*
 * DO_sensor.c
 * Source Code for Dissolved Oxygen Sensor
 * Project: Innovation Center's Project Poseidon
 * Created: 2/8/2018 5:28:12 PM
 *  Author: tran.michel02
 */ 
	
/********************************************************************************
						Includes
********************************************************************************/
#include <stdio.h>
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
	uint8_t TWIEsendBuffer[7] = DO_factory_reset; 
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],7,0);
	_delay_ms(600); 
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,6);
	if(twiMaster.readData[0] == 1)
	{
		for(int i = 0; i < 6; i++)
		{
			DO_data_collection[i] = twiMaster.readData[i];
		}
	}
	else
	{
		// Error condition
		int error = 0;
		printf("%d \n", error);
	}
	
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
		
	// b. Check device info to verify communication
		
	// c. Check device status and verify correct voltage 
	/**/
	
	// d. Calibrate (w/ 60s wait)
	/**/
	
	// e. IF REQUIRED Cal,0 procedure
	/**/
	
	// f. Read cal. parameters
}
	
/*uint8_t DO_initialization(void) {}
uint8_t DO_compensation(void) {}
uint8_t DO_read(void) {}*/