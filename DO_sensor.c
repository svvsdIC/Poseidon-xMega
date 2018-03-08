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
	// a. Factory reset and check response
	strncpy(&TWIEsendBuffer[0], &DO_factory_reset, 7);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],7,0);
	_delay_ms(600); 
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,13);
	_delay_ms(600);
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
	strncpy(TWIEsendBuffer[0], &DO_read_device_info, 1);
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
		
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Not yet troubleshooted %%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
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
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
		
	// f. Do a test read (make sure all params are returned and in range)
	strncpy(&TWIEsendBuffer[0], &DO_return_read, 1);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],1,0);
	_delay_ms(600);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,6);
	_delay_ms(600);
	// ALTER THIS to add verification mechanism for proper input
	if(twiMaster.readData[0] == 1)
	{
		for(int i = 0; i < 6; i++)
		{
			DO_data_collection[i] = twiMaster.readData[i];
			// g. IF everything checked out, turn LED OFF
			strncpy(&TWIEsendBuffer[0], &DO_LED_OFF, 3);
			TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],3,0);
			_delay_ms(300);
			TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,2);
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
				
			// h. Command the DO sensor to sleep
			strncpy(&TWIEsendBuffer[0], &DO_sleep, 5);
			TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],5,0);
			_delay_ms(300); // Not sure if this is necessary... data sheet did not mention a wait time
			
			// i. Return init status (0 if good, 1 and above for errors)
			return(0)
		}
	}
	else
	{
		// Error condition
		int error = 1;
		printf("%d \n", error);
	}
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
}
	
uint8_t DO_calibration(void) 
{
	// a. Factory Reset and check response
	strncpy(&TWIEsendBuffer[0], &DO_factory_reset, 7);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],7,0);
	_delay_ms(600);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,13);
	_delay_ms(600);
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
		
	// b. Check device info
	strncpy(TWIEsendBuffer[0], &DO_read_device_info, 1);
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
		
	// c. Check device status
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
		
	// d. Calibration procedure (Single Point Calibration)
	// Readings should be ~9.09-9.1Xmg/L
	strncpy(&TWIEsendBuffer[0], &DO_cal, 3);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],3,0);
	_delay_ms(1300);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,2);
	_delay_ms(1300);
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
		
	// e. IF NEEDED perform Cal,0 (Add later)
	
	// f. Read calibration params and either save to EEPROM or write them out
	strncpy(&TWIEsendBuffer[0], &DO_save_cal, 6);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],6,0);
	_delay_ms(300);
	TWI_MasterWriteRead(&twiMaster, DO_sensor_address, &TWIEsendBuffer[0],0,19);
	_delay_ms(300);
	if(twiMaster.readData[0] == 1)
	{
		for(int i = 0; i < 6; i++)
		{
			DO_data_collection[i] = twiMaster.readData[i];
			// Need a mechanism to write out the string and then save it as a constant (parsed for import statement)
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
		// Define the string as a constant
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/ 

/*uint8_t DO_compensation(void) {}
uint8_t DO_read(void) {}*/