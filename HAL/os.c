/*
 * os.c
 *
 *  Created on: May 11, 2020
 *      Author: jenki
 */

/**********************************************************************
* Includes
**********************************************************************/
#include"os.h"
#include"dio.h"
#include"../ECAL/PushButton.h"
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/
/**********************************************************************
* Module Typedefs
**********************************************************************/
/**********************************************************************
* Module Variable Definitions
**********************************************************************/
volatile uint8 OS_flag =0;
volatile uint8 OS_counter = 0;
uint16 Tick ;
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
void OS_init (const TMR0Config_t * const config,uint16 period)
{
	TMR0_Init(config);
	INT_setGlobalInterrupt();
	INT_enableInterrupt(TIMER0_COMP);
	INT_callbackRegister(TIMER0_COMP_VECTOR,OS_countPeriod);
	loadOCR(125);
	Tick = period ;
}
void OS_countPeriod(void)
{
	
	OS_counter++;

	if(OS_counter==Tick)
	{
		OS_counter=0;
		OS_flag=1;
	}
}
void OS_schedule(void)
{

	if(OS_flag==1)
	{
		//tasks
		//Dio_ChannelToggle(PORTA_ID,_PIN4);

		SSD_update();
		PB_update();
		DISP_update();
		CNT_update();

		OS_flag=0;
		//sleep
	}
}








