#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "FreeRTOS.h"
#include "task.h"

void LED1(void *pv);
void LED2(void *pv);
void LED3(void *pv);

#define TASK3_PRIORITY (0)
#define TASK2_PRIORITY (1)
#define TASK1_PRIORITY (2)

#define TASK1_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define TASK2_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define TASK3_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)


void main(void)
{
	PORT_voidInit();
	xTaskCreate(LED1,NULL,TASK1_STACK_SIZE,NULL,TASK1_PRIORITY,NULL);
	xTaskCreate(LED2,NULL,TASK2_STACK_SIZE,NULL,TASK2_PRIORITY,NULL);
	xTaskCreate(LED3,NULL,TASK3_STACK_SIZE,NULL,TASK3_PRIORITY,NULL);

	vTaskStartScheduler();
}

void LED1(void *pv)
{
	while(1)
	{
		DIO_enumTogglePinValue(PORTA,DIO_PIN0);
		vTaskDelay(1000);
	}
}
void LED2(void *pv)
{
	while(1)
	{
		DIO_enumTogglePinValue(PORTA,DIO_PIN1);
		vTaskDelay(2000);
	}
}
void LED3(void *pv)
{
	while(1)
	{
		DIO_enumTogglePinValue(PORTA,DIO_PIN2);
		vTaskDelay(3000);
	}
}



