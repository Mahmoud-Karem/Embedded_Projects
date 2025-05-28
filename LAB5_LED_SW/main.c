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
#include "SW_interface.h"

#include "avr/delay.h"

LED_Type LED1 = {LED_PORTA,LED_PIN0,ACTIVE_HIGH};
SW_Type SW1 = {DIO_PORTB , DIO_PIN0 , SW_Int_PULL_UP};

LED_Type LED2 = {LED_PORTA,LED_PIN1,ACTIVE_HIGH};
SW_Type SW2 = {DIO_PORTB , DIO_PIN1 , SW_Int_PULL_UP};


void main(void)
{
	/* Set Pin A0 as Output Pin */
	LED_voidInit(LED1);
	SW_voidInit(SW1);
	LED_voidInit(LED2);
	SW_voidInit(SW2);

	/* Toggle forever */
	while(1)
	{
		// Polling Not Interrupt

		if(SW_u8GetPressed(SW1))
		{
			LED_voidToggle(LED1);
		}

		if(SW_u8GetPressed(SW2))
		{
			LED_voidOn(LED2);
		}
		else
		{
			LED_voidOff(LED2);
		}
	}
}
