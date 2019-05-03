/******************************************************************************
 * motors.h
 * 
 * This is presently a place holder to hold all of the motor thrust vector 
 *  calculations.  There is some testbed code that can be moved here along 
 * with some of the timer counter constants found in the timer counter routines.
 *
 * Created: 8/17/2017 2:20:05 PM
 * Author :
 *
********************************************************************************/

#ifndef MOTORS_H_
#define MOTORS_H_

/********************************************************************************
						Includes
********************************************************************************/
#include "poseidon.h"

/********************************************************************************
                        Global Variables
********************************************************************************/
// The default neutral setting for the motors is 1.5mS.  This is converted to
// clock counts below.  These will be replaced by empirical values later.
// At 32MHz, our 20mS period is 10,000 clocks, so 1mS=500, 2mS=1000;
extern uint16_t motor_1_neutral_setting;
extern uint16_t motor_2_neutral_setting;
extern uint16_t motor_3_neutral_setting;
extern uint16_t motor_4_neutral_setting;
extern uint16_t motor_5_neutral_setting;
extern uint16_t motor_6_neutral_setting;

// Clock counts for servos
extern uint16_t servo_1_neutral_setting;
extern uint16_t servo_2_neutral_setting;
extern uint16_t servo_3_neutral_setting;

// Clock counts for lights
extern uint16_t light_lowest_setting;
extern uint16_t light_middle_setting;
extern uint16_t light_highest_setting;
extern uint16_t lights_off;

#endif /* MOTORS_H_ */