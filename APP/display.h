/*
 * display.h
 *
 *  Created on: May 29, 2020
 *      Author: jenki
 */

#ifndef APP_DISPLAY_H_
#define APP_DISPLAY_H_

/**********************************************************************
* Includes
**********************************************************************/
#include "counter.h"
#include "../ECAL/SSD.h"
#include"../HAL/os.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define SSD_units 	     3
#define SSD_tens  		 2
#define SSD_hundreds 	 1
#define SSD_thousands  	 0


#define DISP_UPDATE_PERIOD_MS 20
/**********************************************************************
* Typedefs
**********************************************************************/
/**********************************************************************
* Function Prototypes
**********************************************************************/
void DISP_update(void);
void Disp_init(void);

#endif /* APP_DISPLAY_H_ */
