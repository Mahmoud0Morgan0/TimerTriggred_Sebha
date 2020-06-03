/*
 * interruptHandler.h
 *
 *  Created on: May 5, 2020
 *      Author: jenki
 */

#ifndef SYSTEM_INTERRUPTHANDLER_H_
#define SYSTEM_INTERRUPTHANDLER_H_

/**********************************************************************
* Includes
**********************************************************************/
#include"../RAL/hw_types.h"
#include"../RAL/HW_Interrupt.h"
#include	<avr/interrupt.h>
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define MAX_INTERRUPT_NUM 		26


#define TIMER0_COMP_VECTOR 		1

/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief Enumerate Possible modes of interrupt flag.*/
typedef enum
{
	FlAG_ClEARED,						/**< The flag is cleared = 0 */
	FLAG_SET							/**< The flag is set = 1 */
}INT_FlagStatus_t;
/** \brief Enumerate the types of errors in the interrupt handler.*/
typedef enum
{
	TIMER0_OVF,						/**< Timer0 OverFlow Interrupt */
	TIMER0_COMP						/**< Timer0 On Compare Interrupt */
}INT_InterruptType_t;
/** \brief Enumerate the types of errors in the interrupt handler.*/
typedef enum
{
	INT_PASS,						/**< There is no Error */
	INCORRECT_INTERRUPT_TYPE		/**< There is Error in Interrupt type*/
}INT_Error_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/
INT_Error_t INT_setGlobalInterrupt(void);
INT_Error_t INT_enableInterrupt(INT_InterruptType_t);
INT_Error_t INT_disableInterrupt(INT_InterruptType_t);
INT_Error_t INT_callbackRegister(uint8 InterruptID ,void (*ptr)(void));
INT_Error_t INT_checkFlag(INT_InterruptType_t,INT_FlagStatus_t *flag);
#endif /* SYSTEM_INTERRUPTHANDLER_H_ */
