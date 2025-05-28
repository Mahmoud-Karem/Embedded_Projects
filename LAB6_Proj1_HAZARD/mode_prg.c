/******************************************************************************/
/*                                                                            */
/* !Layer           : Application Abstraction Layer                           */
/*                                                                            */
/* !Component       : MODE                                                    */
/* !Description     : Hazzard Indicator Function module                       */
/*                                                                            */
/* !Module          : MODE                                                    */
/* !Description     : MODE Module interface                                   */
/*                                                                            */
/* !File            : mode_prg.c                                              */
/*                                                                            */
/* !Scope           : Private                                                 */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Induction training exercise project                     */
/*                                                                            */
/* !Target          : ATMega32                                                */
/*                                                                            */
/* !Compiler        : AVR GCC Cross Compiler                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Coded by        : Mahmoud Karem Zamel             !Date : NOV 21, 2023    */
/*                                                                            */
/******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SW_interface.h"
#include "SSD_interface.h"
#include "CLCD_interface.h"


#include "mode_int.h"

/******************************************************************************/

MODE_enutModeState Mode_MyState;

u8 u8PreviousState = IDLE;

/*****************************************************************************************/
extern SSD_Type R_SSD ;
extern SSD_Type L_SSD ;

extern SW_Type R_SW ;
extern SW_Type L_SW ;
extern SW_Type H_SW ;
/*****************************************************************************************/

/******************************************************************************/
/*! \Description Helper Functions                                             */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
void APP_vidSetMode(MODE_enutModeState enutSetMode)
{
	switch(enutSetMode)
	{
	case IDLE:
		// SSD For IDLE
		SSD_voidDisable(R_SSD);
		SSD_voidDisable(L_SSD);
		// CLCD For IDLE
		CLCD_voidSendString((u8*)"IDLE MODE");
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		break;

	case RIGHT_BLINK:
		// SSD For Right
		SSD_voidEnable(R_SSD);
		SSD_voidDisable(L_SSD);
		SSD_voidSendNumber(R_SSD,0);
		// CLCD For Right
		CLCD_voidSendString((u8*)"RIGHT BLINK MODE");
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		break;

	case LEFT_BLINK:
		// SSD For Left
		SSD_voidEnable(L_SSD);
		SSD_voidDisable(R_SSD);
		SSD_voidSendNumber(L_SSD,0);
		// CLCD For Left
		CLCD_voidSendString((u8*)"LEFT BLINK MODE");
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		break;

	case HAZZARD_BLINK:
		// SSD For Hazard
		SSD_voidEnable(R_SSD);
		SSD_voidEnable(L_SSD);
		SSD_voidSendNumber(R_SSD,0);
		SSD_voidSendNumber(L_SSD,0);
		// CLCD For Hazard
		CLCD_voidSendString((u8*)"HAZARD MODE");
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		break;
	}

}

/***************************************/
void MODE_vidIdle (void)
{
	APP_vidSetMode(IDLE);
	if(SW_u8GetPressed(L_SW))
	{
		Mode_MyState = LEFT_BLINK;
	}
	else if(SW_u8GetPressed(R_SW))
	{
		Mode_MyState = RIGHT_BLINK;
	}
	else if(SW_u8GetPressed(H_SW))
	{
		u8PreviousState = IDLE;
		Mode_MyState = HAZZARD_BLINK;
	}
}
void MODE_vidRightBlink (void)
{
	APP_vidSetMode(RIGHT_BLINK);
	if(SW_u8GetPressed(L_SW))
	{
		Mode_MyState = IDLE;
	}
	else if(SW_u8GetPressed(R_SW))
	{
		Mode_MyState = RIGHT_BLINK;
	}
	else if(SW_u8GetPressed(H_SW))
	{
		u8PreviousState = RIGHT_BLINK;
		Mode_MyState = HAZZARD_BLINK;
	}
}
void MODE_vidLeftBlink (void)
{
	APP_vidSetMode(LEFT_BLINK);
	if(SW_u8GetPressed(L_SW))
	{
		Mode_MyState = LEFT_BLINK;
	}
	else if(SW_u8GetPressed(R_SW))
	{
		Mode_MyState = IDLE;
	}
	else if(SW_u8GetPressed(H_SW))
	{
		u8PreviousState = LEFT_BLINK;
		Mode_MyState = HAZZARD_BLINK;
	}
}
void MODE_vidHazardBlink (void)
{
	APP_vidSetMode(HAZZARD_BLINK);
	if(SW_u8GetPressed(L_SW))
	{
		Mode_MyState = HAZZARD_BLINK;
	}
	else if(SW_u8GetPressed(R_SW))
	{
		Mode_MyState = HAZZARD_BLINK;
	}
	else if(SW_u8GetPressed(H_SW))
	{
		Mode_MyState = u8PreviousState;
	}
}


/*****************************************************************************************/

/******************************************************************************/
/*! \Description Initialize the MODE driver variables                         */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
void MODE_vidInit(void)
{
	Mode_MyState  = IDLE;
	APP_vidSetMode(IDLE);
}

/******************************************************************************/
/*! \Description The MODE driver task, should be called periodically.
				 This service update the state of all configured push
                 buttons.                                                     */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
void MODE_vidTask(void)
{
	if(Mode_MyState == IDLE)
	{
		MODE_vidIdle();
	}
	else if(Mode_MyState == RIGHT_BLINK)
	{
		MODE_vidRightBlink();
	}
	else if(Mode_MyState == LEFT_BLINK)
	{
		MODE_vidLeftBlink();
	}
	else if(Mode_MyState == HAZZARD_BLINK)
	{
		MODE_vidHazardBlink();
	}
}

/**********************************************************************************************/
