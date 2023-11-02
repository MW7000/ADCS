/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 2 NOV 2023                        */
/*  SWC: Servo Motor                        */
/********************************************/


#ifndef  SRVM_PRIVATE_H
#define  SRVM_PRIVATE_H


// for controlling Servo motor, actual DC values should be between 2.4% and 12% instead of the theoretical values [5%,10%] for full range [0,180]
// DC is multiplied here by 10 to enable floating-point inputs for the TIM1_voidFGeneratePWM(uint8 copy_uint8Freq , uint16 *copy_puint16DutyCycle)
#define    SRVM_MAX_DC         120
#define    SRVM_MIN_DC         25

#define    SRVM_MAX_ANGLE      180
#define    SRVM_MIN_ANGLE      0

#define    SRVM_OPERATING_FREQ_IN_HZ 	50


#endif
