/*
 * counter.c
 *
 *  Created on: May 29, 2020
 *      Author: jenki
 */

/**********************************************************************
* Includes
**********************************************************************/
#include"counter.h"
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
uint16 CNT_counter = 0;
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
void CNT_init(uint16 c)
{
	CNT_counter=c;
}
void CNT_update()
{
	PB_state_t state;
	static uint8 CNT_period_counter=0;
	CNT_period_counter+=OS_TICK_MS;
	if(CNT_period_counter<CNT_UPDATE_PERIOD_MS)
	{
		return;
	}
	CNT_period_counter=0;
	PB_getButtonState(PB_RESET,&state);
	if(state==PB_PRESSED)
	{
		CNT_counter=0;
	}
	PB_getButtonState(PB_COUNTER,&state);
	if(state==PB_PRESSED)
	{
		CNT_counter++;
		if(CNT_counter==100)
		{
			CNT_counter=0;
		}
	}
}
uint16 CNT_getCounter()
{
	return CNT_counter;
}
