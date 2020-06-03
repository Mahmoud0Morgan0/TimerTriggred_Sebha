/*
 * PushButton.h
 *
 *  Created on: May 17, 2020
 *      Author: jenki
 */

#ifndef ECAL_PUSHBUTTON_H_
#define ECAL_PUSHBUTTON_H_

/**********************************************************************
* Includes
**********************************************************************/
#include "../Config/PB_cfg.h"
#include "../HAL/dio.h"
#include "../HAL/os.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief Enumerate the types of errors in the Push Button module.*/
typedef enum
{
	PB_PASS,					/**< There is no Error */
	INCORRECT_INIT_STATE,		/**< Error IN initial state */
	INCORRECT_BUTTON_ID			/**< Error IN button number */
}PB_error_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/
PB_error_t PB_init(const PB_data_t * data);
void PB_update(void);
PB_error_t PB_getButtonState(uint8 buttonId,PB_state_t *state);
#endif /* ECAL_PUSHBUTTON_H_ */
