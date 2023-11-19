/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V03                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: TIMER1                             */
/********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM1_int.h"
#include "TIM1_priv.h"
#include "TIM1_config.h"
#include "TIM1_reg.h"




uint16 initialCount=57535; // by 1 prescaler
uint16 TOP, Ton, Ttot,Ta,Tb,Tc;
uint8 ICUFlag=0;

void TIM1_voidInit(void){
	
	
#if	TIM1_OPERTAION_MODE == TIM1_NORMAL_MODE

TIM1_TCCR1A=0;

#elif TIM1_OPERTAION_MODE == TIM1_FAST_PWM_MODE

#if TIM1_FAST_PWM_RESOLUTION==TIM1_8_BIT_PWM

		SET_BIT(TIM1_TCCR1A, 0);
		CLEAR_BIT(TIM1_TCCR1A, 1);
		SET_BIT(TIM1_TCCR1B, 3);
		CLEAR_BIT(TIM1_TCCR1B, 4);
		TOP = 0x00FF;

#elif TIM1_FAST_PWM_RESOLUTION==TIM1_9_BIT_PWM

		CLEAR_BIT(TIM1_TCCR1A, 0);
		SET_BIT(TIM1_TCCR1A, 1);
		SET_BIT(TIM1_TCCR1B, 3);
		CLEAR_BIT(TIM1_TCCR1B, 4);
		TOP = 0x01FF;

#elif TIM1_FAST_PWM_RESOLUTION==TIM1_10_BIT_PWM


		SET_BIT(TIM1_TCCR1A, 0);
		SET_BIT(TIM1_TCCR1A, 1);
		SET_BIT(TIM1_TCCR1B, 3);
		CLEAR_BIT(TIM1_TCCR1B, 4);
		TOP = 0x03FF;

#elif TIM1_FAST_PWM_RESOLUTION==TIM1_ICR1_PWM

		CLEAR_BIT(TIM1_TCCR1A, 0);
		SET_BIT(TIM1_TCCR1A, 1);
		SET_BIT(TIM1_TCCR1B, 3);
		SET_BIT(TIM1_TCCR1B, 4);

#elif TIM1_FAST_PWM_RESOLUTION==TIM1_OCR1A_PWM

		SET_BIT(TIM1_TCCR1A, 0);
		SET_BIT(TIM1_TCCR1A, 1);
		SET_BIT(TIM1_TCCR1B, 3);
		SET_BIT(TIM1_TCCR1B, 4);

#endif

#if TIM1_FAST_PWM_CHANNEL==TIM1_PWM_CHANNEL_A

	TIM1_TCCR1A |= TIM1_FAST_PWM_SIGNAL<<6;

#elif TIM1_FAST_PWM_CHANNEL==TIM1_PWM_CHANNEL_B

	TIM1_TCCR1A |= TIM1_FAST_PWM_SIGNAL<<4;

#else

	TIM1_TCCR1A |= TIM1_FAST_PWM_A_SIGNAL<<6;
	TIM1_TCCR1A |= TIM1_FAST_PWM_B_SIGNAL<<4;

#endif


#elif TIM1_OPERTAION_MODE == TIM1_PHASE_PWM_MODE


#elif TIM1_OPERTAION_MODE == TIM1_PHASE_FREQ_PWM_MODE


#elif TIM1_OPERTAION_MODE == TIM1_CTC_MODE


#endif

#if (TIM1_CLK_CONFIG == TIM1_INT_CLK_BY_8) && (TIM1_OPERTAION_MODE == TIM1_NORMAL_MODE)
	
initialCount = 64535;
	
#elif (TIM1_CLK_CONFIG == TIM1_INT_CLK_BY_64) && (TIM1_OPERTAION_MODE == TIM1_NORMAL_MODE)

initialCount = 65410;
	
#elif (TIM1_CLK_CONFIG == TIM1_INT_CLK_BY_256) && (TIM1_OPERTAION_MODE == TIM1_NORMAL_MODE)
	
initialCount = 65410;			// mimimun desired period 4ms
	
#elif (TIM1_CLK_CONFIG == TIM1_INT_CLK_BY_1024) && (TIM1_OPERTAION_MODE == TIM1_NORMAL_MODE)
	
initialCount = 65410;			// mimimun desired period 16ms
	
#endif
	
}

void TIM1_voidEnable(void){

	TIM1_TCCR1B &= TIM1_PRESCALER_MASK;
	TIM1_TCCR1B |= TIM1_CLK_CONFIG;		// timer prescaler , internal or external clk

}


void TIM1_voidDisable(void){

	TIM1_TCCR1B &= TIM1_PRESCALER_MASK;

}



#if TIM1_OPERTAION_MODE==TIM1_NORMAL_MODE
void TIM1_voidSetBusyWait(uint16 copy_uint16DesiredPeriodInMilli){

	TIM1_TCCR1B &= TIM1_PRESCALER_MASK;
	TIM1_TCCR1B |= TIM1_CLK_CONFIG;		// timer prescaler , internal or external clk

	if(TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_256){

		copy_uint16DesiredPeriodInMilli/=4;
	}else if(TIM1_CLK_CONFIG==TIM1_INT_CLK_BY_1024){
		copy_uint16DesiredPeriodInMilli/=16;
	}

	for(uint16 k=0;k<copy_uint16DesiredPeriodInMilli;k++){
		
		//TIM1_TCNT1H = 0x00FF & (initialCount>>8);
		//TIM1_TCNT1L = 0x00FF & initialCount;
		TIM1_TCNT1 = initialCount;
		
		while(GET_BIT(TIM1_TIFR,2)==0);

		SET_BIT(TIM1_TIFR,2);			// clearing the TOV1 bit
	}
	TIM1_TCCR1B=0;
}


void TIM1_voidSetIntervalSingle(uint16 copy_uint16DesiredPeriod, void(*Copy_voidTaskToBeDone)(void)){
	
	
	
	
}

void TIM1_voidSetIntervalPeriodic(uint16 copy_uint16DesiredPeriod, void(*Copy_voidTaskToBeDone)(void)){
	
	
	
}


void TIM1_voidCount(void){

	TIM1_TCNT1=0;
}

uint16 TIM1_uint16ReadCounter(void){

	return TIM1_TCNT1;
}

#if TIM1_ICU_OPERATION==TIM1_ICU_ON
void TIM1_voidGetSignalInfo(uint8 *copy_puint8DutyCycle, uint16 *copy_uint16Freq){

	uint8 TCCR1B_config = 0b01000000 | TIM1_CLK_CONFIG;
	while(Tb<=Ta || Tc<=Tb){

		TIM1_TCNT1=0;
		TIM1_TCCR1B = TCCR1B_config;
		SET_BIT(TIM1_TIFR, 5);

		while (GET_BIT(TIM1_TIFR,5) == 0);

		Ta = TIM1_ICR1;

		SET_BIT(TIM1_TIFR, 5);

		while (GET_BIT(TIM1_TIFR,5) == 0);

		Tb = TIM1_ICR1;

		SET_BIT(TIM1_TIFR, 5);

		TIM1_TCCR1B = TIM1_CLK_CONFIG;

		while (GET_BIT(TIM1_TIFR,5) == 0);

		Tc = TIM1_ICR1;

		SET_BIT(TIM1_TIFR, 5);

		TIM1_TCCR1B = 0;
	}

	Ttot = Tb-Ta;
	Ton = Tc-Tb;

	if(Ton>=Ttot)
		Ton=Ton-(Ttot);		// because of ICU not detecting narrow pulses

	*copy_puint8DutyCycle = ((uint32)((uint32)Ton*(uint32)100)/Ttot)+1;
	*copy_uint16Freq = (TIM1_CLK/Ttot);
}


void TIM1_voidEnableICUINT(void){

//	SET_BIT(TIM1_ACSR,2);
	SET_BIT(TIM1_TIMSK,5);
}

void TIM1_voidDisableICUINT(void){

	CLEAR_BIT(TIM1_TIMSK,5);
}
#endif

#endif

#if TIM1_OPERTAION_MODE==TIM1_FAST_PWM_MODE

#if TIM1_FAST_PWM_RESOLUTION != TIM1_ICR1_PWM

void TIM1_voidGeneratePWM(uint16 *copy_puint16DutyCycle ){
	
#if TIM1_FAST_PWM_CHANNEL==TIM1_PWM_CHANNEL_A

#if TIM1_FAST_PWM_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1A = (((copy_puint16DutyCycle[0]*(TOP+1))-1)/1000);

#elif TIM1_FAST_PWM_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[0]=1000-copy_puint16DutyCycle[0];
	TIM1_OCR1A = (((copy_puint16DutyCycle[0]*(TOP+1))-1)/1000);

#endif

	
#elif TIM1_FAST_PWM_CHANNEL==TIM1_PWM_CHANNEL_B

#if TIM1_FAST_PWM_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1B = (((copy_puint16DutyCycle[0]*(TOP+1))-1)/1000);

#elif TIM1_FAST_PWM_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[0]=1000-copy_puint16DutyCycle[1]
	TIM1_OCR1B = (((copy_puint16DutyCycle[1]*(TOP+1))-1)/1000);

#endif

#else

#if TIM1_FAST_PWM_A_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1A = (((copy_puint16DutyCycle[0]*(TOP+1))-1)/1000);

#elif TIM1_FAST_PWM_A_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[0]=1000-copy_puint16DutyCycle[0];
	TIM1_OCR1A = (((copy_puint16DutyCycle[0]*(TOP+1))-1)/1000);

#endif

#if TIM1_FAST_PWM_B_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1B = (((copy_puint16DutyCycle[1]*(TOP+1))-1)/1000);

#elif TIM1_FAST_PWM_B_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[1]=1000-copy_puint16DutyCycle[1];
	TIM1_OCR1B = (((copy_puint16DutyCycle[1]*(TOP+1))-1)/1000);

#endif

	
#endif
	TIM1_TCCR1B &= TIM1_PRESCALER_MASK;
	TIM1_TCCR1B |= TIM1_CLK_CONFIG;		// timer prescaler , internal or external clk

}

#elif TIM1_FAST_PWM_RESOLUTION == TIM1_ICR1_PWM

void TIM1_voidFGeneratePWM(uint8 copy_uint8Freq , uint16 *copy_puint16DutyCycle){

	TIM1_ICR1 = (((uint32)TIM1_CLK)/copy_uint8Freq)-1;		// Setting ICR Value (Period time). 1 represents the overflow tick

	// Implement the DC input to handle float data type
#if TIM1_FAST_PWM_CHANNEL==TIM1_PWM_CHANNEL_A

#if TIM1_FAST_PWM_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1A = ((((uint32)copy_puint16DutyCycle[0]*(TIM1_ICR1+1))-1)/1000);   // Setting compare match Value (Duty Cycle)

#elif TIM1_FAST_PWM_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[0] = 1000 - copy_puint16DutyCycle[0];
	TIM1_OCR1A = ((((uint32)copy_puint16DutyCycle[0]*(TIM1_ICR1+1))-1)/1000);   // Setting compare match Value (Duty Cycle)

#endif


#elif TIM1_FAST_PWM_CHANNEL==TIM1_PWM_CHANNEL_B

#if TIM1_FAST_PWM_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1B = ((((uint32)copy_puint16DutyCycle[0]*(TIM1_ICR1+1))-1)/1000);

#elif TIM1_FAST_PWM_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[1] = 1000 - copy_puint16DutyCycle[1];
	TIM1_OCR1B = ((((uint32)copy_puint16DutyCycle[0]*(TIM1_ICR1+1))-1)/1000);

#endif

#else			// 2 channels selected to operate together

#if TIM1_FAST_PWM_A_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1A = ((((uint32)copy_puint16DutyCycle[0]*(TIM1_ICR1+1))-1)/1000);

#elif TIM1_FAST_PWM_A_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[0] = 1000 - copy_puint16DutyCycle[0];
	TIM1_OCR1A = ((((uint32)copy_puint16DutyCycle[0]*(TIM1_ICR1+1))-1)/1000);

#endif

#if TIM1_FAST_PWM_B_SIGNAL==TIM1_NON_INVERTING_PWM

	TIM1_OCR1B = ((((uint32)copy_puint16DutyCycle[1]*(TIM1_ICR1+1))-1)/1000);

#elif TIM1_FAST_PWM_B_SIGNAL==TIM1_INVERTING_PWM

	copy_puint16DutyCycle[1]=1000-copy_puint16DutyCycle[1];
	TIM1_OCR1B = ((((uint32)copy_puint16DutyCycle[1]*(TIM1_ICR1+1))-1)/1000);

#endif


#endif

	TIM1_TCCR1B &= TIM1_PRESCALER_MASK;
	TIM1_TCCR1B |= TIM1_CLK_CONFIG;		// timer prescaler , internal or external clk

}
#endif

#endif

void __vector_6(void) __attribute__((signal , used));
void __vector_6(void)
{

}
