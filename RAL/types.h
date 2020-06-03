/*
 * types.h
 *
 *  Created on: Apr 25, 2020
 *      Author: jenki
 */

#ifndef TYPES_H_
#define TYPES_H_

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Defines TRUE status value */
#ifndef TRUE
#define TRUE     (1U)
#endif

/** \brief Defines FALSE status value */
#ifndef FALSE
#define FALSE    (0U)
#endif

/** \brief Defines NULL pointer value */
#ifndef NULL
#define NULL ((void*) 0U)
#endif





/** \brief create a 32 bit unsigned type */
typedef unsigned int uint32;

/** \brief create a 8 bit unsigned type */
typedef unsigned char uint8;

/** \brief create a 16 bit unsigned type */
typedef unsigned short uint16;


#endif /* TYPES_H_ */
