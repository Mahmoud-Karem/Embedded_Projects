/*

 * main.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Mahmoud
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SSD_interface.h"

#include "avr/delay.h"

SSD_Type SSD1 = {SSD_COMMON_CATHODE,SSD_PORTA,SSD_PORTA,SSD_PIN7};

void main ()
{
	SSD_voidInitialDataPort(SSD1);

	while(1)
	{

		for (int i=0 ; i<10 ; i++)
		{
			SSD_voidSendNumber(SSD1,i);
			_delay_ms(1000);
		}
	}
}
