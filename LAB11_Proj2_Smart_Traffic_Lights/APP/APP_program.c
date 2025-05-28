/*
 * APP_program.c

 *
 *  Created on: 12 Oct 2022
 *      Author: Mahmoud Karem
 */

/*LIB includes */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/*MCAL includes */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/TIMER0/TIMER_interface.h"
/*HAL includes */
#include "../HAL/LED/LED_interface.h"
#include "../HAL/SWITCH/SW_interface.h"
#include "../HAL/SSD/SSD_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
/*APP includes */
#include "APP_interface.h"

/**************************************************************************/

LED_Type carRedLED = {LED_PORTB,LED_PIN0,ACTIVE_HIGH};
LED_Type carGreenLED = {LED_PORTB,LED_PIN1,ACTIVE_HIGH};
LED_Type carYellowLED = {LED_PORTB,LED_PIN2,ACTIVE_HIGH};

LED_Type pedesRedLED    = {LED_PORTA,LED_PIN3,ACTIVE_HIGH};
LED_Type pedesGreenLED  = {LED_PORTA,LED_PIN4,ACTIVE_HIGH};
LED_Type pedesYellowLED = {LED_PORTA,LED_PIN5,ACTIVE_HIGH};

SW_Type interrupt_SW = {DIO_PORTA, DIO_PIN2,SW_Int_PULL_UP};

SSD_Type SSD={SSD_COMMON_CATHODE,SSD_PORTC,SSD_PORTC,SSD_PIN7};

/**************************************************************************/

/*car LED State*/
LED_STATE_t carRed_LED    = LED_IDLE;
LED_STATE_t carGreen_LED  = LED_IDLE;
LED_STATE_t carYellow_LED = LED_IDLE;
/*pedestrian LED State*/
LED_STATE_t pedesRed_LED    = LED_IDLE;
LED_STATE_t pedesGreen_LED  = LED_IDLE;
LED_STATE_t pedesYellow_LED = LED_IDLE;

/*initial mode state*/
MODE_t modeState = NORMAL_MODE;

/**************************************************************************/

#define COV 1000
#define PreLoad_Val 125
u16 Timer_SWCounter=0;
u16 Modes_Counter=0;

/**************************************************************************/

/*All application logic*/
void APP_voidPeriodicTask(void)
{
	Timer_SWCounter ++ ;
	if (Timer_SWCounter == COV)
	{
		// Action Every One Sec
		SSD_voidSendNumber(SSD,(Modes_Counter%5));
		Modes_Counter ++ ;
		switch(modeState)
		{
		case NORMAL_MODE:
			if(Modes_Counter <= 5)
			{
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSendString((u8*)"You Can Move Now");
				LED_voidOn(pedesGreenLED);
				pedesGreen_LED = LED_ACTIVE ;
				LED_voidOff(pedesRedLED);
				pedesRed_LED = LED_IDLE;
				LED_voidOff(pedesYellowLED);
				pedesYellow_LED = LED_IDLE;

				LED_voidOn(carRedLED);
				carRed_LED = LED_ACTIVE ;
				LED_voidOff(carGreenLED);
				carGreen_LED = LED_IDLE ;
				LED_voidOff(carYellowLED);
				carYellow_LED = LED_IDLE ;
			}
			else if ((Modes_Counter > 5) && (Modes_Counter <= 10))
			{
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSendString((u8*)"Do Not Move       ");
				LED_voidOn(pedesRedLED);
				pedesRed_LED = LED_ACTIVE;
				LED_voidOff(pedesGreenLED);
				pedesGreen_LED = LED_IDLE;
				LED_voidOff(pedesYellowLED);
				pedesYellow_LED = LED_IDLE;

				LED_voidOn(carGreenLED);
				carGreen_LED = LED_ACTIVE ;
				LED_voidOff(carRedLED);
				carRed_LED = LED_IDLE ;
				LED_voidOff(carYellowLED);
				carYellow_LED = LED_IDLE ;
			}
			else if ((Modes_Counter > 10) && (Modes_Counter <= 15))
			{
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSendString((u8*)"Wait .....         ");

				LED_voidOn(pedesYellowLED);
				pedesYellow_LED = LED_ACTIVE;
				LED_voidOff(pedesGreenLED);
				pedesGreen_LED = LED_IDLE;
				LED_voidOff(pedesRedLED);
				pedesRed_LED = LED_IDLE;

				LED_voidOn(carYellowLED);
				carYellow_LED = LED_ACTIVE ;
				LED_voidOff(carRedLED);
				carRed_LED = LED_IDLE ;
				LED_voidOff(carGreenLED);
				carGreen_LED = LED_IDLE ;
				/* Reset Modes Counter */
				if (Modes_Counter==15)
				{
					Modes_Counter = 0 ;
				}
			}
			else if ((Modes_Counter > 15) && (Modes_Counter <= 20))
			{
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSendString((u8*)"Wait .....         ");
				LED_voidOff(pedesRedLED);
				pedesRed_LED = LED_IDLE;
				LED_voidOff(pedesGreenLED);
				pedesGreen_LED = LED_IDLE;

				LED_voidOff(carRedLED);
				carRed_LED = LED_IDLE ;
				LED_voidOff(carGreenLED);
				carGreen_LED = LED_IDLE ;

				LED_voidToggle(carYellowLED);
				LED_voidToggle(pedesYellowLED);
				/* Reset Modes Counter */
				if (Modes_Counter==20)
				{
					Modes_Counter = 0 ;
				}
			}


			break;
		case PEDESTRIAN_MODE:
			if((carRed_LED == LED_ACTIVE)&&(carGreen_LED == LED_IDLE)&&(carYellow_LED == LED_IDLE))
			{
				Modes_Counter = 0 ;
				modeState = NORMAL_MODE;
			}
			else if ((carRed_LED == LED_IDLE)&&((carGreen_LED == LED_ACTIVE)||(carYellow_LED == LED_ACTIVE)))
			{
				Modes_Counter = 16 ;
				modeState = NORMAL_MODE;
			}

			break;
		}

		Timer_SWCounter = 0 ;
		TIMER0_voidSetPreload(PreLoad_Val);
	}
}

/*all Initials I need */
void APP_voidInit(void)
{
	PORT_voidInit();
	SSD_voidInitialDataPort(SSD);
	SSD_voidEnable(SSD);
	CLCD_voidInit();
	EXTI_voidSetSignalLatch(EXTI_FALLING_EDGE,EXTI_LINE0);
	EXTI_voidSetCallBack(INT0_ISR,0);
	EXTI_voidEnableInterrupt(EXTI_LINE0);
	SW_voidInit(interrupt_SW);
	TIMER_u8SetCallBack(APP_voidPeriodicTask,TIMER0_CTC_VECTOR_ID);
	TIMER0_voidInit();
	GIE_VoidEnable();
}

void INT0_ISR(void)
{
	modeState = PEDESTRIAN_MODE;
}
