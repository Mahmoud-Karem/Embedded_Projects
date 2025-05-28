/*

 * main.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Mahmoud Karem
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "avr/delay.h"

LED_Type LED1 = {LED_PORTA,LED_PIN0,ACTIVE_HIGH};

void main(void)
{
	/* Set Pin A0 as Output Pin */
	LED_voidInit(LED1);

	/* Toggle forever */
	while(1)
	{
		LED_voidToggle(LED1);
		_delay_ms(1000);
	}
}
