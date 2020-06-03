/*
 * gpio.h
 *
 *  Created on: Apr 25, 2020
 *      Author: jenki
 */

#ifndef HAL_DIO_H_
#define HAL_DIO_H_


/**********************************************************************
* Includes
**********************************************************************/
#include "../RAL/HW_GPIO.h"
#include "../RAL/types.h"
#include "../RAL/hw_types.h"
#include "../Config/dio_cfg.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief Enumerate the types of errors in the gpio module.*/
typedef enum {
	PASS,						/**< There is no Error */
	INCORRECT_PORT,				/**< Error in POrt num */
	INCORRECT_PIN_NUM,			/**< Error in Pin num */
	INCORRECT_DIRECTION,		/**< Error in pin Direction */
	INCORRECT_VALUE,			/**< Error in the value */
	INCORRECT_RESISTOR			/**< Error in the Resisitor */
}gGPIOError_t;

/**********************************************************************
* Function Prototypes
**********************************************************************/
gGPIOError_t Dio_Init(const DioConfig_t * const config);
gGPIOError_t Dio_ChannelRead(DioPORTS_t port,DioChannel_t channel,DioPinState_t *state);
gGPIOError_t Dio_ChannelWrite(DioPORTS_t port,DioChannel_t channel,DioPinState_t state);
gGPIOError_t Dio_ChannelToggle(DioPORTS_t port,DioChannel_t channel);
gGPIOError_t Dio_portRead(DioPORTS_t port,uint8 *data);
gGPIOError_t Dio_portWrite(DioPORTS_t port,uint8 data);
#endif /* HAL_DIO_H_ */
