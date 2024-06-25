/*
 =====================================================================================
 * File Name     : application.c
 *
 * Description   : Distance Measuring Application using ultrasonc sensor
 *
 * Author        : Youssef Hossam
 ====================================================================================
 */


#include "ultrasonic_sensor.h"
#include "lcd.h"
#include <avr/io.h>

void main(){
	uint16 distance = 0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize both the LCD  and Ultrasonic sensor Driver*/
	LCD_init();

	Ultrasonic_init();

	/* display distance string on the LCD */
	LCD_displayString("distance = ");
	while(1){
		/* Read the calculated distance value using ultrasonic */
		distance = Ultrasonic_readDistance();

		/* Display distance on LCD */
		LCD_moveCursor(0,10);
		LCD_intgerToString(distance);
		LCD_displayString(" cm");

		/* To override the additional digit shown after decrementing distance from 100 to less than */
		if (distance < 100) {
			LCD_displayCharacter(' ');
		}
	}
}
