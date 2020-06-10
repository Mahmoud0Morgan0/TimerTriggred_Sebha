/*
 * SSD_cfg.c
 *
 *  Created on: May 22, 2020
 *      Author: jenki
 */

/**********************************************************************
* Includes
**********************************************************************/
#include"SSD_cfg.h"
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
const SSD_Config_t SSDConfig[numOfSSD] =
{
		{0,PORTC_ID,SSD_0,PORTA_ID,_PIN2},
		{1,PORTC_ID,SSD_0,PORTA_ID,_PIN3},
		{2,PORTC_ID,SSD_0,PORTA_ID,_PIN4},
		{3,PORTC_ID,SSD_0,PORTA_ID,_PIN5}
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/**********************************************************************
* Function : SSD_ConfigGet()
*//**
* \b Description:
*
* This function is used to return the configuration table to SSD_init function
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
* const SSD_config_t *Config = SSD_ConfigGet();
*
* SSD_init(Config);
* @endcode
*
* @see PB_init

**********************************************************************/
const SSD_Config_t * const SSD_ConfigGet(void)
{
/*
* The cast is performed to ensure that the address of the first element
* of configuration table is returned as a constant pointer and NOT a
* pointer that can be modified.
*/
	return (const SSD_Config_t*)SSDConfig;
}
/*************** END OF FUNCTIONS ********************************/
