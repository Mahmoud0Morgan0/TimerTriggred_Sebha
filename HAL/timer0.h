/*
 * timer0.h
 *
 *  Created on: May 3, 2020
 *      Author: jenki
 */

#ifndef HAL_TIMER0_H_
#define HAL_TIMER0_H_

/**********************************************************************
* Includes
**********************************************************************/
#include"../Config/tmr0_cfg.h"
#include"../RAL/hw_types.h"
#include"../RAL/HW_Timer0.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define CS00 	0
#define CS01 	1
#define CS02 	2
#define WGM01 	3
#define WGM00 	6
#define COM00 	4
#define COM01	5
/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief Enumerate the types of errors in the timer0 module.*/
typedef enum {
	TMR0PASS,					/**< There is no Error */
	INCORRECT_MODE,				/**< Error in operation mode */
	INCORRECT_COMPARE_MODE,		/**< Error in Compare Mode */
	INCORRECT_CLOCK,			/**< Error in Clock  */
	INCORRECT_TIMER_VALUE				/**< Error in value written to register */
}Timer0error_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/
Timer0error_t TMR0_Init(const TMR0Config_t * const config );
Timer0error_t loadOCR(uint8 value);

#endif /* HAL_TIMER0_H_ */
