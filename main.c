/*
 * main.c
 *
 *  Created on: Apr 25, 2020
 *      Author: jenki
 */
#include "HAL/dio.h"
#include "HAL/os.h"
#include<avr/interrupt.h>
#include"ECAL/PushButton.h"
#include"ECAL/SSD.h"
#include "APP/counter.h"
#include "APP/display.h"
int main()
{
	const DioConfig_t *config = Dio_ConfigGet();
	Dio_Init(config);
	const TMR0Config_t *tmr0Config =Tmr0_ConfigGet();
	OS_init(tmr0Config,5);
	const PB_data_t *buttonConfig =PB_ConfigGet();
	PB_init(buttonConfig);
	const SSD_Config_t *SSD_config=SSD_ConfigGet();
	SSD_init(SSD_config);
	CNT_init(5);
	Disp_init();
	while(1)
	{
		OS_schedule();
	}
}


