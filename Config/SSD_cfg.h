/*
 * SSD_cfg.h
 *
 *  Created on: May 22, 2020
 *      Author: jenki
 */

#ifndef CONFIG_SSD_CFG_H_
#define CONFIG_SSD_CFG_H_

/**********************************************************************
* Includes
**********************************************************************/
#include"../HAL/dio.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define numOfSSD 4

#define SSD_UPDATE_PERIOD_MS (5)
/**********************************************************************
* Typedefs
**********************************************************************/
/** \brief enumerates the possible symbols of SSD */
typedef enum
{
	SSD_0,						/**<Number Zero */
	SSD_1,						/**<Number One */
	SSD_2,						/**<Number Two */
	SSD_3,						/**<Number Three */
	SSD_4,						/**<Number Four */
	SSD_5,						/**<Number Five */
	SSD_6,						/**<Number Six */
	SSD_7,						/**<Number Seven */
	SSD_8,						/**<Number Eight */
	SSD_9,						/**<Number Nine */
	SSD_NULL
}SSD_symbols_t;
/** \brief enumerates the states of SSD */
typedef enum
{
	SSD_ON,									/**<the SSD is working*/
	SSD_OFF,								/**<the SSD is not Working */
	SSD_STATE_MAX,							/**<Max SSD states */
}SSD_State_t;
/** \brief structure contains data for each SSD.*/
typedef struct
{
	uint8 SSD_id;				/**<the ID number of SSD*/
	DioPORTS_t port;			/**<the port which SSD is connected to*/
	SSD_symbols_t symbol;		/**<symbol that will be displayed */
	DioPORTS_t controlport;		/**<the port that control the SSD */
	DioChannel_t controlPin;	/**<the pin that control the SSD */
	SSD_State_t state;			/**<THe state of the SSD */
}SSD_Config_t;

/**********************************************************************
* Function Prototypes
**********************************************************************/

#endif /* CONFIG_SSD_CFG_H_ */
