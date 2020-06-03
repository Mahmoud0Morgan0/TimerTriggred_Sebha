/*
 * PushButton.c
 *
 *  Created on: May 17, 2020
 *      Author: jenki
 */

/**********************************************************************
* Includes
**********************************************************************/
#include"PushButton.h"
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
PB_data_t buttons[numOfPushButton];
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/*********************************************************************
* Function : PB_init()
*//**
* \b Description:
*
* This function is used to initialize PushButtons module
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0) <br>
* PRE-CONDITION: NUMBER_OF_Buttons > 0 <br>
* PRE-CONDITION: NUMBER_OF_Samples > 0 <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: PB is set up with the configuration
* settings.
*
* @param Config is a pointer to the configuration table that
* contains the initialization for the peripheral.
*
* @return the PB_error_t State of this function
*
* \b Example:
* @code
*
* PB_init(Config);
* @endcode
*
* @see PB_update();
*
**********************************************************************/
PB_error_t PB_init(const PB_data_t * data)
{
	uint8 i;
	PB_error_t errorState=PB_PASS;
	for(i=0;i<numOfPushButton;i++)
	{
		buttons[i].channel=data[i].channel;
		buttons[i].buttonID=data[i].buttonID;
		buttons[i].port=data[i].port;
		buttons[i].state=data[i].state;
		if(data[i].state==PB_RELEASED)
		{
			buttons[i].samples[0]=PB_RELEASED_LEVEL;
			buttons[i].samples[1]=PB_RELEASED_LEVEL;
		}else if(data[i].state==PB_PRESSED)
		{
			buttons[i].samples[0]=PB_PRESSED_LEVEL;
			buttons[i].samples[1]=PB_PRESSED_LEVEL;
		}else
			errorState=INCORRECT_INIT_STATE;
	}
	return errorState;
}
/*********************************************************************
* Function : PB_update()
*//**
* \b Description:
*
* This function is the core logic for pushButton module it calculates the cureent state for the button
*
* PRE-CONDITION: push button is initialized  <br>
* PRE-CONDITION: NUMBER_OF_Buttons > 0 <br>
* PRE-CONDITION: NUMBER_OF_Buttons < max number of buttons <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:the live state of button is calculated
*
* \b Example:
* @code
*
* PB_update();
* @endcode
*
* @see PB_init();
* @see PB_getState();
*
**********************************************************************/
void PB_update(void)
{
	uint8 i ;
	static uint8 PB_update_counter =0;
	PB_update_counter+=OS_TICK_MS;
	if(PB_update_counter<PB_UPDATE_PERIOD_MS)
	{
		return;
	}
	PB_update_counter=0;
	for(i=0;i<numOfPushButton;i++)
	{
		buttons[i].samples[0]=buttons[i].samples[1];
		Dio_ChannelRead(buttons[i].port,buttons[i].channel,&buttons[i].samples[1]);
		switch(buttons[i].state)
		{
		case PB_RELEASED:
			if((buttons[i].samples[0]==PB_PRESSED_LEVEL) &&
			   (buttons[i].samples[1]==PB_PRESSED_LEVEL))
			{
				buttons[i].state=PB_PREPRESSED;
			}
			break;
		case PB_PREPRESSED:
			if(buttons[i].samples[1]==PB_PRESSED_LEVEL)
			{
				buttons[i].state=PB_PRESSED;
			}
			break;
		case PB_PRESSED:
			if((buttons[i].samples[0]==PB_RELEASED_LEVEL) &&
			   (buttons[i].samples[1]==PB_RELEASED_LEVEL))
			{
				buttons[i].state=PB_PRERELEASED;
			}
			break;
		case PB_PRERELEASED:
			if(buttons[i].samples[1]==PB_RELEASED_LEVEL)
			{
				buttons[i].state=PB_RELEASED;
			}
			break;
		default:
			break;
		}
	}
}
/*********************************************************************
* Function : PB_getButtonState()
*//**
* \b Description:
*
* This function is used to get state of PB
*
* PRE-CONDITION: push button is initialized  <br>
* PRE-CONDITION: NUMBER_OF_Buttons > 0 <br>
* PRE-CONDITION: NUMBER_OF_Buttons < max number of buttons <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:the state of SSD is is returned
*
* @param buttonId is the id of the SSD user want set its state
*
* @param state the state that will be returned from function
*
* @return the PB_error_t State of this function
*
* \b Example:
* @code
*
* PB_getButtonState(1,&state);
* @endcode
*
* @see PB_init();
* @see PB_update();
**********************************************************************/
PB_error_t PB_getButtonState(uint8 buttonId,PB_state_t *state)
{
	PB_error_t errorState = PB_PASS;
	if(buttonId<numOfPushButton)
	{
		*state=buttons[buttonId].state;
	}else
		errorState=INCORRECT_BUTTON_ID;
	return errorState;
}
