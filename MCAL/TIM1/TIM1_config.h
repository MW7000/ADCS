/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V03                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: TIMER1                             */
/********************************************/

#ifndef			TIM1_CONFIG_H
#define			TIM1_CONFIG_H

#define  CPU_FREQ 	16000000

/* here you can enter the TIM1 clock prescaler:
 * 
 *  TIM1_INT_CLK_BY_1
 *  TIM1_INT_CLK_BY_8
 *  TIM1_INT_CLK_BY_64
 *  TIM1_INT_CLK_BY_256
 *  TIM1_INT_CLK_BY_1024
 *  TIM1_EXT_CLK_ON_FALLING
 *  TIM1_EXT_CLK_ON_RISING
 */

#define 		TIM1_CLK_CONFIG				TIM1_INT_CLK_BY_8

#if TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_1

#define TIM1_CLK	 	CPU_FREQ/TIM1_ICU_IO_CLK_PRESCALER_BY_1

#elif TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_8

#define TIM1_CLK		CPU_FREQ/TIM1_ICU_IO_CLK_PRESCALER_BY_8

#elif TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_64

#define TIM1_CLK		CPU_FREQ/TIM1_ICU_IO_CLK_PRESCALER_BY_64

#elif TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_256

#define TIM1_CLK		CPU_FREQ/TIM1_ICU_IO_CLK_PRESCALER_BY_256

#elif TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_1024

#define TIM1_CLK		CPU_FREQ/TIM1_ICU_IO_CLK_PRESCALER_BY_1024

#endif

// for 256 and 1024, Min desired period should be 4 and 16 respectively

/* options:
*	TIM1_NORMAL_MODE
*	TIM1_FAST_PWM_MODE
*  	TIM1_PHASE_PWM_MODE 	
*  	TIM1_PHASE_FREQ_PWM_MODE
*  	TIM1_CTC_MODE 			
*
*/


#define 		TIM1_OPERTAION_MODE			TIM1_FAST_PWM_MODE



#if TIM1_OPERTAION_MODE==TIM1_FAST_PWM_MODE

/*
 * options:
 * TIM1_8_BIT_PWM
 * TIM1_9_BIT_PWM
 * TIM1_10_BIT_PWM
 * TIM1_OCR1A_PWM
 * TIM1_ICR1_PWM
 */

#define TIM1_FAST_PWM_RESOLUTION	TIM1_ICR1_PWM

/*
 * options:
 * TIM1_PWM_CHANNEL_A
 * TIM1_PWM_CHANNEL_B
 * TIM1_PWM_BOTH_CHANNELS
 */

#define TIM1_FAST_PWM_CHANNEL		TIM1_PWM_CHANNEL_B

/*
 * options:
 * TIM1_INVERTING_PWM
 * TIM1_NON_INVERTING_PWM
 */
#if TIM1_FAST_PWM_CHANNEL!=TIM1_PWM_BOTH_CHANNELS

#define TIM1_FAST_PWM_SIGNAL	 TIM1_NON_INVERTING_PWM

#else

#define	TIM1_FAST_PWM_A_SIGNAL 		TIM1_INVERTING_PWM

#define	TIM1_FAST_PWM_B_SIGNAL 		TIM1_INVERTING_PWM

#endif


#elif TIM1_OPERTAION_MODE==TIM1_NORMAL_MODE

#define TIM1_ICU_OPERATION 	TIM1_ICU_ON

#endif

#endif
