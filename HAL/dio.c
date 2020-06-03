/*
 * gpio.c
 *
 *  Created on: Apr 25, 2020
 *      Author: jenki
 */

/** @file dio.c
* @brief The implementation for the dio.
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "dio.h"

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
/**
* Defines a table of pointers to the peripheral input register on the
* microcontroller.
*/
uint8 dataInReg[4]={PINA,PINB,PINC,PIND};
/**
* Defines a table of pointers to the peripheral data direction register
on
* the microcontroller.
*/
uint8 dataDirReg[4]={DDRA,DDRB,DDRC,DDRD};
/**
* Defines a table of pointers to the peripheral latch register on the
* microcontroller
*/
uint8 dataOutReg[4]={PORTA,PORTB,PORTC,PORTD};


/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/*********************************************************************
* Function : Dio_Init()
*//**
* \b Description:
*
* This function is used to initialize the Dio based on the configuration
* table defined in dio_cfg module.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0) <br>
* PRE-CONDITION: NUMBER_OF_CHANNELS_PER_PORT > 0 <br>
* PRE-CONDITION: NUMBER_OF_PORTS > 0 <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: The DIO peripheral is set up with the configuration
* settings.
*
* @param Config is a pointer to the configuration table that
* contains the initialization for the peripheral.
*
* @return the gGPIOError_t State of this function
*
* \b Example:
* @code
* const DioConfig_t *DioConfig = Dio_ConfigGet();
*
* Dio_Init(DioConfig);
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
*
**********************************************************************/
gGPIOError_t Dio_Init(const DioConfig_t * Config)
{
	gGPIOError_t state = PASS;
	uint8 i =0;
	for(i=0;i<NUMBER_OF_CHANNELS_USED;i++)
	{
		if(Config[i].Port<DIO_MAX_PORT)
		{
			if(Config[i].Channel < DIO_MAX_PIN)
			{
				if((Config[i].Direction==DIO_INPUT)||(Config[i].Direction==DIO_OUTPUT))
				{
					HW_WRITE_BIT(dataDirReg[Config[i].Port],Config[i].Channel,Config[i].Direction);
				}else
					state=INCORRECT_DIRECTION;
				if((Config[i].Resistor==DIO_PULLUP_DISABLED)||(Config[i].Resistor==DIO_PULLUP_ENABLED))
				{
					HW_WRITE_BIT(dataOutReg[Config[i].Port],Config[i].Channel,Config[i].Resistor);
				}else
					state=INCORRECT_RESISTOR;
				if(((Config[i].Data==DIO_LOW)||(Config[i].Data==DIO_HIGH))&&(Config[i].Direction==DIO_OUTPUT))
				{
					HW_WRITE_BIT(dataOutReg[Config[i].Port],Config[i].Channel,Config[i].Data);
				}else
					state=INCORRECT_VALUE;
			}else
				state=INCORRECT_PIN_NUM;
		}else
			state=INCORRECT_PORT;
	}

	return state;
}
/**********************************************************************
* Function : Dio_ChannelRead()
*//**
* \b Description:
*
* This function is used to read the state of a dio channel (pin)
*
* PRE-CONDITION: The channel is configured as INPUT <br>
* PRE-CONDITION: The channel is configured as GPIO <br>
* PRE-CONDITION: The channel is within the maximum DioChannel_t
* definition
*
* POST-CONDITION: The channel state is returned.
*
* @param port is the DioPorts_t that represents a port
* @param Channel is the DioChannel_t that represents a pin
* @param state is pointer to the DioPinState_t that will be returned
*
* @return the gGPIOError_t State of this function
*
* \b Example:
* @code
* uint8_t pin = Dio_ReadChannel(PORT1_0);
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
*
**********************************************************************/
gGPIOError_t Dio_ChannelRead(DioPORTS_t port,DioChannel_t channel,DioPinState_t *data)
{
	uint8 temp ;
	gGPIOError_t state = PASS;
	if(port<DIO_MAX_PORT)
	{
		if(channel < DIO_MAX_PIN)
		{
			temp = HW_READ_BIT(dataInReg[port],channel);
			if(temp==0)
			{
				*data=DIO_LOW;
			}else if(temp==1)
				*data=DIO_HIGH;
		}else
			state = INCORRECT_PIN_NUM;
	}else
		state = INCORRECT_PORT;
	return state;
}
/**********************************************************************
* Function : Dio_ChannelRead()
*//**
* \b Description:
*
* This function is used to read the state of a dio port (pin)
*
* PRE-CONDITION: The port is configured as INPUT <br>
* PRE-CONDITION: The port is configured as GPIO <br>
* PRE-CONDITION: The port is within the maximum DioChannel_t
* definition
*
* POST-CONDITION: The channel state is returned.
*
* @param port is the DioPorts_t that represents a port
* @param state is pointer to the uint8 data that will be returned
*
* @return the gGPIOError_t State of this function
*
* \b Example:
* @code
* uint8_t pin = Dio_portChannel(porta_id);
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
*
**********************************************************************/
gGPIOError_t Dio_portRead(DioPORTS_t port,uint8 *data)
{
	uint8 temp ;
	gGPIOError_t state = PASS;
	if(port<DIO_MAX_PORT)
	{
		*data=HW_READ_REG_8BIT(dataInReg[port]);
	}else
		state = INCORRECT_PORT;
	return state;
}
/**********************************************************************
/**********************************************************************
* Function : Dio_ChannelWrite()
*//**
* \b Description:
*
* This function is used to write the state of a channel (pin) as either
* logic high or low through
*
*
* PRE-CONDITION: The channel is configured as OUTPUT <br>
* PRE-CONDITION: The channel is configured as GPIO <br>
* PRE-CONDITION: The channel is within the maximum DioChannel_t
* definition
*
* POST-CONDITION: The channel state will be state
*
* @param port is the DioPorts_t that represents a port
* @param Channel is the DioChannel_t that represents a pin
* @param state is State is HIGH or LOW
*
* @return the gGPIOError_t State of this function
*
* \b Example:
* @code
* Dio_WriteChannel(PORT1_0, LOW); // Set the PORT1_0 pin low
* Dio_WriteChannel(PORT1_0, HIGH); // Set the PORT1_0 pin high
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
*
**********************************************************************/
gGPIOError_t Dio_ChannelWrite(DioPORTS_t port,DioChannel_t channel,DioPinState_t data)
{
	gGPIOError_t state = PASS;
	if(port<DIO_MAX_PORT)
	{
		if(channel < DIO_MAX_PIN)
		{
			HW_WRITE_BIT(dataOutReg[port],channel,data);
		}else
			state = INCORRECT_PIN_NUM;
	}else
		state = INCORRECT_PORT;
	return state;
}
/**********************************************************************
* Function : Dio_portWrite()
*//**
* \b Description:
*
* This function is used to write the state of a port as either
* logic high or low through
*
*
* PRE-CONDITION: The port is configured as OUTPUT <br>
* PRE-CONDITION: The port is configured as GPIO <br>
* PRE-CONDITION: The port is within the maximum DioChannel_t
* definition
*
* POST-CONDITION: The channel state will be state
*
* @param port is the DioPorts_t that represents a port
* @param Channel is the DioChannel_t that represents a pin
* @param state is State is HIGH or LOW
*
* @return the gGPIOError_t State of this function
*
* \b Example:
* @code
* Dio_portChannel(PORT1_0, data);
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
*
**********************************************************************/
gGPIOError_t Dio_portWrite(DioPORTS_t port,uint8 data)
{
	gGPIOError_t state = PASS;
	if(port<DIO_MAX_PORT)
	{
		HW_WRITE_REG_8BIT(dataOutReg[port],data);
	}else
		state = INCORRECT_PORT;
	return state;
}
/**************************************************************************
* Function : Dio_ChannelToggle()
*//**
* \b Description:
* *
This function is used to toggle the current state of a channel (pin).
*
* PRE-CONDITION: The channel is configured as OUTPUT <br>
* PRE-CONDITION: The channel is configured as GPIO <br>
* PRE-CONDITION: The channel is within the maximum DioChannel_t definition
*
* POST-CONDITION:
*
* @param port is the DioPorts_t that represents a port
* @param Channel is the pin from the DioChannel_t that is
* to be modified.
*
* @return the gGPIOError_t State of this function
*
* \b Example:
* @code
* Dio_ChannelToggle(PORTA_1);
* @endcode
*
* @see Dio_Init
* @see Dio_ChannelRead
* @see Dio_ChannelWrite
* @see Dio_ChannelToggle
* @see Dio_RegisterWrite
* @see Dio_RegisterRead
* @see Dio_CallbackRegister
* **********************************************************************/
gGPIOError_t Dio_ChannelToggle(DioPORTS_t port,DioChannel_t channel)
{
	gGPIOError_t state = PASS;
	if(port<DIO_MAX_PORT)
	{
		if(channel < DIO_MAX_PIN)
		{
			HW_TOGGLE_BIT(dataOutReg[port],channel);
		}else
			state = INCORRECT_PIN_NUM;
	}else
		state = INCORRECT_PORT;
	return state;
}
