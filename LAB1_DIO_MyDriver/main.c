/*

 * main.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Mahmoud Karem
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "avr/delay.h"

void main(void)
{
	/* Set Pin A0 as Output Pin */
	DIO_enumSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);

	/* Toggle forever */
	while(1)
	{
		DIO_enumSetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
		_delay_ms(1000);

		DIO_enumSetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
		_delay_ms(1000);
	}
}
