/*
 * XMEGA_PWM.c
 *
 * Created: 4/7/2017 10:11:16 PM
 * Author : craig
 */
#define F_CPU 32000000UL    //This is set via environment variable
// Make certain the internal 32MHz clock is selected!!
/********************************************************************************
                        Includes
********************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdbool.h>
//#include <avr/eeprom.h>
//#include <stdio.h>
//#include <string.h>
//#include <avr/pgmspace.h>
//#include <asf.h>
//#include <util/twi.h>
#include <util/delay.h>
/********************************************************************************
                        Macros and Defines
********************************************************************************/
#define SetBit(port,bit)    port |= (1<<bit)    // macro to set a register bit to 1
#define ClearBit(port,bit)    port &= ~(1<<bit)    // macro to set a register bit to 0
#define ToggleBit(port,bit)    port ^= (1<<bit)    // macro to toggle a register bit
#define BitIsSet(port,bit)    (port & (1<<bit))    // macro test - see if bit is set
#define BitIsClear(port,bit)     (!(port & (1<<bit)))    // macro test - see if bit is set
/********************************************************************************
                        Global Variables
********************************************************************************/
void USART_init(){
	PORTE_DIR = 0b00001000;
	// Sets the BAUD speed of USART connection
	// Port A: bits 0-2, 7
	SetBit(USARTE0_BAUDCTRLA, USART_BSEL0_bp);
	SetBit(USARTE0_BAUDCTRLA, USART_BSEL1_bp);
	SetBit(USARTE0_BAUDCTRLA, USART_BSEL2_bp);
	SetBit(USARTE0_BAUDCTRLA, USART_BSEL7_bp);
	// Port B: bits 5-7
	SetBit(USARTE0_BAUDCTRLB, USART_BSCALE1_bp);
	SetBit(USARTE0_BAUDCTRLB, USART_BSCALE2_bp);
	SetBit(USARTE0_BAUDCTRLB, USART_BSCALE3_bp);
	// Stop Registers - medium setting on pins 2 and 3
	USARTE0_CTRLA = USART_TXCINTLVL_MED_gc;  
	// Enables Receiver and transmitter on port B
	SetBit(USARTE0_CTRLB, USART_RXEN_bp);
	SetBit(USARTE0_CTRLB, USART_TXEN_bp);
	// Sets communication mode to asynchronous, parity to 0, stop bit to 2, data length to 8bits
	SetBit(USARTE0_CTRLC, USART_SBMODE_bp);
	USARTE0_CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc;
	/*
	//enable port E USART pins as output
	PORTE_DIR = 0b00001000;
	// BAUD CTRL A & B sets the BAUD speed of USART connection
	USARTE0_BAUDCTRLB = 0b11100000;
	USARTE0_BAUDCTRLA = 0b10000111;
	// stop registers
	USARTE0_CTRLA = 0b10;
	//enables receiver and transmitter
	USARTE0_CTRLB = 0b00011000;
	//sets communication mode to asynchronous, no parity and stop bit to 2, with Data length to 8bits
	USARTE0_CTRLC = 0b00001011
	*/
}
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
/********************************************************************************
                        Main
********************************************************************************/
int main(void) {
    // *************************************************************************
    // initialization code & device configuration
    // *************************************************************************
    //
    system_clock_init();
    //
    // Blink an LED to make certain we are running..
    PORTR_DIR = 1; //Set port pins 0 (LED pins) to output
    for (char i=0;i<8;i++)
    {
    ToggleBit(PORTR_OUT,0);
    _delay_ms(100);
    }
    //    
    // *************************************************************************
    // main loop
    // *************************************************************************
    while (1)
    {
        ///Run Ben's code...
        ToggleBit(PORTR_OUT,0);
        _delay_ms(500);
    }
    return(0);
}
/********************************************************************************
*********************************************************************************
                        Interrupt Service Routines
*********************************************************************************
********************************************************************************/