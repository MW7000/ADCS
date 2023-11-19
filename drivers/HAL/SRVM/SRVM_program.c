/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: Servo Motor                        */
/********************************************/




/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "SRVM_interface.h"
#include "SRVM_private.h"

#include "TIM1_int.h"



void SRVM_voidOn(uint8 Copy_uint8Angle)
{
	uint16 local_uint16MappedDutyCycle;

	/* TMR1 init at pwm mode 14 */
	// TIM1 should be initialized in the app file as this function isn't the initialization function for the SERVO motor.
	// if TIM_init() is called every time the user change input angle, this will cause useless overhead as init function is only called once.

	local_uint16MappedDutyCycle = MAP(SRVM_MIN_ANGLE, SRVM_MAX_ANGLE, SRVM_MIN_DC, SRVM_MAX_DC, Copy_uint8Angle);

	/* Set pwm fre. = 50 */
	/* Set pwm duty cycle between 5 : 10
	 depend on desired angle[0 : 180] */
	/* TMR1 start */
	TIM1_voidFGeneratePWM(SRVM_OPERATING_FREQ_IN_HZ, &local_uint16MappedDutyCycle);
}


void SRVM_voidOff(void)
{
	/* TMR1 stop */
	TIM1_voidDisable();
}



