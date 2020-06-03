/*
 * os.h
 *
 *  Created on: May 11, 2020
 *      Author: jenki
 */


#ifndef HAL_OS_H_
#define HAL_OS_H_
/**********************************************************************
* Includes
**********************************************************************/
#include"../Config/tmr0_cfg.h"
#include"timer0.h"
#include"../System/interruptHandler.h"
#include"../APP/counter.h"
#include"../APP/display.h"
#include"../ECAL/SSD.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define OS_TICK_MS 5
/**********************************************************************
* Typedefs
**********************************************************************/
/**********************************************************************
* Function Prototypes
**********************************************************************/
void OS_init(const TMR0Config_t * const tmr0config,uint16 period);
void OS_countPeriod(void);
void OS_schedule(void);

#endif /* HAL_OS_H_ */
