/*
 * PB_cfg.c
 *
 *  Created on: May 18, 2020
 *      Author: jenki
 */


/**********************************************************************
* Includes
**********************************************************************/
#include"PB_cfg.h"
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
PB_data_t buttonsConfig[numOfPushButton] =
{
		{0,		PORTA_ID,			_PIN1,			PB_RELEASED,{0,0}}
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/**********************************************************************
* Function : PB_ConfigGet()
*//**
* \b Description:
*
* This function is used to return the configuration table to PB_init function
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
* const PB_state_t *Config = PB_ConfigGet();
*
* PB_init(Config);
* @endcode
*
* @see PB_init

**********************************************************************/
const PB_data_t * const PB_ConfigGet(void)
{
/*
* The cast is performed to ensure that the address of the first element
* of configuration table is returned as a constant pointer and NOT a
* pointer that can be modified.
*/
	return (const PB_data_t*)buttonsConfig;
}
/*************** END OF FUNCTIONS ********************************/
