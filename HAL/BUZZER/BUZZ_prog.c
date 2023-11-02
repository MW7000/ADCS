/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 2 NOV 2023	   					*/
/*  SWC : BUZZER                   			*/
/********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "BUZZ_int.h"
#include "BUZZ_config.h"
#include "DIO_int.h"
#include "TIM2_int.h"

void BUZZER_voidOutputTune(uint16 copy_uint16Delay_ms){

	DIO_voidSetPinValue(BUZZER_PIN,DIO_PIN_HIGH);
	TIM2_voidSetBusyWaitSynch(copy_uint16Delay_ms);
	DIO_voidSetPinValue(BUZZER_PIN,DIO_PIN_LOW);
	TIM2_voidSetBusyWaitSynch(copy_uint16Delay_ms);
}



