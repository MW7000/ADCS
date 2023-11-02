/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V02                            */
/*  Date: 26 OCT 2023	   					*/
/*  SWC : TIM0                   			*/
/********************************************/

#ifndef		TIM0_INT_H
#define 	TIM0_INT_H

#define		TIM0_DELAY_SINGLE		1
#define		TIM0_DELAY_CONTINUOUS	2


void TIM0_voidInit(void);

void TIM0_voidStop(void);

void TIM0_voidSetBusyWaitSynch(uint16 copy_uint16_periodInMilliSeconds);

/*
 * copy_uint8DelayType parameter options :
 *
 *        TIM0_DELAY_SINGLE
 *        TIM0_DELAY_CONTINUOUS
 *
 */

void TIM0_voidSetDelayAsynch_ms(uint16 copy_uint16Delay_ms, uint8 copy_uint8DelayType);

void TIM0_voidClearCounter(void);

uint8 TIM0_uint8ReadCounter(void);

void TIM0_voidStart(void);

void TIM0_voidSetCallBackFunc(void (*copy_fptrCallBackFunc) (void));

void TIM0_voidSetCompareMatchValue(uint8 copy_uint8CompareMatchValue);

void TIM0_voidGeneratePWMSignal(uint8 copy_uint8SignalDC);

void TIM0_voidGeneratePhaseCorrectPWMSignal(uint8 copy_uint8SignalDC);

#endif
