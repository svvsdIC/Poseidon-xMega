/******************************************************************************
 * colorSensor.c
 * This set of defines and routines is in support of the TCS3472 color light
 * sensor, specifically the breakout board from AdaFruit.  This code will be 
 * needed for the Poseidon project (surface board and submarine) and the
 * upcoming St Vrain Valley Light Projects.
 * 
 * Created: 12/29/2017 12:47:33 PM
 *  Author: craig
********************************************************************************/

/********************************************************************************
						Includes
********************************************************************************/
//#include "TempSensor.h"
//#include "twiForPoseidon.h"
//#include "twi_master_driver.h"

/********************************************************************************
						Local variables
********************************************************************************/
//volatile unsigned char temp; //for debug

/********************************************************************************
						Functions
********************************************************************************/
/*void xmega_TEMPsensor_init(void) {
	// Set up the light sensor integration time and gain
	// Process for writing data to registers for the TCS34725:
	// 1) Send the sensor I2C address and the write bit set
	// 2) Write the command register with the transaction mode and register address(es)
	// 3) Send the data for the register(s)
	// First turn everything on...
	//TWIEsendBuffer[0] = RGB_SENSOR_WRITE; // The first byte must always have TWI slave address.
	TWIEsendBuffer[0] = (0x80 | RGB_ENABLE_REGISTER_ADDRESS); // Where we gonna write
	TWIEsendBuffer[1] = RGB_ENABLE_REGISTER_SETTING; // What we gonna write
	// Two bytes to send, none to read:
	TWI_MasterWriteRead(&twiMaster, TWI_RGB_SENSOR_ADDRESS, &TWIEsendBuffer[0],2,0);
	while (!(twiMaster.status == TWIM_STATUS_READY))
	{
		//wait for the transaction to finish
	}
	// Now verify we're talking to the right device...set up a read of the chip ID:
	TWIEsendBuffer[0] = (0x80 | TCS34725_ID_ADDRESS); //  Address from which to read on the next transaction
	// One byte to send, one byte to read:
	TWI_MasterWriteRead(&twiMaster,	TWI_RGB_SENSOR_ADDRESS,	&TWIEsendBuffer[0],1,1);
	// Wait for transaction to complete...
	while (!(twiMaster.status == TWIM_STATUS_READY)) { }
	// Note that the data we want is actually in twiMaster.readData, starting in location [0]
	if (!(twiMaster.readData[0]==0x44))
	{
		temp=255; // We're talking to the wrong device!!
	}
	else
	{
		temp=0xAD; // We're talking to the right device.
	}
	// Now set the light sensor integration time...
	TWIEsendBuffer[0] = (0x80 | TCS34725_ATIME_ADDRESS); // Where we gonna write
	TWIEsendBuffer[1] = TCS34725_INTEG_700MS; // What we gonna write
	// Two bytes to send, none to read:
	TWI_MasterWriteRead(&twiMaster, TWI_RGB_SENSOR_ADDRESS, &TWIEsendBuffer[0],2,0);
	// Wait for transaction to complete...
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
	// Now set the light sensor gain
	TWIEsendBuffer[0] = (0x80 | TCS34725_CONTROL_ADDRESS); // Where we gonna write
	TWIEsendBuffer[1] = TCS34725_GAIN_1X; // What we gonna write
	// Two bytes to send, none to read:
	TWI_MasterWriteRead(&twiMaster, TWI_RGB_SENSOR_ADDRESS, &TWIEsendBuffer[0],2,0);
	// Wait for transaction to complete...
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
	//
	//Now we are ready to read some sensor values (I think)...
	// To read the light sensor values,
	// 1) Send the sensor I2C address and write bit
	// 2) Set the command register with block (sequential) read and cdatal sensor address (low)
	// 3) send the sensor I2C address with the READ bit
	// 4) Read eight bytes of light sensor readings.
	TWIEsendBuffer[0] = (0x80 | TCS34725_CDATAL_ADDRESS);  // 0xA0 specifies sequential read
	// one bytes to send, eight to read:
	TWI_MasterWriteRead(&twiMaster, TWI_RGB_SENSOR_ADDRESS, &TWIEsendBuffer[0],1,8);
	// Wait for transaction to complete...
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
	//Transfer values to our variables....
	raw_clear = (twiMaster.readData[1]<<8)+twiMaster.readData[0];
	raw_red = (twiMaster.readData[3]<<8)+twiMaster.readData[2];
	raw_green = (twiMaster.readData[5]<<8)+twiMaster.readData[4];
	raw_blue = (twiMaster.readData[7]<<8)+twiMaster.readData[6];
	// The RGB sensor is now ready to read...
}

unsigned char xmega_read_TEMP_values(void){
	// and for the read part...note I don't have to reset the read address each time - it will always
	// start where the command buffer is pointing
	// No bytes to send, eight to read:
	TWI_MasterWriteRead(&twiMaster, TWI_RGB_SENSOR_ADDRESS, &TWIEsendBuffer[0],0,8);
	// Wait for transaction to complete...
	while (!(twiMaster.status == TWIM_STATUS_READY)) {}
	//Transfer values to our variables....
	raw_clear = (twiMaster.readData[1]<<8)+twiMaster.readData[0];
	raw_red = (twiMaster.readData[3]<<8)+twiMaster.readData[2];
	raw_green = (twiMaster.readData[5]<<8)+twiMaster.readData[4];
	raw_blue = (twiMaster.readData[7]<<8)+twiMaster.readData[6];
	return(twiMaster.status);
}*/