/*

 * main.c
 *
 *  Created on: Sep 10, 2022
 *      Author: Mahmoud Karem
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"


#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../RTOS/semphr.h"

#include "avr/delay.h"

void LCD1(void * pv);
void LCD2(void * pv);

xSemaphoreHandle LCDSem ;
void main()
{
	CLCD_voidInit();

	xTaskCreate(&LCD1,NULL,250,NULL,0,NULL);
	xTaskCreate(&LCD2,NULL,250,NULL,0,NULL);

	LCDSem = xSemaphoreCreateCounting (1,1);

	vTaskStartScheduler();
	while(1)
	{

	}
}

void LCD1(void * pv)
{
	u8 Local_u8SemState;
	while(1)
	{
		/* Try to take the semaphore */
		Local_u8SemState = xSemaphoreTake(LCDSem,0);
		CLCD_voidClearScreen();
		if (Local_u8SemState==pdPASS)
		{
			/* semaphore is taked , Access LCD */
			CLCD_voidSendString("I AM TASK1!");
			_delay_ms(100);
			/* Access is finished ,give the semaphore now */
			xSemaphoreGive(LCDSem);
		}
		vTaskDelay(1000);
	}
}
void LCD2(void * pv)
{
	u8 Local_u8SemState;
	while(1)
	{
		/* Try to take the semaphore */
		Local_u8SemState = xSemaphoreTake(LCDSem,0);
		CLCD_voidClearScreen();
		if (Local_u8SemState==pdPASS)
		{
			/* semaphore is taked , Access LCD */
			CLCD_voidSendString("I AM TASK2!");
			_delay_ms(100);
			/* Access is finished ,give the semaphore now */
			xSemaphoreGive(LCDSem);
		}
		vTaskDelay(1000);
	}
}
