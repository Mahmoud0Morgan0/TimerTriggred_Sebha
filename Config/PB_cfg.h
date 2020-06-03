/*
 * PB_cfg.h
 *
 *  Created on: May 17, 2020
 *      Author: jenki
 */

#ifndef CONFIG_PB_CFG_H_
#define CONFIG_PB_CFG_H_

/**********************************************************************
* Includes
**********************************************************************/
#include"../RAL/types.h"
#include"dio_cfg.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define numOfPushButton 	2
#define numOfSamples		2

#define PB_RELEASED_LEVEL  	1
#define PB_PRESSED_LEVEL	0

#define PB_RESET			0
#define PB_COUNTER			1

#define PB_UPDATE_PERIOD_MS  20
/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief Enumerate the STATES OF PUSH BUTTON.*/
typedef enum
{
	PB_RELEASED,			/**< THE PUSH BUTTON IN RELAEASED STATE */
	PB_PREPRESSED,			/**< THE PUSH BUTTON IN PREPRESSED STATE */
	PB_PRESSED,				/**< THE PUSH BUTTON IN PRESSED STATE */
	PB_PRERELEASED			/**< THE PUSH BUTTON IN PRERELAEASED STATE */
}PB_state_t;
/** \brief structure defines the data of BushButton .*/
typedef struct
{
	uint8 buttonID;
	DioPORTS_t port;							/**< the port which pushbutton is connected to  */
	DioChannel_t channel;						/**< the channel which pushbutton is connected to  */
	PB_state_t state;							/**< the state of push button  */
	DioPinState_t samples[numOfSamples];		/**< Actual pin value at a time  */
}PB_data_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/
const PB_data_t * const PB_ConfigGet(void);

#endif /* CONFIG_PB_CFG_H_ */
