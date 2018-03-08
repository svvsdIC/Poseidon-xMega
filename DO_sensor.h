/*
 * DO_sensor.h
 *
 * Created: 2/8/2018 5:27:11 PM
 *  Author: tran.michel02
 */ 


#ifndef DO_SENSOR_H_
#define DO_SENSOR_H_

/*
Header File for Dissolved Oxygen Sensor
Project: Innovation Center's Project Poseidon
Created: 1/25/18
*/

// Define DO sensor address
#define DO_sensor_address 0x61

// DO sensor commands
// Initialization
#define DO_factory_reset "Factory"
#define DO_read_device_info	"i"
#define DO_remove_param "O"
#define DO_save_cal "Export"
#define DO_load_cal "Import"
#define DO_toggle_LED "L"
#define DO_enable_saturation "O,%,1"
#define DO_status "Status"
uint8_t DO_data_collection[6];
// Calibration
#define DO_cal "Cal"
#define DO_pressure "P"
#define DO_salinity "S"
#define DO_temp "T"
// Measurement
#define DO_return_read "R"
#define DO_sleep "Sleep"

// Function Prototypes
void DO_initialization(void);
// uint8_t DO_calibration(void);
// uint8_t DO_compensation(void);
// uint8_t DO_read(void);




#endif /* DO_SENSOR_H_ */