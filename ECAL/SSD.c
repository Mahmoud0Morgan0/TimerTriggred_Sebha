/*
 * SSD.c
 *
 *  Created on: May 20, 2020
 *      Author: jenki
 */

/**********************************************************************
* Includes
**********************************************************************/
#include "SSD.h"
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
SSD_Config_t SSDs[numOfSSD];

static uint8 SSD_data[SSD_NULL]=
{
		0b00111111,
		0b00000110,
	    0b01011011,
	    0b01001111,
	    0b01100110,
	    0b01101101,
	    0b01111101,
	    0b00000111,
	    0b01111111,
	    0b01101111,
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/*********************************************************************
* Function : SSD_init()
*//**
* \b Description:
*
* This function is used to initialize SSD module
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0) <br>
* PRE-CONDITION: NUMBER_OF_SDD > 0 <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: SSD is set up with the configuration
* settings.
*
* @param Config is a pointer to the configuration table that
* contains the initialization for SSD.
*
* @return the SSD_error_t State of this function
*
* \b Example:
* @code
*
* SSD_init(Config);
* @endcode
*
* @see SSD_update();
*
**********************************************************************/
SSD_error_t SSD_init(const SSD_Config_t *config)
{
	SSD_error_t errorState=SSD_PASS;
	uint8 i ;
	for(i=0;i<numOfSSD;i++)
	{
		if(config[i].SSD_id<numOfSSD)
		{
			SSDs[i].SSD_id=config[i].SSD_id;
		}else
			errorState=INCORRECT_SSD_ID;
		if(config[i].symbol<SSD_NULL)
		{
			SSDs[i].symbol=config[i].symbol;
		}else
			errorState=INCORRECT_SSD_SYMBOL;
		if(config[i].port<DIO_MAX_PORT)
		{
			SSDs[i].port=config[i].port;
		}else
			errorState=INCORRECT_PORT;
		if(config[i].controlPin<DIO_MAX_PIN)
		{
			SSDs[i].controlPin=config[i].controlPin;
		}else
			errorState=INCORRECT_PIN_NUM;
		if(config[i].controlPin<DIO_MAX_PIN)
		{
			SSDs[i].controlport=config[i].controlport;
		}else
			errorState=INCORRECT_PORT;
	}
	return errorState;
}
/*********************************************************************
* Function : SSD_update()
*//**
* \b Description:
*
* This function is the core logic for SSD module
*
* PRE-CONDITION: SSD is initialized  <br>
* PRE-CONDITION: NUMBER_OF_SSD > 0 <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:current SSD displaying its symbol
*
* \b Example:
* @code
*
* SSD_update();
* @endcode
*
* @see SSD_init();
* @see SSD_getState();
* @see SSD_setState();
* @see SSD_setSymbol();
**********************************************************************/
void SSD_update(void)
{
	uint8 i;
	static uint8 SSD_update_counter =0;
	SSD_update_counter+=OS_TICK_MS;
	if(SSD_update_counter<SSD_UPDATE_PERIOD_MS)
	{
		return;
	}
	SSD_update_counter=0;

	static uint8 currentSSD=0;
	/*for(i=0;i<numOfSSD;i++)
	{
		SSD_setState(i,SSD_OFF);
	}*/
	SSD_setState(0,SSD_OFF);
	SSD_setState(1,SSD_OFF);
	SSD_setState(currentSSD,SSD_ON);
	currentSSD++;
	if(currentSSD==numOfSSD)
	{
		currentSSD=0;
	}
}
/*********************************************************************
* Function : SSD_setState()
*//**
* \b Description:
*
* This function is used to set state of SSD On or OFF
*
* PRE-CONDITION: SSD is initialized  <br>
* PRE-CONDITION: NUMBER_OF_SSD > 0 <br>
* PRE-CONDITION: NUMBER_OF_SSD < numOfSSD <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:the state of SSD is set
*
* @param SSD_id is the number of the SSD user want set its state
*
* @param state the state user wants to be set
*
* @return the SSD_error_t State of this function
*
* \b Example:
* @code
*
* SSD_setState(1,SSD_ON);
* @endcode
*
* @see SSD_init();
* @see SSD_getState();
* @see SSD_update();
* @see SSD_setSymbol();
**********************************************************************/
SSD_error_t SSD_setState(uint8 SSD_id,SSD_State_t state)
{
	SSD_error_t errorState=SSD_PASS;
	if(SSD_id<numOfSSD)
	{
		if(state<SSD_STATE_MAX)
		{
			Dio_ChannelWrite(SSDs[SSD_id].controlport,SSDs[SSD_id].controlPin,state);
			SSDs[SSD_id].state=state;
		}else
			errorState=INCORRECT_SSD_STATE;
	}else
		errorState=INCORRECT_SSD_ID;
	return errorState;
}
/*********************************************************************
* Function : SSD_getState()
*//**
* \b Description:
*
* This function is used to get state of SSD On or OFF
*
* PRE-CONDITION: SSD is initialized  <br>
* PRE-CONDITION: NUMBER_OF_SSD > 0 <br>
* PRE-CONDITION: NUMBER_OF_SSD < numOfSSD <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:the state of SSD is is returned
*
* @param SSD_id is the number of the SSD user want set its state
*
* @param state the state that will be returned from function
*
* @return the SSD_error_t State of this function
*
* \b Example:
* @code
*
* SSD_getState(1,&state);
* @endcode
*
* @see SSD_init();
* @see SSD_setState();
* @see SSD_update();
* @see SSD_setSymbol();
**********************************************************************/
SSD_error_t SSD_getState(uint8 SSD_id,SSD_State_t *state)
{
	DioPinState_t temp;
	SSD_error_t errorState=SSD_PASS;
	if(SSD_id<numOfSSD)
	{
		Dio_ChannelRead(SSDs[SSD_id].controlport,SSDs[SSD_id].controlPin,&temp);
		if(temp==DIO_LOW)
		{
			*state=SSD_OFF;
		}else if(temp==DIO_HIGH)
		{
			*state=SSD_ON;
		}
	}else
		errorState=INCORRECT_SSD_ID;
	return errorState;
}
/*********************************************************************
* Function : SSD_setSymbol()
*//**
* \b Description:
*
* This function is used to set Symbol of SSD
*
* PRE-CONDITION: SSD is initialized  <br>
* PRE-CONDITION: NUMBER_OF_SSD > 0 <br>
* PRE-CONDITION: NUMBER_OF_SSD < numOfSSD <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:the Symbol of SSD is set
*
* @param SSD_id is the number of the SSD user want set its state
*
* @param symbol the symbol user wants to be set
*
* @return the SSD_error_t State of this function
*
* \b Example:
* @code
*
* SSD_setSymbol(1,SSD_5);
* @endcode
*
* @see SSD_init();
* @see SSD_getState();
* @see SSD_update();
* @see SSD_setState();
**********************************************************************/
SSD_error_t SSD_setSymbol(uint8 SSD_id,SSD_symbols_t symbol)
{
	SSD_error_t errorState=SSD_PASS;
	if(SSD_id<numOfSSD)
	{
		if(symbol<SSD_NULL)
		{
			Dio_portWrite(SSDs[SSD_id].port,SSD_data[symbol]);
			SSDs[SSD_id].symbol=symbol;
		}else
			errorState=INCORRECT_SSD_SYMBOL;
	}else
		errorState=INCORRECT_SSD_ID;
	return errorState;
}
/*********************************************************************
* Function : SSD_getSymbol()
*//**
* \b Description:
*
* This function is used to get symbol of SSD
*
* PRE-CONDITION: SSD is initialized  <br>
* PRE-CONDITION: NUMBER_OF_SSD > 0 <br>
* PRE-CONDITION: NUMBER_OF_SSD < numOfSSD <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION:the state of SSD is is returned
*
* @param SSD_id is the number of the SSD user want set its symbol
*
* @param state the symbol that will be returned from function
*
* @return the SSD_error_t State of this function
*
* \b Example:
* @code
*
* SSD_getSymbol(1,&symbol);
* @endcode
*
* @see SSD_init();
* @see SSD_setState();
* @see SSD_update();
* @see SSD_setSymbol();
**********************************************************************/
SSD_error_t SSD_getSymbol(uint8 SSD_id,SSD_symbols_t *symbol)
{
	uint8 data,i;
	SSD_error_t errorState=SSD_PASS;
	if(SSD_id<numOfSSD)
	{
		Dio_portRead(SSDs[SSD_id].port,&data);
		for(i=0;i<SSD_NULL;i++)
		{
			if(data==SSD_data[i])
			{
				*symbol=i;
				break;
			}
		}
	}else
		errorState=INCORRECT_SSD_ID;
	return errorState;
}
