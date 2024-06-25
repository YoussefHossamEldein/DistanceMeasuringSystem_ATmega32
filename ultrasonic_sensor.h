 /*==================================================================================
 *
 * Module      : ultrasonic sensor
 *
 * File Name   : ultrasonic_sensor.h
 *
 * Description : header file for ultrasonic sensor device
 *
 * Author      : Youssef Hossam
 *
 *====================================================================================
 */

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_
/********************************** Includes Section ************************/
#include "std_types.h"

/********************************** Data Types Section *********************/


/***************************** Macro Definition Section ********************/
#define UlTRASONIC_TRIGGER_PORT_ID			PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID			PIN5_ID

/***************************** Macro Functions Section *********************/

/**************************** Functions Declaration Section ****************/
/*=====================================================================
 * @brief  : function to initialize ultrasonic sensor module
 * @param  : function takes nothing
 * @retVal : function returns nothing
 *
 * ====================================================================
 */
void Ultrasonic_init(void);
/*=========================================================================================
 * @brief  : function to initialize trigger pin of ultrasonic and write output on it
 * @param  : function takes nothing
 * @retVal : function returns nothing
 *
 * ========================================================================================
 */
void Ultrasonic_Trigger(void);
/*=======================================================================
 * @brief  : function to read distance measured by the ultrasnoic sensor
 * @param  : function takes nothing
 * @retVal : function returns distance measured
 *
 * ======================================================================
 */
uint16 Ultrasonic_readDistance(void);
/*=====================================================================
 * @brief  : function to measure the time of the echo pulse
 * @param  : function takes nothing
 * @retVal : function returns nothing
 *
 * ====================================================================
 */
void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_SENSOR_H_ */
