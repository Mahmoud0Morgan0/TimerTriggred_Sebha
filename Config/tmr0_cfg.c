/*
 * tmr0_cfg.c
 *
 *  Created on: May 3, 2020
 *      Author: jenki
 */

/** @file dio_cfg.c
* @brief This module contains the Timer 0 peripheral  configuration
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "tmr0_cfg.h" /* For this modules definitions */
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
/**********************************************************************
* Module Typedefs
**********************************************************************/
/*********************************************************************
* Module Variable Definitions
**********************************************************************/
/**
* The following struct contains the configuration data for Timer0.
* This configuration is read in by Tmr0_init.
*/

/*  					 operation mode			Compare mode					Clock	*/
/*																								*/
TMR0Config_t tmr0Config= {CTC_MODE,				NORMAL,					CLK_8};


/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/**********************************************************************
* Function : Tmr0_ConfigGet()
*//**
* \b Description:
*
* This function is used to send Timer 0 Configuration to the initialization function.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0)
*
* POST-CONDITION: A constant pointer to the first member of the
* configuration table will be returned.
*
* @return A pointer to the configuration table.
*
* \b Example Example:
* @code
* const TMR0Config_t *Config = Tmr0_GetConfig();
*
*
* @endcode
*
* @see Tmr0_Init

*
**********************************************************************/
const TMR0Config_t * const Tmr0_ConfigGet(void)
{
/*
* The cast is performed to ensure that the address of the first element
* of configuration table is returned as a constant pointer and NOT a
* pointer that can be modified.
*/
	return (const TMR0Config_t*)&tmr0Config;
}
/*************** END OF FUNCTIONS ********************************/
