/*

 * main.c
 *
 *  Created on: Mar 20, 2023
 *      Author: Mahmoud Karem
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"

#include "LED_interface.h"
#include "CLCD_interface.h"
#include "LM35_interface.h"

u8 LM35_V = 0;
/***********************************************/

LED_Type LED1={LED_PORTC,LED_PIN0,ACTIVE_HIGH};

LM35_CONFIG LM35_S = {ADC_CHANNEL0,AVCC,ADC_RESOLUTION_8_BIT};

/***********************************************/

static void APP_Init()
{
	ADC_voidInit();
	CLCD_voidInit();
	LED_voidInit(LED1);
	LED_voidOff(LED1);
}

/***********************************************/
int main ()
{
	APP_Init();
	CLCD_voidSendString((u8 *)"LearnPlusPlus :)");
	while(1)
	{
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_2);
		CLCD_voidSendString((u8 *)"Temp = ");
		LM35_u8GetTemp(&LM35_S,&LM35_V);
		CLCD_voidSendNumber(LM35_V);
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_12);
		CLCD_voidSendString((u8 *)" C");

		if (LM35_V >= 20)
		{
			LED_voidOn(LED1);
		}
		else
		{
			LED_voidOff(LED1);
		}
	}
	return 0;
}
