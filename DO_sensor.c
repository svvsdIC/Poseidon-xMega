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
#include <string.h>
#include "DO_sensor.h"
#include "twiForPoseidon.h"
#include "twi_master_driver.h"

/********************************************************************************
						Local variables
********************************************************************************/

/********************************************************************************
						Functions
********************************************************************************/
void DO_initialization(void)
{
	// a. Factory reset
	strncpy(&TWIEsendBuffer[0], &DO_factory_reset, 7);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],7,0);
	_delay_ms(600); 
	// b. Check device info to verify communication
	strncpy(TWIEsendBuffer[0], DO_read_device_info, 1);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],1,0);
	_delay_ms(300);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0], 0, 14);
	_delay_ms(300);
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
		
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Not yet troubleshooted %%%%%%%%%%%%%%%%%%%%%%%%%%%5
	// c. Check device status and verify correct voltage 
	strncpy(&TWIEsendBuffer[0], &DO_status, 6);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],6,0);
	_delay_ms(300);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,17);
	_delay_ms(300);
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
	// Verify correct voltage?
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
		
	// d. Import saved calibration
	strncpy(&TWIEsendBuffer[0], &DO_load_cal, 6);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],6,0);
	_delay_ms(300);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,250); // Ask about large amount of bytes
	_delay_ms(300);
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
	// Verify correct voltage?
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
	
	// e. Enable %saturation output
	strncpy(&TWIEsendBuffer[0], &DO_enable_saturation, 6);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],6,0);
	_delay_ms(300);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,17);
	_delay_ms(300);
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
	// Verify correct voltage?
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
		
	// f. Read cal. parameters
}
	
/*uint8_t DO_calibration(void) {}
uint8_t DO_compensation(void) {}
uint8_t DO_read(void) {}*/