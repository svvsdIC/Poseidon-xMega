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

// Light frequency is going to be 400 Hz, prescalar is 8
#define LIGHT_FREQ 400UL // This is the lowest frequency we could get that was still above 240 Hz
#define LIGHT_PRESCALER 8UL
#define LIGHT_TOP_COUNT F_CPU/(LIGHT_FREQ*LIGHT_PRESCALER)-1


/********************************************************************************
                        Function Prototypes
********************************************************************************/
void timer_counter_F0_init(uint16_t topcount);

/********************************************************************************
                        Global Variables
********************************************************************************/
// The default neutral setting for the motors is 1.5mS.  This is converted to
// clock counts below.  These will be replaced by empirical values later

// Clock counts for RGB lights
uint16_t light_lowest_setting = .25*10000;
uint16_t light_middle_setting = .5*10000;
uint16_t light_highest_setting = .99*10000;

/********************************************************************************
                        Functions
********************************************************************************/
void timer_counter_F0_init(uint16_t topcount) {
	//
	// This routine initializes the timer counters on PORT C to support driving
	// Electronic Speed Controllers (ESCs) via the single slope PWM operating mode
	//
	// From the XMEGA data sheet, to make the waveform visible on the
	// connected port pin, the following requirements must be fulfilled
	// 1. A waveform generation mode must be selected.
	// 2. Event actions must be disabled.
	// 3. The CC channels used must be enabled. This will override the
	//        corresponding port pin output register.
	// 4. The direction for the associated port pin must be set to output.
	// ...so, let's do it...
	// Set the data direction register for the PORT C PWM pins.
	// The output register pins are c0 through C5, set them to output:
	PORTD_DIR=0b00000111;
	//
	// Set the clock prescaler to 64.  From table 14-3:
	TCD0_CTRLA = 0b00000101;
	//
	// Enable the compare enable functions: See 14.12.2
	// Set WGM=0b011, which is single slope PWM.  See 14.12.2
	TCD0_CTRLB = TC0_CCAEN_bm | TC0_CCBEN_bm  | TC0_CCCEN_bm | TC0_CCDEN_bm | 0b00000011;
	//
	// Ensure event actions are turned OFF
	TCD0_CTRLD = 0b00000000 | 0b00000000;
	//
	// Nothing to set in TCCx control registers C, and E.
	//
	// Ensure timer/counters are enabled for port C (See 8.7.3)
	ClearBit(PR_PRPD, PR_TC0_bp);
	//
	// Set the TOP count in the Input Compare Register PER registers
	// This is a 16 bit register, so we should block interrupts when
	// writing to it, but interrupts should not yet be enabled...
	//
	TCD0_PER = topcount;
	//
	// We now need to set the output compare registers to a value that will
	// prevent the motors from spinning.  To do this. we need calibrated values
	// from a dataset loaded somewhere...like EEPROM.  FOr now, we'll use the
	// defaults calculated in the global variables above.
	// Again, we should write these after disabling interrupts, but since this
	// should run BEFORE interrupts are enabled, we should be OK.
	
	// We are assigning only one of each setting to each pin, however
	// the structure will have to be altered later so that each pin can access
	// each setting.
	TCD0_CCA = light_lowest_setting;
	TCD0_CCB = light_middle_setting;
	TCD0_CCC = light_highest_setting;
	//
	// Timer Counters 0 and 1 should now be set up on PORTC
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
    // Initialize timer counters...
    //timer_counter_C0_C1_D0_init(ESC_TOP_COUNT);
	timer_counter_F0_init(LIGHT_TOP_COUNT);
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