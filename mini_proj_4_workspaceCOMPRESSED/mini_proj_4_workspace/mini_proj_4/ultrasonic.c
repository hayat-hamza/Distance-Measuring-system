/*
 * ultrasonic.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Hayat Hussein
 */
#include "ultrasonic.h"
#include "gpio.h"
#include <util/delay.h>


uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void Ultrasonic_init(void)
{
	/*
	 * - Initialize the ICU driver as required.
	 */
	ultrasonic_config.clock=F_CPU_8;
	ultrasonic_config.edge=RISING;
	Icu_init(&ultrasonic_config);
	/*
	 * - Setup the ICU call back function.
	 */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/*
	 * Setup the direction for the trigger pin as output pin through the GPIO driver
	 */

	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
}
/*
 * Description
- Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID,PIN5_ID,1);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,0);

}
/*
 * Description
- Send the trigger pulse by using Ultrasonic_Trigger function.
- Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void)
{
	 /*Send the trigger pulse*/
	Ultrasonic_Trigger();
/*
 * ICU measurements
 */
    return ((float)g_timeHigh/58.8);
}

/*
 * Description
- This is the call back function called by the ICU driver.
- This is used to calculate the high time (pulse time) generated by
the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}

}
