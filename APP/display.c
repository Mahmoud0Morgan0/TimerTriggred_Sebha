/*
 * display.c
 *
 *  Created on: May 29, 2020
 *      Author: jenki
 */

/**********************************************************************
* Includes
**********************************************************************/
#include"display.h"
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
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
void Disp_init(void)
{
	SSD_setSymbol(SSD_units,SSD_0);
	SSD_setSymbol(SSD_Hundreds,SSD_0);
	SSD_setState(SSD_units,SSD_ON);
	SSD_setState(SSD_Hundreds,SSD_ON);
}

void DISP_update(void)
{

	uint16 units = CNT_getCounter()%10;
	uint16 hundreds = CNT_getCounter()/10;
	static uint8 DISP_period_counter =0;
	DISP_period_counter+=OS_TICK_MS;
	if(DISP_period_counter<DISP_UPDATE_PERIOD_MS)
	{
		return;
	}
	DISP_period_counter=0;
	SSD_setSymbol(SSD_units,units);
	SSD_setSymbol(SSD_Hundreds,hundreds);
}
