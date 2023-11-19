/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V03                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: TIMER1                             */
/********************************************/

#ifndef			TIM1_PRIV_H
#define			TIM1_PRIV_H


#define         TIM1_NORMAL_MODE  				0
#define         TIM1_FAST_PWM_MODE				1
#define         TIM1_PHASE_PWM_MODE 			3
#define         TIM1_PHASE_FREQ_PWM_MODE	 	5
#define         TIM1_CTC_MODE 					7

#define			TIM1_INT_CLK_BY_1               1
#define			TIM1_INT_CLK_BY_8               2
#define			TIM1_INT_CLK_BY_64              3
#define			TIM1_INT_CLK_BY_256             4
#define			TIM1_INT_CLK_BY_1024            5
#define			TIM1_EXT_CLK_ON_FALLING         6
#define         TIM1_EXT_CLK_ON_RISING          7



#define 	    TIM1_ICU_IO_CLK_PRESCALER_BY_1			1
#define 	    TIM1_ICU_IO_CLK_PRESCALER_BY_8		    8
#define 	    TIM1_ICU_IO_CLK_PRESCALER_BY_64		    64
#define 	    TIM1_ICU_IO_CLK_PRESCALER_BY_256	    256
#define 	    TIM1_ICU_IO_CLK_PRESCALER_BY_1024	    1024


#define         TIM1_ICU_ON      1
#define         TIM1_ICU_OFF     2


#define         TIM1_8_BIT_PWM                  0
#define         TIM1_9_BIT_PWM                  1
#define         TIM1_10_BIT_PWM                 3
#define         TIM1_OCR1A_PWM                  5
#define         TIM1_ICR1_PWM                   7


#define         TIM1_PWM_CHANNEL_A              0
#define         TIM1_PWM_CHANNEL_B              1
#define         TIM1_PWM_BOTH_CHANNELS          3

#define         TIM1_NON_INVERTING_PWM			2
#define         TIM1_INVERTING_PWM				3

#define 		TIM1_PRESCALER_MASK				0xF8

#endif
