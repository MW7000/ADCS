/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 1 AUG 2023   						*/
/*  SWC : KEYPAD                   			*/
/********************************************/


#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#define 	KEYPAD_ROW1_PIN         DIO_PIN_NO_21
#define 	KEYPAD_ROW2_PIN         DIO_PIN_NO_20
#define 	KEYPAD_ROW3_PIN         DIO_PIN_NO_19
#define 	KEYPAD_ROW4_PIN         DIO_PIN_NO_18
#define 	KEYPAD_COLUMN1_PIN      DIO_PIN_NO_31
#define 	KEYPAD_COLUMN2_PIN      DIO_PIN_NO_30
#define 	KEYPAD_COLUMN3_PIN      DIO_PIN_NO_29
#define 	KEYPAD_COLUMN4_PIN      DIO_PIN_NO_27

//  Columns are configured as input
//  Rows are configured as output


#define 	KEYPAD_KEY_VALUES 		{{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','$'},{'*','0','#','@'}}
 

#endif
