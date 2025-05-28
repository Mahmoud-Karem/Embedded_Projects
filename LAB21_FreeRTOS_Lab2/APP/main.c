

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../HAL/CLCD/CLCD_interface.h"


#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"

#include <util/delay.h>

//#define TASK2_PRIORITY (1)
//#define TASK1_PRIORITY (2) //Highest

/* Shared Resource Problem */
#define TASK2_PRIORITY (1)
#define TASK1_PRIORITY (1)

#define TASK1_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define TASK2_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)

void CLCD_TASK1(void *pvParamter);
void CLCD_TASK2(void *pvParamter);

u8 CLCD_Flag=1;

int main(void)
{

	CLCD_voidInit();
	/*Create tasks*/
	xTaskCreate(CLCD_TASK1, NULL, TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(CLCD_TASK2, NULL, TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	/*start Scheduler */
	vTaskStartScheduler();

	return 0;
}

void CLCD_TASK1(void *pvParamter)
{
	for (;;)
	{
		if (CLCD_Flag==1)
		{
			CLCD_Flag=0;
			CLCD_voidClearScreen();
			CLCD_voidSendString((u8 *)"Task 1 :");
			CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
			CLCD_voidSendString((u8 *)"I am Task 1");
			CLCD_Flag=1;
		}
		vTaskDelay(1000);
	}
}
void CLCD_TASK2(void *pvParamter)
{
	for (;;)
	{
		if (CLCD_Flag==1)
		{
			CLCD_Flag=0;
			CLCD_voidClearScreen();
			CLCD_voidSendString((u8 *)"Task 2 :");
			CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
			CLCD_voidSendString((u8 *)"I am Task 2");
			CLCD_Flag=1;
		}
		vTaskDelay(1000);
	}
}
