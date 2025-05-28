/*
 * APP_program.c

 *
 *  Created on: 12 Oct 2022
 *      Author: Mahmoud Karem
 */

#include <util/delay.h>

/*LIB includes */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/*MCAL includes */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/EEPROM/EEPROM_driver.h"
/*HAL includes */
#include "../HAL/LED/LED_interface.h"
#include "../HAL/SWITCH/SW_interface.h"
#include "../HAL/SSD/SSD_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
#include "../HAL/KPD/KPD_interface.h"
/*APP includes */
#include "APP_interface.h"

/**************************************************************************/

SSD_Type SSD={SSD_COMMON_CATHODE,SSD_PORTC,SSD_PORTC,SSD_PIN7};

/**************************************************************************/

u8 KPD_Return=NOTPRESSED;


#define EEPROM_STATUS_LOCATION    0x20
#define EEPROM_PASSWORD_LOCATION1 0x21
#define EEPROM_PASSWORD_LOCATION2 0x22
#define EEPROM_PASSWORD_LOCATION3 0x23
#define EEPROM_PASSWORD_LOCATION4 0x24

#define MAX_TRIES 3

u8 My_PW_Arr[4];
u8 My_Flag=0;

/**************************************************************************/
/*********************    Helper Functions   ******************************/
/**************************************************************************/

static void APP_voidInitPW(void)
{
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
	CLCD_voidSendString((u8*)"Set P.W: ");
	do
	{
		KPD_Return=KPD_u8GetPressed();
	} while (KPD_Return==NOTPRESSED);
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_10);
	CLCD_voidSendData(KPD_Return);
	//Take-->KPD_Return(4--->****)
	//EEPROM_Write	--->	for	each	*

	EEPROM_write(EEPROM_STATUS_LOCATION,0x00);

}
static void APP_voidSetPW(void)
{
	u8 tries=MAX_TRIES;
	while(My_Flag==0)
	{
		My_PW_Arr[0] = My_PW_Arr[1] = My_PW_Arr[2] = My_PW_Arr[3] = NOTPRESSED;
		CLCD_voidClearScreen();
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		CLCD_voidSendString((u8*)"Enter PW : ");

		//Take-->KPD_Return(4--->****)-->Store_at_Array
		//Comp_Using-->	EEPROM_Read	(4)	-->	Right/Wrong Password


		if(...)
		{
			//Right Password
			APP_voidInitPW();
			My_Flag=1;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				//Wrong Password	-->	tries left:


			}
			else
			{
				//The Safe Closed
				while(1);
				break;
			}
		}
	}


}

/************/
static void APP_voidEnterPW(void)
{
	u8 tries=MAX_TRIES;
	while(My_Flag==0)
	{
		My_PW_Arr[0] = My_PW_Arr[1] = My_PW_Arr[2] = My_PW_Arr[3] = NOTPRESSED;
		CLCD_voidClearScreen();
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		CLCD_voidSendString((u8*)"Enter PW : ");

		//Take-->KPD_Return(4--->****)-->Store_at_Array
		//Comp_Using-->	EEPROM_Read	(4)	-->	Right/Wrong Password


		if(...)
		{
			//Right Password
			APP_voidInitPW();
			My_Flag=1;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				//Wrong Password	-->	tries left:


			}
			else
			{
				//The Safe Closed
				while(1);
				break;
			}
		}
	}

}

/**************************************************************************/
/**************************************************************************/
/**************************************************************************/


/*All application logic*/
void APP_voidAppLoop (void)
{

	while(My_Flag==0)
	{
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		CLCD_voidSendString((u8*)"Enter Num (1,2) :");
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
		CLCD_voidSendString((u8*)"Open , Change PW");
		//algorithm
		}
	}

}

/*all Initials I need */
void APP_voidInit(void)
{
	//Init_All
	/***************/
	CLCD_voidSendString((u8*)"Welcome .....         ");
	_delay_ms(2000);
	CLCD_voidClearScreen();
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);

	/* Set P.W ---> EEPROM */
	if(EEPROM_read(EEPROM_STATUS_LOCATION)==NOTPRESSED)
	{
		APP_voidInitPW();
	}
}


/**************************************************************************/
