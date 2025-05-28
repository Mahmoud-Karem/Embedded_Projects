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
	_delay_ms(500);
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_10);
	CLCD_voidSendData('*');
	_delay_ms(500);
	EEPROM_write(EEPROM_PASSWORD_LOCATION1,KPD_Return);
	KPD_Return=NOTPRESSED;

	do
	{
		KPD_Return=KPD_u8GetPressed();
	} while (KPD_Return==NOTPRESSED);
	CLCD_voidSendData(KPD_Return);
	_delay_ms(500);
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_11);
	CLCD_voidSendData('*');
	_delay_ms(500);
	EEPROM_write(EEPROM_PASSWORD_LOCATION2,KPD_Return);
	KPD_Return=NOTPRESSED;

	do
	{
		KPD_Return=KPD_u8GetPressed();
	} while (KPD_Return==NOTPRESSED);
	CLCD_voidSendData(KPD_Return);
	_delay_ms(500);
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_12);
	CLCD_voidSendData('*');
	_delay_ms(500);
	EEPROM_write(EEPROM_PASSWORD_LOCATION3,KPD_Return);
	KPD_Return=NOTPRESSED;

	do
	{
		KPD_Return=KPD_u8GetPressed();
	} while (KPD_Return==NOTPRESSED);
	CLCD_voidSendData(KPD_Return);
	_delay_ms(500);
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_13);
	CLCD_voidSendData('*');
	_delay_ms(500);
	EEPROM_write(EEPROM_PASSWORD_LOCATION4,KPD_Return);
	KPD_Return=NOTPRESSED;

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
		do
		{
			My_PW_Arr[0]=KPD_u8GetPressed();
		} while (My_PW_Arr[0]==NOTPRESSED);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_12);
		CLCD_voidSendData(My_PW_Arr[0]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_12);
		CLCD_voidSendData('*');
		_delay_ms(500);

		do
		{
			My_PW_Arr[1]=KPD_u8GetPressed();
		} while (My_PW_Arr[1]==NOTPRESSED);
		CLCD_voidSendData(My_PW_Arr[1]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_13);
		CLCD_voidSendData('*');
		_delay_ms(500);

		do
		{
			My_PW_Arr[2]=KPD_u8GetPressed();
		} while (My_PW_Arr[2]==NOTPRESSED);
		CLCD_voidSendData(My_PW_Arr[2]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_14);
		CLCD_voidSendData('*');
		_delay_ms(500);
		do
		{
			My_PW_Arr[3]=KPD_u8GetPressed();
		} while (My_PW_Arr[3]==NOTPRESSED);
		CLCD_voidSendData(My_PW_Arr[3]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_15);
		CLCD_voidSendData('*');
		_delay_ms(500);
		if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==My_PW_Arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==My_PW_Arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==My_PW_Arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==My_PW_Arr[3])
		{
			CLCD_voidClearScreen();
			CLCD_voidSendString((u8*)"Right Password");
			_delay_ms(1000);
			CLCD_voidClearScreen();
			CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
			APP_voidInitPW();
			My_Flag=1;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString((u8*)"Wrong Password");
				_delay_ms(1000);
				CLCD_voidClearScreen();
				CLCD_voidSendString((u8*)"tries left:");
				CLCD_voidSendData(tries+48);
				_delay_ms(1000);

			}
			else
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString((u8*)"Wrong Password");
				CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
				CLCD_voidSendString((u8*)"The Safe Closed");
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
		do
		{
			My_PW_Arr[0]=KPD_u8GetPressed();
		} while (My_PW_Arr[0]==NOTPRESSED);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_12);
		CLCD_voidSendData(My_PW_Arr[0]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_12);
		CLCD_voidSendData('*');
		_delay_ms(500);

		do
		{
			My_PW_Arr[1]=KPD_u8GetPressed();
		} while (My_PW_Arr[1]==NOTPRESSED);
		CLCD_voidSendData(My_PW_Arr[1]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_13);
		CLCD_voidSendData('*');
		_delay_ms(500);

		do
		{
			My_PW_Arr[2]=KPD_u8GetPressed();
		} while (My_PW_Arr[2]==NOTPRESSED);
		CLCD_voidSendData(My_PW_Arr[2]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_14);
		CLCD_voidSendData('*');
		_delay_ms(500);
		do
		{
			My_PW_Arr[3]=KPD_u8GetPressed();
		} while (My_PW_Arr[3]==NOTPRESSED);
		CLCD_voidSendData(My_PW_Arr[3]);
		_delay_ms(500);
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_15);
		CLCD_voidSendData('*');
		_delay_ms(500);
		if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==My_PW_Arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==My_PW_Arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==My_PW_Arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==My_PW_Arr[3])
		{
			CLCD_voidClearScreen();
			CLCD_voidSendString((u8*)"Right Password");
			CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
			CLCD_voidSendString((u8*)"The Safe Opened");
			My_Flag=1;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString((u8*)"Wrong Password");
				_delay_ms(1000);
				CLCD_voidClearScreen();
				CLCD_voidSendString((u8*)"tries left:");
				CLCD_voidSendData(tries+48);
				_delay_ms(1000);

			}
			else
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString((u8*)"Wrong Password");
				CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
				CLCD_voidSendString((u8*)"The Safe Closed");
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
		do
		{
			KPD_Return=KPD_u8GetPressed();
		} while (KPD_Return == NOTPRESSED );

		switch(KPD_Return)
		{
		case '1':
			CLCD_voidClearScreen();
			APP_voidEnterPW();
			break;

		case '2':
			My_Flag=0;
			CLCD_voidClearScreen();
			APP_voidSetPW();
			CLCD_voidClearScreen();
			CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
			CLCD_voidSendString((u8*)"Done ... ");
			_delay_ms(2000);
			break;

		default:
			CLCD_voidSendString((u8*)"Not Valid");
			_delay_ms(2000);
			break;
		}
	}

}

/*all Initials I need */
void APP_voidInit(void)
{
	CLCD_voidInit();
	KPD_Init();
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
