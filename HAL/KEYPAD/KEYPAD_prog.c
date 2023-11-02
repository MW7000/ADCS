/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 1 AUG 2023   						*/
/*  SWC : KEYPAD                   			*/
/********************************************/

#include "STD_TYPES.h"
#include "DIO_int.h"
#include "KEYPAD_int.h"
#include "KEYPAD_config.h"
#include "KEYPAD_priv.h"

static uint8 local_uint8columns[KEYPAD_COLUMNS_NO]={KEYPAD_COLUMN1_PIN, KEYPAD_COLUMN2_PIN, KEYPAD_COLUMN3_PIN, KEYPAD_COLUMN4_PIN};
static uint8 local_uint8Rows[KEYPAD_ROWS_NO]={KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN, KEYPAD_ROW4_PIN};
static uint8 local_uint8Result;
static uint8 local_uint8keypadValues[4][4] = KEYPAD_KEY_VALUES;

void KEYPAD_voidInit(void){

	for(uint8 local_uint8Row=0;local_uint8Row<KEYPAD_ROWS_NO;local_uint8Row++){

		DIO_voidSetPinValue(local_uint8Rows[local_uint8Row], DIO_PIN_HIGH);

	}

}


uint8 KEYPAD_uint8GetPressedKey(void){
	
	local_uint8Result = KEYPAD_KEY_NOT_PRESSED;

	for(uint8 local_uint8Row=0;local_uint8Row<KEYPAD_ROWS_NO;local_uint8Row++){
		
		DIO_voidSetPinValue(local_uint8Rows[local_uint8Row], DIO_PIN_LOW);
		
		for(uint8 local_uint8Column=0;local_uint8Column<KEYPAD_COLUMNS_NO;local_uint8Column++){
			
			if(!DIO_uint8GetPinValue(local_uint8columns[local_uint8Column])){
				
				local_uint8Result = local_uint8keypadValues[local_uint8Row][local_uint8Column];
				while(!DIO_uint8GetPinValue(local_uint8columns[local_uint8Column]));				// polling until key is released
				DIO_voidSetPinValue(local_uint8Rows[local_uint8Row], DIO_PIN_HIGH);
				return local_uint8Result;
			}
			
		}
		DIO_voidSetPinValue(local_uint8Rows[local_uint8Row], DIO_PIN_HIGH);
		
	}
	return local_uint8Result;
	
}
