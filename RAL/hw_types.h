/*
 * hw_types.h
 *
 *  Created on: Apr 25, 2020
 *      Author: jenki
 */

#ifndef HW_TYPES_H_
#define HW_TYPES_H_



/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "../RAl/types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#ifndef INPUT
#define INPUT 0
#endif

#ifndef OUTPUT
#define OUTPUT 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif


/**
 *
 *  \brief  Macro to read a 8 bit register.
 *
 *  \param  address  8bit register address.
 *
 */
#define HW_READ_REG_8BIT(address) (*(volatile uint8*)(address))

/**
 *
 *  \brief  Macro to write a value to a 8 bit register.
 *
 *  \param  address  8bit register address.
 *  \param  value    value to write to the 8bit register.
 *
 */
#define HW_WRITE_REG_8BIT(address,value) ((*(volatile uint8*)(address)) = value )

/**
 *
 *  \brief  Macro to set a bit in a 8BIT register.
 *
 *  \param  addr  8BIT register address.
 *  \param  bit   the bit number to be set.
 *
 */
#define HW_SET_BIT(addr,bit) \
	(HW_READ_REG_8BIT(addr) |=(1<<bit))
/**
 *
 *  \brief  Macro to set a bit in a 8BIT register.
 *
 *  \param  addr  8BIT register address.
 *  \param  bit   the bit number to be set.
 *
 */
#define HW_TOGGLE_BIT(addr,bit) \
	(HW_READ_REG_8BIT(addr) ^=(1<<bit))
/**
 *
 *  \brief  Macro to reset a 8 bit register.
 *
 *  \param  addr  8BIT register address.
 *  \param  bit   the bit number to be reset.
 *
 */
#define HW_RESET_BIT(addr,bit) \
	(HW_READ_REG_8BIT(addr) &=~(1<<bit))

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/**
 *  \brief  This function is to write a bit within a 8bit register.
 *
 *  \param  reg  8bit register
 *  \param  pin  pin number for the pin to change its value.
 *  \param  val  the value to update the pin content.
 *
 */
static inline void HW_WRITE_BIT(uint8 reg, uint8 pin , uint8 val);


/**
 *  \brief  This function is to read a bit within a 8bit register.
 *
 *  \param  reg  8bit register
 *  \param  pin  pin number for the pin to read its value.
 *
 *  \retval bit-field value of the pin.(shifted to LSB ,return value will only be (0 or 1)
 *
 */
static inline uint8 HW_READ_BIT(uint8 reg,uint8 pin);


/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */


static inline void HW_WRITE_BIT(uint8 reg, uint8 pin , uint8 val){
	if(val == HIGH){
	HW_READ_REG_8BIT(reg)|= (1<<pin);
	}else if(val == LOW){
		HW_READ_REG_8BIT(reg)&= ~(1<<pin);
	}
}

static inline uint8 HW_READ_BIT(uint8 reg,uint8 pin){

	return ((HW_READ_REG_8BIT(reg)&(1<<pin))>>pin);
}


#endif /* HW_TYPES_H_ */
