/*
 * dio_cfg.h
 *
 *  Created on: Apr 28, 2020
 *      Author: jenki
 */

#ifndef HAL_DIO_CFG_H_
#define HAL_DIO_CFG_H_


/**********************************************************************
* Includes
**********************************************************************/
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**
 * Defines the number of pins on each processor port.
*/
#define NUMBER_OF_CHANNELS_PER_PORT 8U
/**
* Defines the number of ports on the processor.
*/
#define NUMBER_OF_PORTS 4U
/**
 * Defines the number of pins the user want to use "configrable".
*/
#define NUMBER_OF_CHANNELS_USED 10U
/**********************************************************************
* Typedefs
**********************************************************************/
/**
* Defines the possible states for a digital output pin.
*/
typedef enum
{
	DIO_LOW,	 		/** Defines digital state ground */
	DIO_HIGH, 			/** Defines digital state power */
	DIO_PIN_STATE_MAX 	/** Defines the maximum digital state */
}DioPinState_t;

/**
* Defines the possible states of the channel pull-ups
*/
typedef enum
{
	DIO_PULLUP_DISABLED, 		/*< Used to disable the internal pull-ups */
	DIO_PULLUP_ENABLED, 		/*< Used to enable the internal pull-ups */
	DIO_MAX_RESISTOR 			/*< Resistor states should be below this value */
}DioResistor_t;

typedef enum
{
	DIO_INPUT, 				/*< Pin works as input */
	DIO_OUTPUT, 			/*< Pin Works as output */
	DIO_MAX_DIRECTION 		/*< Pin Direction should be below this value */
}DioDirection_t;


/**
* Defines the possible DIO pin multiplexing values. The datasheet
* should be reviewed for proper muxing options.
*/
typedef enum
{
	/* TODO: Populate with possible mode options */
	GPIO,
	DIO_MAX_MODE
}DioMode_t;
/**
* Defines the possible Ports in the GPIO
*/
typedef enum
{
	PORTA_ID, 		/*< PORTA */
	PORTB_ID, 		/*< PORTB */
	PORTC_ID,		/*< PORTC */
	PORTD_ID,		/*< PORTD */
	DIO_MAX_PORT	/*< Max Num Of Ports */
}DioPORTS_t;

/**
* Defines the possible Pins in the GPIO
*/
typedef enum
{
	_PIN0, 			/*< PIN0 */
	_PIN1, 			/*< PIN1 */
	_PIN2,			/*< PIN2 */
	_PIN3,			/*< PIN3 */
	_PIN4, 			/*< PIN4 */
	_PIN5, 			/*< PIN5 */
	_PIN6,			/*< PIN6 */
	_PIN7,			/*< PIN8 */
	DIO_MAX_PIN		/*< Max Num Of Ports */
}DioChannel_t;

/**
* Defines the digital input/output configuration table’s elements that are
used
* by Dio_Init to configure the Dio peripheral.
*/
typedef struct
{
	DioPORTS_t Port;			/**< The I/O port */
	DioChannel_t Channel; 		/**< The I/O pin */
	DioResistor_t Resistor; 	/**< ENABLED or DISABLED */
	DioDirection_t Direction; 	/**< OUTPUT or INPUT */
	DioPinState_t Data; 		/**<HIGH or LOW */
	DioMode_t Function; 		/**< Mux Function - Dio_Peri_Select*/
}DioConfig_t;

/**********************************************************************
* Function Prototypes
**********************************************************************/
const DioConfig_t * const Dio_ConfigGet(void);

#endif /* HAL_DIO_CFG_H_ */
