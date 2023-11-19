/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V03                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: TIMER1                             */
/********************************************/

#ifndef			TIM1_INT_H
#define			TIM1_INT_H


void TIM1_voidInit(void);

void TIM1_voidSetBusyWait(uint16 copy_uint16DesiredPeriodInMilli);

void TIM1_voidSetIntervalSingle(uint16 copy_uint16DesiredPeriod, void(*Copy_voidTaskToBeDone)(void));

void TIM1_voidSetIntervalPeriodic(uint16 copy_uint16DesiredPeriod, void(*Copy_voidTaskToBeDone)(void));

void TIM1_voidCount(void);

uint16 TIM1_uint16ReadCounter(void);

/* 2 PWM channels can be operated together
 * param : selected channels PWM DC and Freq values
 * all the channels work @ the same freq
 * array element 0 is relevant to channel A
 * array element 1 is related to channel B
 * copy_puint16DutyCycle param accepts floating-point numbers and should be passed after multiplying it by 10
 * copy_uint8Freq param is in HZ
 */

void TIM1_voidGeneratePWM(uint16 *copy_puint16DutyCycle);

void TIM1_voidFGeneratePWM(uint8 copy_uint8Freq , uint16 *copy_puint16DutyCycle);

void TIM1_voidEnable(void);

void TIM1_voidDisable(void);

void TIM1_voidEnableICUINT(void);

void TIM1_voidDisableICUINT(void);
void TIM1_voidGetSignalInfo(uint8 *copy_uint8DutyCycle, uint16 *copy_uint16Freq);

#endif

