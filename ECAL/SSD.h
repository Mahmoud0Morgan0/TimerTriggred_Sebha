/*
 * SSD.h
 *
 *  Created on: May 20, 2020
 *      Author: jenki
 */

#ifndef ECAL_SSD_H_
#define ECAL_SSD_H_

/**********************************************************************
* Includes
**********************************************************************/
#include "../Config/SSD_cfg.h"
#include"../HAL/os.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief Enumerate the types of errors in the SSD module.*/
typedef enum
{
	SSD_PASS,					/**< There is no Error */
	INCORRECT_SSD_ID,			/**< Error IN SSD ID */
	INCORRECT_SSD_SYMBOL,		/**< Error IN SSD Symbol */
	INCORRECT_SSD_STATE			/**< Error IN SSD State */
}SSD_error_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/
SSD_error_t SSD_init(const SSD_Config_t const * config);
void SSD_update(void);
SSD_error_t SSD_setState(uint8 SSD_id,SSD_State_t state);
SSD_error_t SSD_getState(uint8 SSD_id,SSD_State_t *state);
SSD_error_t SSD_setSymbol(uint8 SSD_id,SSD_symbols_t symbol);
SSD_error_t SSD_getSymbol(uint8 SSD_id,SSD_symbols_t *symbol);
SSD_error_t SSD_out(uint8 SSD_id,SSD_symbols_t symbol);
#endif /* ECAL_SSD_H_ */
