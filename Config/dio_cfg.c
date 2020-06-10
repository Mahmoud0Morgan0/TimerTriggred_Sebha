/*
 * dio_cfg.c
 *
 *  Created on: Apr 28, 2020
 *      Author: jenki
 */

/** @file dio_cfg.c
* @brief This module contains the implementation for the digital
* input/output peripheral configuration
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "dio_cfg.h" /* For this modules definitions */
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
* The following array contains the configuration data for each
* digital input/output peripheral channel (pin). Each row represents a *
single pin. Each column is representing a member of the DioConfig_t
* structure. This table is read in by Dio_Init, where each channel is then
* set up based on this table.
*/


const DioConfig_t DioConfig[NUMBER_OF_CHANNELS_USED] =
{
/*  Port		PIN				Resistor			   		Direction		PINState		Mode*/
/*																								*/

{ PORTA_ID,		 _PIN0, 		DIO_PULLUP_ENABLED, 		DIO_INPUT, 			DIO_HIGH ,		GPIO },
{ PORTA_ID,		 _PIN1, 		DIO_PULLUP_ENABLED, 		DIO_INPUT, 			DIO_HIGH ,		GPIO },
{ PORTA_ID,		 _PIN2, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_HIGH ,		GPIO },
{ PORTA_ID,		 _PIN3, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_HIGH ,		GPIO },
{ PORTA_ID,		 _PIN4, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_HIGH ,		GPIO },
{ PORTA_ID,		 _PIN5, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_HIGH ,		GPIO },
{ PORTC_ID,		 _PIN0, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO },
{ PORTC_ID,		 _PIN1, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO },
{ PORTC_ID,		 _PIN2, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO },
{ PORTC_ID,		 _PIN3, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO },
{ PORTC_ID,		 _PIN4, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO },
{ PORTC_ID,		 _PIN5, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO },
{ PORTC_ID,		 _PIN6, 		DIO_PULLUP_DISABLED, 		DIO_OUTPUT, 		DIO_LOW ,		GPIO }
};


/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/**********************************************************************
* Function : Dio_ConfigGet()
*//**
* \b Description:
*
* This function is used to initialize the Dio based on the configuration
* table defined in dio_cfg module.
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
* const Dio_ConfigType *DioConfig = Dio_GetConfig();
*
* Dio_Init(DioConfig);
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
* @see Dio_RegisterWrite
* @see Dio_RegisterRead
*
**********************************************************************/
const DioConfig_t * const Dio_ConfigGet(void)
{
/*
* The cast is performed to ensure that the address of the first element
* of configuration table is returned as a constant pointer and NOT a
* pointer that can be modified.
*/
	return (const DioConfig_t*)DioConfig;
}
/*************** END OF FUNCTIONS ********************************/
