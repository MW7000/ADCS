/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V02                            */
/*  Date: 26 OCT 2023	   					*/
/*  SWC : TIM0                   			*/
/********************************************/


#ifndef		TIM0_PRIV_H
#define 	TIM0_PRIV_H

#define 	TIM0_NORMAL_MODE							1
#define 	TIM0_CTC_MODE								3
#define 	TIM0_FAST_PWM_MODE							5
#define 	TIM0_PHASE_CORRECT_PWM_MODE					7


#define 	TIM0_PRESCALER_CLK_IO_BY_1					1
#define 	TIM0_PRESCALER_CLK_IO_BY_8					2
#define 	TIM0_PRESCALER_CLK_IO_BY_64					3
#define 	TIM0_PRESCALER_CLK_IO_BY_256				4
#define 	TIM0_PRESCALER_CLK_IO_BY_1024				5
#define 	TIM0_PRESCALER_EXTERNAL_CLK_FALLING_EDGE	6
#define 	TIM0_PRESCALER_EXTERNAL_CLK_RISING_EDGE		7


#define     TIM0_PWM_INVERTED                  1
#define     TIM0_PWM_NON_INVERTED              2


#define     TIM0_CLK_PRESCALER_1               1
#define     TIM0_CLK_PRESCALER_8			   8
#define     TIM0_CLK_PRESCALER_64              64
#define     TIM0_CLK_PRESCALER_256             256
#define     TIM0_CLK_PRESCALER_1024            1024

#define		TIM0_TOP_VALUE					   255

#define		TIM0_TOP_VALUE_PLUS_1			   256

#define 	TIM0_CTC_VALUE					   249
#define 	TIM0_CTC_VALUE_PLUS_1			   250

#define		TIM0_TCCR0_PRESCALER_MASK					0xF8



#endif
