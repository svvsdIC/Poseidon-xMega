/*
 * GccApplication5.c
 *
 * Created: 8/10/2017 2:31:38 PM
 * Author : lhamb
 */ 

#include <avr/io.h>
#include "avr_compiler.h"
#include "twi_master_driver.h"

#define SetBit(port,bit)    port |= (1<<bit)    // macro to set a register bit to 1
#define ClearBit(port,bit)    port &= ~(1<<bit)    // macro to set a register bit to 0
#define ToggleBit(port,bit)    port ^= (1<<bit)    // macro to toggle a register bit
#define BitIsSet(port,bit)    (port & (1<<bit))    // macro test - see if bit is set
#define BitIsClear(port,bit)     (!(port & (1<<bit)))    // macro test - see if bit is set

//CPU Speed
#define F_CPU 32000000UL

//Definitions for sensor addresses
#define DO_Sensor 0x61

//Calculated baud value to 155 given CPU speed and desired baud rate given equations on page 266
#define TWI_Baud  0b10011011

//Make an instance of the master struct
TWI_Master_t	twiMaster;

void system_clock_init(void) {
    //*****************************************************************************************
    //
    //  Several things we have to do to set up the system clocks
    //    1 - Enable the external oscillator (32768Hz)
    //            (Used for the RTC and as a DFLL reference)
    //    2 - Hookup the RTC to the external oscillator
    //  3 - Enable the 32MHz internal clock
    //  4 - Set up the Digital Frequency-Locked-Loop (DFLL)
    //            (this improves frequency accuracy)
    //
    // Enable the external oscillator...
    //        First we need to tell the chip what kind of oscillator is out there
    //        In our case, it is a high accuracy 32.768kHz oscillator
    //        Set low power mode and select 32.768kHz TOSC
    OSC_XOSCCTRL = OSC_FRQRANGE_04TO2_gc | OSC_X32KLPM_bm | OSC_XOSCSEL_32KHz_gc;
    //        We need to enable the external oscillator in VBAT land, too.
    //        To do this, we need to first enable access to the registers...
    VBAT_CTRL |= VBAT_ACCEN_bm;
    //        Now enable the oscillator
    VBAT_CTRL |= VBAT_XOSCEN_bm;
    //        New we want to enable the oscillator in the OSC control register
    //        NOTE: Many OSC and CLK registers are protected, so writing to
    //            the CCP register is required to unlock them.  See 7.9-7.11.
    CPU_CCP = CCP_IOREG_gc; // unlock critical IO registers for four clock cycles
    OSC_CTRL |= OSC_XOSCEN_bm; // Write the control register to enable external 32,768Hz clock
    //        Clock should be enabled.  Wait for it to stabilize...
    do {} while BitIsClear(OSC_STATUS,OSC_XOSCRDY_bp);
    //
    // Now we can hook up the RTC to the external oscillator...
    //        Select the external 32.768kHz external crystal oscillator for RTC source
    CPU_CCP = CCP_IOREG_gc; // unlock critical IO registers for four clock cycles
    CLK_RTCCTRL = CLK_RTCSRC_TOSC32_gc | CLK_RTCEN_bm;
    //
    // Now enable the 32MHz internal clock
    //        Enable the 32MHz internal clock in the Oscillator Control Register...
    CPU_CCP = CCP_IOREG_gc; // unlock critical IO registers for four clock cycles
    SetBit(OSC_CTRL, OSC_RC32MEN_bp); // Write the control register to enable internal 32MHz clock    
    //        and wait for the clock to come up to stabilize:
    do {} while BitIsClear(OSC_STATUS,OSC_RC32MRDY_bp);
    //
    // Now that it is enabled and stable, select it as the clock source...
    CPU_CCP = CCP_IOREG_gc; // unlock critical IO registers for four clock cycles
    CLK_CTRL = CLK_SCLKSEL_RC32M_gc; // Write the control register to select internal 32MHz clock
    //
    // Now, to improve accuracy, we want to enable the Digital Frequency
    // Locked Loop (DFLL) for the 32MHz clock and using the external 32.768kHz
    // clock as the reference.  First, select the 32.768kHz external oscillator as the reference source
    OSC_DFLLCTRL = OSC_RC32MCREF_XOSC32K_gc;
    // Now enable the auto-calibration
    SetBit(DFLLRC32M_CTRL, DFLL_ENABLE_bp); // Enable auto-calibration
    //
    // At this point, we should have all the new clocks set up.
    // Before returning, disable the 2MHz clock to save power
    CPU_CCP = CCP_IOREG_gc; // unlock critical IO registers for four clock cycles
    ClearBit(OSC_CTRL, OSC_RC2MEN_bp); // Clear the 2MHz enable bit to disable 2MHz clock    
    //
    // All done!
    //
}

int main(void)
{
   //In the example code, this is where they set direction on registers, not sure what to do on our end?
   
   //Initialize TWi Master
   TWI_MasterInit(&twiMaster, &TWIC, TWI_MASTER_INTLVL_MED_gc, TWI_Baud);
   
   //Enable Medium level interrupts on the xmega
   PMIC.CTRL |= PMIC_MEDLVLEN_bm;
   sei();
   
   //attempt to read data from dissolved Oxygen sensor
   TWI_MasterRead(&twiMaster, DO_Sensor, 1);
   
   while (twiMaster.status != TWIM_STATUS_READY){
	   //wait until transaction is complete
   }
   return (0);
    
}


ISR(TWIC_TWIM_vect){
	TWI_MasterInterruptHandler(&twiMaster);
}
