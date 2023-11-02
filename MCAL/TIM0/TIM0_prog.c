/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V02                            */
/*  Date: 26 OCT 2023	   					*/
/*  SWC : TIM0                   			*/
/********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM0_int.h"
#include "TIM0_priv.h"
#include "TIM0_config.h"
#include "TIM0_reg.h"

static uint8 count;
static uint32 private_uint32CounterMax;
static uint8 private_uint8DelayType;
static void (*private_fptrCallBackFunc)(void)=NULL;		// since only one mode is selected, there is only one pointer to function

void TIM0_voidInit(void){
	
#if TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_1
	
	count = 31;
	
#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_8
	
	count = 4;
	
#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_64
	
	count = 125;
	
#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_256

	count = 31;			// 31.25
	
#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_1024
			
	count = 8;			// 7.8125
	
#endif

	
#if  TIM0_MODE == TIM0_NORMAL_MODE
	
	CLEAR_BIT(TCCR0,TCCR0_WGM01);
	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	
	
	CLEAR_BIT(TCCR0,TCCR0_COM00);			// disconnecting OC0 (Normal bit operation)
	CLEAR_BIT(TCCR0,TCCR0_COM01);


#elif	TIM0_MODE == TIM0_CTC_MODE

	SET_BIT(TCCR0,TCCR0_WGM01);
	CLEAR_BIT(TCCR0,TCCR0_WGM00);

	CLEAR_BIT(TCCR0,TCCR0_COM00);			// disconnecting OC0 (Normal bit operation)
	CLEAR_BIT(TCCR0,TCCR0_COM01);


#elif	TIM0_MODE == TIM0_FAST_PWM_MODE

	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);


#if		TIM0_PWM_MODE == TIM0_PWM_INVERTED

	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif	TIM0_PWM_MODE == TIM0_PWM_NON_INVERTED

	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);


#endif

#elif	TIM0_MODE == TIM0_PHASE_CORRECT_PWM_MODE

	CLEAR_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);


#if		TIM0_PWM_MODE == TIM0_PWM_INVERTED

	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif	TIM0_PWM_MODE == TIM0_PWM_NON_INVERTED

	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);


#endif



#endif


	TCNT0 = 0;
	
}

#if TIM0_MODE == TIM0_NORMAL_MODE

void TIM0_voidSetBusyWaitSynch(uint16 copy_uint16_periodInMilliSeconds){
	

	if(TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_8||TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_1){

		TCNT0=0;
	
	for(uint16 j=0;j<copy_uint16_periodInMilliSeconds;j++){
		
		for(uint16 i=0;i<count;i++){
		
			while(GET_BIT(TIFR,0)==0);			// waiting for the TOV0 to be set
			SET_BIT(TIFR,0);							// clearing the TOV0 flag
														// counting a millisecond
		}	
	}

	}else{

		for(uint16 j=0;j<copy_uint16_periodInMilliSeconds;j++){

			TCNT0 = 256-count;
			while(GET_BIT(TIFR,0)==0);			// waiting for the TOV0 to be set
			SET_BIT(TIFR,0);							// clearing the TOV0 flag
													// counting a millisecond
		}
	}

}
#endif


void TIM0_voidSetDelayAsynch_ms(uint16 copy_uint16Delay_ms, uint8 copy_uint8DelayType){

#if TIM0_MODE==TIM0_NORMAL_MODE

	SET_BIT(TIMSK,TIMSK_TOIE0);		// enabling OVF interrupt

	// overflow method
	uint32	local_uint32TicksNO = (uint32)copy_uint16Delay_ms * TIM0_TICK_TIME_INVERSE;		// number of ticks need to get the required delay
	TCNT0 = TIM0_TOP_VALUE_PLUS_1-(local_uint32TicksNO % TIM0_TOP_VALUE_PLUS_1) ;	 // preload value

	private_uint32CounterMax = (local_uint32TicksNO/TIM0_TOP_VALUE_PLUS_1)+1;						// counter value + preload cycle


#elif TIM0_MODE==TIM0_CTC_MODE

	SET_BIT(TIMSK,TIMSK_OCIE0);		// enabling OCM interrupt

	uint32	local_uint32TicksNO = (uint32)copy_uint16Delay_ms * TIM0_TICK_TIME_INVERSE;		// number of ticks need to get the required delay

	if(((local_uint32TicksNO%TIM0_CTC_VALUE_PLUS_1)==local_uint32TicksNO)||((local_uint32TicksNO%TIM0_CTC_VALUE_PLUS_1)==0)){

		private_uint32CounterMax = 1;
		OCR0 = local_uint32TicksNO-1;
	}
	else{

		OCR0 = TIM0_CTC_VALUE;
		private_uint32CounterMax = local_uint32TicksNO / TIM0_CTC_VALUE_PLUS_1;

	}

#endif

	private_uint8DelayType = copy_uint8DelayType;

}



uint8 TIM0_uint8ReadCounter(void){

	return TCNT0;
}


void TIM0_voidStop(void){
	
	TCCR0 &= TIM0_TCCR0_PRESCALER_MASK;
	
}

void TIM0_voidStart(void){
	
	TCCR0 |= TIM0_PRESCALER_CHOICE;
	
}

void TIM0_voidClearCounter(void){

	TCCR0 &= TIM0_TCCR0_PRESCALER_MASK;			// stopping timer
	TCNT0=0;
	TCCR0 |= TIM0_PRESCALER_CHOICE;				// starting timer
}

void TIM0_voidSetCallBackFunc(void (*copy_fptrCallBackFunc) (void)){

	if (copy_fptrCallBackFunc != NULL) {

			private_fptrCallBackFunc = copy_fptrCallBackFunc;

	}
}

void TIM0_voidSetCompareMatchValue(uint8 copy_uint8CompareMatchValue){

	OCR0 = copy_uint8CompareMatchValue;
}

#if	TIM0_MODE == TIM0_FAST_PWM_MODE

void TIM0_voidGeneratePWMSignal(uint8 copy_uint8SignalDC){

#if		TIM0_PWM_MODE == TIM0_PWM_NON_INVERTED

	if((copy_uint8SignalDC>0)&&(copy_uint8SignalDC<101))
		OCR0 = (((uint16)copy_uint8SignalDC * TIM0_TOP_VALUE_PLUS_1)/100)-1;  // because of the OVF tick

#elif 	TIM0_PWM_MODE == TIM0_PWM_INVERTED

	if((copy_uint8SignalDC>=0)&&(copy_uint8SignalDC<100)){

		copy_uint8SignalDC = 100 - copy_uint8SignalDC;
		OCR0 = (((uint16)copy_uint8SignalDC * TIM0_TOP_VALUE_PLUS_1)/100)-1;
	}
#endif

}

#elif TIM0_MODE == TIM0_PHASE_CORRECT_PWM_MODE

void TIM0_voidGeneratePhaseCorrectPWMSignal(uint8 copy_uint8SignalDC){

#if		TIM0_PWM_MODE == TIM0_PWM_NON_INVERTED

		OCR0 = (((uint16)copy_uint8SignalDC * TIM0_TOP_VALUE)/100);

#elif 	TIM0_PWM_MODE == TIM0_PWM_INVERTED


		copy_uint8SignalDC = 100 - copy_uint8SignalDC;
		OCR0 = (((uint16)copy_uint8SignalDC * TIM0_TOP_VALUE)/100);

#endif

}

#endif

void __vector_10(void)	__attribute__((signal, used));		// OCM interrupt
void __vector_10(void){

#if TIM0_MODE==TIM0_CTC_MODE

	static uint32 local_uint32Counter = 0;
	local_uint32Counter++;
	if(local_uint32Counter==private_uint32CounterMax){
		local_uint32Counter=0;
		private_fptrCallBackFunc();
		if(TIM0_DELAY_SINGLE==private_uint8DelayType){
			CLEAR_BIT(TIMSK, TIMSK_OCIE0);					// disabling interrupt
		}
	}
#else

	private_fptrCallBackFunc();

#endif

}

void __vector_11(void)	__attribute__((signal, used));		// overflow interrupt
void __vector_11(void){

#if TIM0_MODE==TIM0_NORMAL_MODE

	static uint32 local_uint32Counter = 0;
	local_uint32Counter++;
	if(local_uint32Counter==private_uint32CounterMax){
		local_uint32Counter=0;
		private_fptrCallBackFunc();
		if(private_uint8DelayType == TIM0_DELAY_SINGLE){
			CLEAR_BIT(TIMSK, TIMSK_TOIE0);					// disabling interrupt
		}
	}
#else

	private_fptrCallBackFunc();

#endif

}

