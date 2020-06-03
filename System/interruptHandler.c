/*
 * interruptHandler.c
 *
 *  Created on: May 5, 2020
 *      Author: jenki
 */


/**********************************************************************
* Includes
**********************************************************************/
#include"interruptHandler.h"
#include"../HAL/dio.h"
#include"../HAL/os.h"
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
void (* ISR_FUNCTIONS [MAX_INTERRUPT_NUM])(void);

/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/*********************************************************************
* Function : INT_setGlobalInterrupt()
*//**
* \b Description:
*
* This function is used to enable global interrupts
*
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: Global Interrupt is Enabled
*
* @return the INT_Error_t State of this function
*
* \b Example:
* @code
* 	INT_setGlobalInterrupt();
* @endcode
*
* @see INT_enableInterrupt
**********************************************************************/
INT_Error_t INT_setGlobalInterrupt(void)
{
	INT_Error_t state = INT_PASS;
	HW_WRITE_BIT(_SREG,7,1);
	return state;
}
/*********************************************************************
* Function : INT_enableInterrupt()
*//**
* \b Description:
*
* This function is used to enable Interrupt for Peripheral
*
* PRE-CONDITION: The MCU clocks must be configured and enabled.
* PRE-CONDITION: Global Interrupt is enabled.
*
* @param interrupt is interrupt source
*
* POST-CONDITION: Peripheral Interrupt is enabled
*
* @return the INT_Error_t State of this function
*
* \b Example:
* @code
* 	INT_enableInterrupt(TIMER0_OVF);
* @endcode
*
* @see INT_setGlobalInterrupt
* @see INT_disableInterrupt
* @see INT_callbackRegister
**********************************************************************/
INT_Error_t INT_enableInterrupt(INT_InterruptType_t interrupt)
{
	INT_Error_t state = INT_PASS;
	if(interrupt==TIMER0_OVF)
	{
		HW_SET_BIT(_TIMSK,0);
		
	}else if(interrupt==TIMER0_COMP)
	{
		HW_SET_BIT(_TIMSK,1);
		
	}else
		state=INCORRECT_INTERRUPT_TYPE;
	return state;
}
/*********************************************************************
* Function : INT_disableInterrupt()
*//**
* \b Description:
*
* This function is used to disable Interrupt for Peripheral
*
* PRE-CONDITION: The MCU clocks must be configured and enabled.
* PRE-CONDITION: Global Interrupt is enabled.
* PRE-CONDITION:  Corresponding Peripheral interrupt is enabled.
*
* POST-CONDITION: Peripheral Interrupt is disabled
*
* @param interrupt is interrupt source
*
* @return the INT_Error_t State of this function
*
* \b Example:
* @code
* 	INT_disableInterrupt(TIMER0_OVF);
* @endcode
*
* @see INT_setGlobalInterrupt
* @see INT_enableInterrupt
* @see INT_callbackRegister
**********************************************************************/
INT_Error_t INT_disableInterrupt(INT_InterruptType_t interrupt)
{
	INT_Error_t state = INT_PASS;
	if(interrupt==TIMER0_OVF)
	{
		HW_RESET_BIT(_TIMSK,0);
	}else if(interrupt==TIMER0_COMP)
	{
		HW_RESET_BIT(_TIMSK,1);
	}else
		state=INCORRECT_INTERRUPT_TYPE;
	return state;
}
/*********************************************************************
* Function : INT_callbackRegister()
*//**
* \b Description:
*
* This function is used register a function to be an ISR
*
* PRE-CONDITION: The MCU clocks must be configured and enabled.
* PRE-CONDITION: Global Interrupt is enabled.
* PRE-CONDITION: Corresponding Peripheral interrupt is enabled.
*
* POST-CONDITION: The function passed to this function is registered as ISR
*
* @param interrupt is interrupt id
* @param ptr is the function is set to be ISR
*
* @return the INT_Error_t State of this function
*
* \b Example:
* @code
* 	INT_callbackRegister(TIMER0_OVF_VECT,fun);
* @endcode
*
* @see INT_setGlobalInterrupt
* @see INT_enableInterrupt
* @see INT_callbackRegister
**********************************************************************/
INT_Error_t INT_callbackRegister(uint8 interrupt,void (*ptr)(void))
{
	INT_Error_t state = INT_PASS;
	if(interrupt<MAX_INTERRUPT_NUM)
	{
		ISR_FUNCTIONS[interrupt]=ptr;
	}else
		state=INCORRECT_INTERRUPT_TYPE;
	return state;
}
/*********************************************************************
* Function : INT_checkFlag()
*//**
* \b Description:
*
* This function is used to get Flag state
*
* PRE-CONDITION: The MCU clocks must be configured and enabled.
* PRE-CONDITION: Global Interrupt is enabled.
* PRE-CONDITION: Corresponding Peripheral interrupt is enabled.
*
* POST-CONDITION: flag is know in which state is it
*
* @param interrupt is interrupt source
* @param[out] flag is state of the flag
* @return the INT_Error_t State of this function
*
* \b Example:
* @code
* 	INT_FlagStatus_t flag;
* 	INT_checkFlag(TIMER0_OVF,&flag);
* @endcode
*
* @see INT_setGlobalInterrupt
* @see INT_enableInterrupt
* @see INT_callbackRegister
**********************************************************************/
INT_Error_t INT_checkFlag(INT_InterruptType_t interrupt,INT_FlagStatus_t *flag)
{
	INT_Error_t state = INT_PASS;
	if(interrupt==TIMER0_OVF)
	{
		if(HW_READ_BIT(_TIFR,0)==0)
		{
			*flag=FlAG_ClEARED;
		}else
			*flag=FLAG_SET;
	}else if(interrupt==TIMER0_COMP)
	{
		if(HW_READ_BIT(_TIFR,0)==0)
		{
			*flag=FlAG_ClEARED;
		}else
			*flag=FLAG_SET;
	}else
		state=INCORRECT_INTERRUPT_TYPE;
	return state;
}



#ifdef TIMER0_OVF_VECT
ISR(TIMER0_OVF_vect) {
	ISR_FUNCTIONS[TIMER0_OVF_VECT]();
}
#endif

#ifdef TIMER0_COMP_VECTOR
ISR(_VECTOR(10)) {
	
	OS_countPeriod();
	//(*ISR_FUNCTIONS[TIMER0_COMP_VECTOR])();
}
#endif

