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

/**************************** Includes Section ********************************/

#include "ultrasonic_sensor.h"
#include "std_types.h"
#include "gpio.h"
#include "icu.h"
#include "util/delay.h"
/************************ Global Variables Section ****************************/

	uint16 g_timeHigh = 0;

/**************************** Functions Definition Section *********************/
/*=====================================================================
* @brief  : function to initialize ultrasonic sensor module
* @param  : function takes nothing
* @retVal : function returns nothing
*
* ====================================================================
*/
void Ultrasonic_init(void){
	/* Create configuration structure for ICU driver */
		ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	/* initialize icu with the required configuration */
	ICU_init(&ICU_Configurations);
	/* set the call back function of the icu called in the icu ISR */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	/* Setup the direction of the trigger pin as an output pin */
	GPIO_setupPinDirection(UlTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
	}
/*=========================================================================================
 * @brief  : function to initialize trigger pin of ultrasonic and write output on it
 * @param  : function takes nothing
 * @retVal : function returns nothing
 *
 * ========================================================================================
 */
void Ultrasonic_Trigger(void){
		/* write logic high on the trigger pin of the ultrasonic to send radio wave */
			GPIO_writePin(UlTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
		/* make the period of the pulse 10 microsecond */
			_delay_us(10);
		/* write logic low on the trigger pin of the ultrasonic to end the pulse */
			GPIO_writePin(UlTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
	}

/*=======================================================================
 * @brief  : function to read distance measured by the ultrasnoic sensor
 * @param  : function takes nothing
 * @retVal : function returns distance measured
 *
 * ======================================================================
 */
uint16 Ultrasonic_readDistance(void){
			uint16 distance = 0;
			/* send the radio wave on the trigger pin */
			Ultrasonic_Trigger();
			/* measure the distance */
			distance = (g_timeHigh/58) ;
			return distance;
	}

/*=====================================================================
 * @brief  : function to measure the time of the echo pulse
 * @param  : function takes nothing
 * @retVal : function returns nothing
 *
 * ====================================================================
 */
void Ultrasonic_edgeProcessing(void){
		static uint8 g_edgeCount = 0;
		g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			ICU_clearTimerValue();
			/* Detect falling edge */
			ICU_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = ICU_getInputCaptureValue();
			g_edgeCount = 0;
			/* Detect rising edge */
			ICU_setEdgeDetectionType(RAISING);
		}
	}

