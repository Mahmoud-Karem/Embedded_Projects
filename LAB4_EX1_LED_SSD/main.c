/*

 * main.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Mahmoud
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SSD_interface.h"
#include "LED_interface.h"
#include "BUZ_interface.h"

#include "avr/delay.h"

SSD_Type SSD = {SSD_COMMON_CATHODE,SSD_PORTA,SSD_PORTA,SSD_PIN7};
LED_Type LEDS[8] = {{LED_PORTB,LED_PIN0,ACTIVE_HIGH},{LED_PORTB,LED_PIN1,ACTIVE_HIGH},
		{LED_PORTB,LED_PIN2,ACTIVE_HIGH},{LED_PORTB,LED_PIN3,ACTIVE_HIGH},
		{LED_PORTB,LED_PIN4,ACTIVE_HIGH},{LED_PORTB,LED_PIN5,ACTIVE_HIGH},
		{LED_PORTB,LED_PIN6,ACTIVE_HIGH},{LED_PORTB,LED_PIN7,ACTIVE_HIGH}};
BUZ_Type BUZ = {BUZ_PORTC,BUZ_PIN0,ACTIVE_HIGH};

void main ()
{
	SSD_voidInitialDataPort(SSD);
	SSD_voidEnable(SSD);
	for (int i=0 ; i<8 ; i++)
	{
		LED_voidInit(LEDS[i]);
	}
	BUZ_voidInit(BUZ);


	while(1)
	{

		for (int i=0 ; i<9 ; i++)
		{
			if (i==0)
			{
				for (int j=0 ; j<8 ; j++)
				{
					LED_voidOff(LEDS[j]);
					BUZ_voidOff(BUZ);
				}
				SSD_voidSendNumber(SSD,i);
				_delay_ms(1000);
				continue;
			}

			LED_voidOn(LEDS[i-1]);
			SSD_voidSendNumber(SSD,i);
			if (i==8)
			{
				BUZ_voidOn(BUZ);
			}
			_delay_ms(1000);
		}
	}
}
