/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V03                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: TIMER1                             */
/********************************************/

#ifndef			TIM1_REG_H
#define			TIM1_REG_H

#define		TIM1_TCCR1A    *(( volatile uint8*)0x4F )
#define		TIM1_TCCR1B    *(( volatile uint8*)0x4E )
#define		TIM1_TCNT1H    *(( volatile uint8*)0x4D )
#define		TIM1_TCNT1L    *(( volatile uint8*)0x4C )
#define		TIM1_TCNT1     *(( volatile uint16*)0x4C )
#define		TIM1_OCR1AH    *(( volatile uint8*)0x4B )
#define		TIM1_OCR1AL    *(( volatile uint8*)0x4A )
#define		TIM1_OCR1A	   *(( volatile uint16*)0x4A )
#define		TIM1_OCR1BH    *(( volatile uint8*)0x49 )
#define		TIM1_OCR1BL    *(( volatile uint8*)0x48 )
#define		TIM1_OCR1B	   *(( volatile uint16*)0x48 )
#define		TIM1_ICR1H     *(( volatile uint8*)0x47 )
#define		TIM1_ICR1L     *(( volatile uint8*)0x46 )
#define		TIM1_ICR1	   *(( volatile uint16*)0x46 )
#define		TIM1_TIMSK     *(( volatile uint8*)0x59 )
#define		TIM1_TIFR      *(( volatile uint8*)0x58 )
#define		TIM1_ACSR	   *(( volatile uint8*)0x28 )


#endif
