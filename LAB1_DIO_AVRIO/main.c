/*

 * main.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Mahmoud Karem
 */


#include "avr/io.h"
#include "avr/delay.h"

void main(void)
{
	/* Set Pin A0 as Output Pin */
	DDRA = 0x01;


	/* Toggle forever */
	while(1)
	{
		PORTA = 0x01;
		_delay_ms(1000);

		PORTA = 0;
		_delay_ms(1000);
	}
}
