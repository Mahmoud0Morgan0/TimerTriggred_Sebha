/*
 * timer0.c
 *
 *  Created on: May 3, 2020
 *      Author: jenki
 */

/** @file dio.c
* @brief The implementation for the timer0.
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "timer0.h"
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
/*********************************************************************
* Function : TMR0_Init()
*//**
* \b Description:
*
* This function is used to initialize the Timer0 based on the configuration
* table defined in tmr0_cfg module.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0) <br>
* PRE-CONDITION: OPERATION mode must be configured > 0 <br>
* PRE-CONDITION: Compare Mode must be configured > 0 <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: The Timer0 peripheral is set up with the configuration
* settings.
*
* @param Config is a pointer to the configuration table that
* contains the initialization for the peripheral.
*
* @return the Timer0error_t State of this function
*
* \b Example:
* @code
* const TMR0Config_t *tmrConfig = TMR0_ConfigGet();
*
* TMR0_Init(tmrConfig);
* @endcode
*
* @see TMR0_Init

*
**********************************************************************/
Timer0error_t TMR0_Init(const TMR0Config_t * const config )
{
	Timer0error_t state = TMR0PASS;
	if(config->mode==NORMAL_MODE)
	{
		HW_WRITE_BIT(TCCR0,WGM00,0);
		HW_WRITE_BIT(TCCR0,WGM01,0);
	}else if(config->mode==CTC_MODE)
	{
		HW_WRITE_BIT(TCCR0,WGM00,0);
		HW_WRITE_BIT(TCCR0,WGM01,1);
	}else if(config->mode==FAST_PWM)
	{
		HW_WRITE_BIT(TCCR0,WGM00,1);
		HW_WRITE_BIT(TCCR0,WGM01,0);
	}else if(config->mode==CORRECT_PAHSE_PWM)
	{
		HW_WRITE_BIT(TCCR0,WGM00,1);
		HW_WRITE_BIT(TCCR0,WGM01,1);
	}else
		state=INCORRECT_MODE;
	if(config->compareMode==NORMAL)
	{
		HW_WRITE_BIT(TCCR0,COM00,0);
		HW_WRITE_BIT(TCCR0,COM01,0);
	}else if(config->compareMode==TOGGLE)
	{
		HW_WRITE_BIT(TCCR0,COM00,1);
		HW_WRITE_BIT(TCCR0,COM01,0);
	}else if(config->compareMode==CLEAR)
	{
		HW_WRITE_BIT(TCCR0,COM00,0);
		HW_WRITE_BIT(TCCR0,COM01,1);
	}else if(config->compareMode==SET)
	{
		HW_WRITE_BIT(TCCR0,COM00,1);
		HW_WRITE_BIT(TCCR0,COM01,1);
	}else
		state=INCORRECT_COMPARE_MODE;
	if(config->clock==NO_PRESCALING)
	{
		HW_WRITE_BIT(TCCR0,CS00,1);
		HW_WRITE_BIT(TCCR0,CS01,0);
		HW_WRITE_BIT(TCCR0,CS02,0);
	}else if(config->clock==CLK_8)
	{
		HW_WRITE_BIT(TCCR0,CS00,0);
		HW_WRITE_BIT(TCCR0,CS01,1);
		HW_WRITE_BIT(TCCR0,CS02,0);
	}else if(config->clock==CLK_64)
	{
		HW_WRITE_BIT(TCCR0,CS00,1);
		HW_WRITE_BIT(TCCR0,CS01,1);
		HW_WRITE_BIT(TCCR0,CS02,0);
	}else if(config->clock==CLK_256)
	{
		HW_WRITE_BIT(TCCR0,CS00,0);
		HW_WRITE_BIT(TCCR0,CS01,0);
		HW_WRITE_BIT(TCCR0,CS02,1);
	}else if(config->clock==CLK_1024)
	{
		HW_WRITE_BIT(TCCR0,CS00,1);
		HW_WRITE_BIT(TCCR0,CS01,0);
		HW_WRITE_BIT(TCCR0,CS02,1);
	}else if(config->clock==EXT_FALLING)
	{
		HW_WRITE_BIT(TCCR0,CS00,0);
		HW_WRITE_BIT(TCCR0,CS01,1);
		HW_WRITE_BIT(TCCR0,CS02,1);
	}else if(config->clock==EXT_RISING)
	{
		HW_WRITE_BIT(TCCR0,CS00,1);
		HW_WRITE_BIT(TCCR0,CS01,1);
		HW_WRITE_BIT(TCCR0,CS02,1);
	}else
		state=INCORRECT_CLOCK;

	return state;
}

void TMR0_update (void)
{

}
/*********************************************************************
* Function : loadOCR()
*//**
* \b Description:
*
* This function is used to Load OCR register with specified value.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0) <br>
* PRE-CONDITION: OPERATION mode must be configured > 0 <br>
* PRE-CONDITION: Compare Mode must be configured > 0 <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: the OCR register has the value that will be compared to the TCNT
*
* @param value the value to be set in OCR register.
*
*
* @return the Timer0error_t State of this function
*
* \b Example:
* @code
* loadOCR(200);
*
*
* @endcode
*
* @see TMR0_Init
* @see TMR0_update
*
**********************************************************************/
Timer0error_t loadOCR(uint8 value)
{
	Timer0error_t state =TMR0PASS;
	if (value<255)
	{
		HW_WRITE_REG_8BIT(OCR0,value);
	}else
		state=INCORRECT_TIMER_VALUE;
	return state;
}
