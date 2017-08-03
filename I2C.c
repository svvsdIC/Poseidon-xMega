// I2C Initialization

#include "avr_compiler.h"
#include "twi_master_driver.h"
#include "twi_slave_driver.h"

/*! Defining an example slave address. */
#define SLAVE_ADDRESS_pH    0x63

/*! CPU speed 2MHz, BAUDRATE 100kHz and Baudrate Register Settings */
#define CPU_SPEED       32000000
#define BAUDRATE	100000
#define TWI_BAUDSETTING TWI_BAUD(CPU_SPEED, BAUDRATE)


/* Global variables */
TWI_MASTER_t twiMaster;    /*!< TWI master module. */

void TWI_MasterInit(TWI_MASTER_t *twi,
TWI_t *module,
TWI_MASTER_INTLVL_t intLevel,
uint8_t baudRateRegisterSetting)
{
	twi->interface = module;
	twi->interface->MASTER.CTRLA = intLevel |
	TWI_MASTER_RIEN_bm |
	TWI_MASTER_WIEN_bm |
	TWI_MASTER_ENABLE_bm;
	twi->interface->MASTER.BAUD = baudRateRegisterSetting;
	twi->interface->MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}

void TWI_MasterInterruptHandler(TWI_MASTER_t *twi)
{
	uint8_t currentStatus = twi->interface->MASTER.STATUS;

	/* If arbitration lost or bus error. */
	if ((currentStatus & TWI_MASTER_ARBLOST_bm) ||
	(currentStatus & TWI_MASTER_BUSERR_bm)) {

		TWI_MasterArbitrationLostBusErrorHandler(twi);
	}

	/* If master write interrupt. */
	else if (currentStatus & TWI_MASTER_WIF_bm) {
		TWI_MasterWriteHandler(twi);
	}

	/* If master read interrupt. */
	else if (currentStatus & TWI_MASTER_RIF_bm) {
		TWI_MasterReadHandler(twi);
	}

	/* If unexpected state. */
	else {
		TWI_MasterTransactionFinished(twi, TWIM_RESULT_FAIL);
	}
}

/*! /brief Example code
 *
 *  Example code that reads the key pressed and show a value from the buffer,
 *  sends the value to the slave and read back the processed value which will
 *  be inverted and displayed after key release.
 */
int main(void)
{
	/* Initialize PORTE for output and PORTD for inverted input. ----------------------------------------?*/ 
	/*PORTE.DIRSET = 0xFF;
	PORTD.DIRCLR = 0xFF;
	PORTCFG.MPCMASK = 0xFF;
	PORTD.PIN0CTRL |= PORT_INVEN_bm;*/
//      PORTCFG.MPCMASK = 0xFF;
//      PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc;
	
	// Enable internal pull-up on PC0, PC1.. Uncomment if you don't have external pullups ----------------?
//	PORTCFG.MPCMASK = 0x03; // Configure several PINxCTRL registers at the same time
//	PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc; //Enable pull-up to get a defined level on the switches

	

	/* Initialize TWI master. */
	TWI_MasterInit(&twiMaster,
	               &TWIE,
	               TWI_MASTER_INTLVL_MED_gc, 
	               TWI_BAUDSETTING);

	/* Enable LO interrupt level. 
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	sei(); */
		
}

/*! TWIC Master Interrupt vector. */
ISR(TWIC_TWIM_vect)
{
	TWI_MasterInterruptHandler(&twiMaster);
}
