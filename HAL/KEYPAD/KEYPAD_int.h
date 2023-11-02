/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 1 AUG 2023   						*/
/*  SWC : KEYPAD                   			*/
/********************************************/


#ifndef KEYPAD_INT_H
#define KEYPAD_INT_H

void KEYPAD_voidInit(void);

uint8 KEYPAD_uint8GetPressedKey(void);

#define 	KEYPAD_KEY_NOT_PRESSED	0xFF

#endif
