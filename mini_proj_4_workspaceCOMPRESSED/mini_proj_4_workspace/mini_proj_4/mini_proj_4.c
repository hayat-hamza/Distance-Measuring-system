/*
 * mini_proj_4.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Hayat Hussein
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

extern uint8 g_edgeCount;

int main()
{
	uint16 distance=0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	LCD_init(); /*initialize the LCD*/
	Ultrasonic_init(); /*initialize the ultrasonic*/
	//LCD_displayString("Distance =   %"); /*display only once*/
	while(1)
	{

		if(g_edgeCount == 2)
		{
			g_edgeCount = 0;
			/*
			 * return cursur to original position
			 */
			LCD_moveCursor(0,0);
			LCD_displayString("Duty =");
			/* get the distance */
			distance = Ultrasonic_readDistance();
			/* display the distance on LCD screen */
			LCD_intgerToString(distance);
			LCD_displayString("cm ");
		}
	}
}


