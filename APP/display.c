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
	SSD_setSymbol(0,SSD_0);
	SSD_setState(SSD_units,SSD_ON);
	SSD_setState(0,SSD_ON);
}

void DISP_update(void)
{

	uint16 units = CNT_getCounter()%10;
	uint16 tens = (CNT_getCounter()%100)/10;
	uint16 hundreds = (CNT_getCounter()%1000)/100;
	uint16 thousands = CNT_getCounter()/1000;
	static uint16 testCount = 0;
	static uint8 DISP_period_counter =0;
	DISP_period_counter+=OS_TICK_MS;
	if(DISP_period_counter<DISP_UPDATE_PERIOD_MS)
	{
		return;
	}
	DISP_period_counter=0;
#if 1

	SSD_setSymbol(SSD_units,units);
	SSD_setSymbol(SSD_thousands,thousands);
	SSD_setSymbol(SSD_hundreds,hundreds);
	SSD_setSymbol(SSD_tens,tens);
#else
	testCount++;
	if(testCount==10)
	{
		testCount=0;
	}
	SSD_setSymbol(SSD_units,testCount);
	SSD_setSymbol(SSD_Hundreds,5);
#endif
}
