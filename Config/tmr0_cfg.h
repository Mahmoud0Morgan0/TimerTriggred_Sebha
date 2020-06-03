/*
 * tmr0_cfg.h
 *
 *  Created on: May 2, 2020
 *      Author: jenki
 */

#ifndef CONFIG_TMR0_CFG_H_
#define CONFIG_TMR0_CFG_H_



/**********************************************************************
* Includes
**********************************************************************/
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Typedefs
**********************************************************************/
/**
* Defines the possible MODEs Timer0 can operate.
*/
typedef enum
{
	NORMAL_MODE,		/**< Timer0 operates in Normal Mode */
	CTC_MODE,			/**< Timer0 operates in Clear Time on Compare Match Mode */
	FAST_PWM,			/**< Timer0 operates in Fast PWM Mode */
	CORRECT_PAHSE_PWM	/**< Timer0 operates in Correct phase PWM Mode */
}TMR0Modes_t;
/**
* Defines the compare output Modes for Timer0.
*/
typedef enum
{
	NORMAL,			/**< Normal port operation, OC0 disconnected. */
	TOGGLE,			/**< Toggle OC0 on compare match */
	CLEAR,			/**< Clear OC0 on compare match */
	SET				/**< Set OC0 on compare match */
}TMR0CMPModes_t;
/**
* Defines the Clock Selection for Timer0.
*/
typedef enum
{
	NO_PRESCALING,			/**< No prescaling */
	CLK_8,					/**< clk/8 (From prescaler)*/
	CLK_64,					/**< clk/64 (From prescaler) */
	CLK_256,				/**< clk/256 (From prescaler) */
	CLK_1024,				/**< clk/1024 (From prescaler) */
	EXT_FALLING,			/**< External clock source on T0 pin. Clock on falling edge.*/
	EXT_RISING				/**< External clock source on T0 pin. Clock on rising edge*/
}TMR0CLK_t;

/**
* Defines the Timer0 configuration table’s elements that are
used
* by TMR0_Init to configure the Timer0 peripheral.
*/
typedef struct
{
	TMR0Modes_t mode;
	TMR0CMPModes_t compareMode;
	TMR0CLK_t clock;
}TMR0Config_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/
const TMR0Config_t * const Tmr0_ConfigGet(void);

#endif /* CONFIG_TMR0_CFG_H_ */
