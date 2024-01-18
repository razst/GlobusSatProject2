/*
 * common.h
 *
 * Contains functions that are used in across multiple demo's
 *
 *  Created on: 5 okt. 2015
 *      Author: lrot
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <hal/boolean.h>

#include <stddef.h>

typedef enum INGRV_enum	// input number generic return values
{
	 INGRV_val = 0,		// input number valid
	 INGRV_inv = 1,		// input number invalid
	 INGRV_rng = 2,		// input number out of specified range
	 INGRV_esc = 3		// user pressed escape twice to indicate aborting input
} INGRV_e;

typedef enum CONFIG_PARAM_OP_enum				//!< configuration param printing an getting user input function
{
	CONFIG_PARAM_OP_ask_parid = 0,				///!< ask user for the parameter-id
	CONFIG_PARAM_OP_ask_parid_and_data = 1,		///!< ask user for param-id and its data
	CONFIG_PARAM_OP_print = 2					///!< show parameter id and data to the user
} CONFIG_PARAM_OP_e;

typedef struct __attribute__ ((__packed__)) WOD_Telemetry_t
{
	unsigned short vbat;					///< the current voltage on the battery [mV]
	unsigned short volt_5V;				///< the current voltage on the 5V bus [mV]
	unsigned short volt_3V3;				///< the current voltage on the 3V3 bus [mV]
	unsigned short charging_power;			///< the current charging power [mW]
	unsigned short consumed_power;			///< the power consumed by the satellite [mW]
	unsigned short electric_current;		///< the up-to-date electric current of the battery [mA]
	unsigned short current_3V3;			///< the up-to-date 3.3 Volt bus current of the battery [mA]
	unsigned short current_5V;			///< the up-to-date 5 Volt bus current of the battery [mA]
	unsigned short mcu_temp; 				/*!< Measured temperature provided by a sensor internal to the MCU in raw form */
	unsigned short bat_temp; 				/*!< 2 cell battery pack: not used 4 cell battery pack: Battery pack temperature on the front of the battery pack. */
	//int32_t solar_panels[6];                // temp of each solar panel
	unsigned long sat_time;				///< current Unix time of the satellites clock [sec]
	unsigned int free_memory;		///< number of bytes free in the satellites SD [byte]
	unsigned int corrupt_bytes;		///< number of currpted bytes in the memory	[bytes]
	unsigned int number_of_resets;	///< counts the number of resets the satellite has gone through [#]
	unsigned long sat_uptime;			///< Sat uptime
	unsigned int photo_diodes[5]; 			// photo diodes
	unsigned int num_of_cmd_resets;///< counts the number of resets the satellite has gone through due to ground station command [#]
} WOD_Telemetry_t;


/***
 * input number generic (ING) user input request functions
 * provides a scanf style input function that includes watchdog petting in the data request loop
 * it is used to get user input.
 */
INGRV_e ing_interact(char *p_head, char *p_buf, size_t buf_sz, size_t *p_gotten_sz);
INGRV_e ing_parse(double *p_value, char *p_buf, size_t buf_sz, double min, double max, double def);
INGRV_e ing(char *p_head, double *p_value, double min, double max, double def);

/***
 * prints typed configuration parameters and gets parameter id and values from the user
 * depending on the requested operation.
 * Used with the generic configuration parameter system of the IMTQ and IEPS.
 */
Boolean config_param_info(CONFIG_PARAM_OP_e op, unsigned short* p_param_id, void* vp_param_data);

/***
 * prints an error message if the error code differs from 0
 */
void print_error(int error);

/***
 *
 */
int createSendBeaconTask();
/***
 *
 */
int sendBeaconTask(void* args);
/***
 *
 */
WOD_Telemetry_t createRandBeacon();
#endif /* COMMON_H_ */
