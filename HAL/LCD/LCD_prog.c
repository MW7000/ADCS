/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 5 SEP 2023	   					*/
/*  SWC : LCD                   			*/
/********************************************/


#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "DIO_int.h"
#include  "LCD_int.h"
#include  "LCD_priv.h"
#include  "LCD_config.h"
#include  <util/delay.h>


void LCD_voidInit(void){

	_delay_ms(30);
	LCD_voidWriteCommand(LCD_RETURN_HOME_CMD);
	LCD_voidWriteCommand(32|LCD_INTERFACE_MODE|LCD_ACTIVATED_LINES|LCD_FONT_SIZE);
	_delay_ms(1);
	LCD_voidWriteCommand(12|LCD_CURSOR_OPERATION|LCD_CURSOR_APPEARANCE);
	_delay_ms(1);
	LCD_voidWriteCommand(LCD_CLEAR_DISPLAY_CMD);
	_delay_ms(1);
	LCD_voidWriteCommand(LCD_ENTRY_MODE_SET_CMD);

}

void LCD_voidWriteCommand(uint8 copy_uint8Command){

   DIO_voidSetPinValue(LCD_PIN_RS, DIO_PIN_LOW);

   LCD_voidExecuteCommand(copy_uint8Command);

}

void LCD_voidWriteChar(char copy_uint8Char){

    DIO_voidSetPinValue(LCD_PIN_RS, DIO_PIN_HIGH);

	LCD_voidExecuteCommand(copy_uint8Char);

}

void LCD_voidWriteString(char * copy_pcharStr){

	DIO_voidSetPinValue(LCD_PIN_RS, DIO_PIN_HIGH);

	uint8 Local_uint8Index = 0;

	while(copy_pcharStr[Local_uint8Index]!='\0'){

		LCD_voidWriteChar(copy_pcharStr[Local_uint8Index]);

		Local_uint8Index ++;
	}

}

void LCD_voidGoToLocation(uint8 copy_uint8Row , uint8 copy_uint8Colmun){

	uint8 local_uint8LCDLocation;

	if(copy_uint8Row == 1){

		local_uint8LCDLocation = 0x80 + copy_uint8Colmun;


	}else if (copy_uint8Row == 2){

		local_uint8LCDLocation = 0xC0 + copy_uint8Colmun;

	}
	else if(copy_uint8Row == 3){

		local_uint8LCDLocation = 0x94 + copy_uint8Colmun;

	}
	else if(copy_uint8Row == 4){

		local_uint8LCDLocation = 0xD4 + copy_uint8Colmun;

	}

	LCD_voidWriteCommand(local_uint8LCDLocation);

}

void LCD_voidClearScreen(void){

	LCD_voidWriteCommand(LCD_CLEAR_DISPLAY_CMD);

}


void LCD_voidExecuteCommand(uint8 copy_uint8Command){

	//DIO_voidSetPinValue(LCD_PIN_RW , DIO_PIN_LOW);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_PIN_E, DIO_PIN_HIGH);
    _delay_ms(1);


#if		LCD_INTERFACE_MODE==LCD_EIGHT_BIT_MODE

	DIO_voidSetPinValue(LCD_PIN_D0 , GET_BIT(copy_uint8Command, 0 ));
	DIO_voidSetPinValue(LCD_PIN_D1 , GET_BIT(copy_uint8Command, 1 ));
	DIO_voidSetPinValue(LCD_PIN_D2 , GET_BIT(copy_uint8Command, 2 ));
	DIO_voidSetPinValue(LCD_PIN_D3 , GET_BIT(copy_uint8Command, 3 ));
	DIO_voidSetPinValue(LCD_PIN_D4 , GET_BIT(copy_uint8Command, 4 ));
	DIO_voidSetPinValue(LCD_PIN_D5 , GET_BIT(copy_uint8Command, 5 ));
	DIO_voidSetPinValue(LCD_PIN_D6 , GET_BIT(copy_uint8Command, 6 ));
	DIO_voidSetPinValue(LCD_PIN_D7 , GET_BIT(copy_uint8Command, 7 ));

#elif	LCD_INTERFACE_MODE==LCD_FOUR_BIT_MODE

	DIO_voidSetPinValue(LCD_PIN_D4 , GET_BIT(copy_uint8Command, 4 ));
	DIO_voidSetPinValue(LCD_PIN_D5 , GET_BIT(copy_uint8Command, 5 ));
	DIO_voidSetPinValue(LCD_PIN_D6 , GET_BIT(copy_uint8Command, 6 ));
	DIO_voidSetPinValue(LCD_PIN_D7 , GET_BIT(copy_uint8Command, 7 ));

	_delay_ms(1);
    DIO_voidSetPinValue(LCD_PIN_E, DIO_PIN_LOW);
    _delay_ms(2);

	DIO_voidSetPinValue(LCD_PIN_E, DIO_PIN_HIGH);
    _delay_ms(1);

	DIO_voidSetPinValue(LCD_PIN_D4 , GET_BIT(copy_uint8Command, 0 ));
	DIO_voidSetPinValue(LCD_PIN_D5 , GET_BIT(copy_uint8Command, 1 ));
	DIO_voidSetPinValue(LCD_PIN_D6 , GET_BIT(copy_uint8Command, 2 ));
	DIO_voidSetPinValue(LCD_PIN_D7 , GET_BIT(copy_uint8Command, 3 ));

#endif

	_delay_ms(1);
    DIO_voidSetPinValue(LCD_PIN_E, DIO_PIN_LOW);
    _delay_ms(2);

}

// max of 5 digits to print
void LCD_voidWriteNumber(uint32 copy_uint16No){

	uint32 divisor;
	uint32 modFact=10;

	while((copy_uint16No%modFact)!=copy_uint16No){

		modFact*=10;
	}
	divisor=modFact/10;
	while(divisor!=0){

		LCD_voidWriteChar(((copy_uint16No%modFact)/divisor)+48);
		divisor/=10;
		modFact/=10;
	}
}
//max of 3 digits after . sign and 6 digits before

void LCD_voidWriteFloatingNumber(f32 copy_uintf32No){

	uint32 divisor;
	uint32 modFact=10;
	uint32 NOtoPrint = copy_uintf32No*100;

	while((NOtoPrint%modFact)!=NOtoPrint){

		modFact*=10;
	}

	divisor=modFact/10;
	while(divisor!=0){

		LCD_voidWriteChar(((NOtoPrint%modFact)/divisor)+48);
		divisor/=10;
		modFact/=10;
		if(modFact==100){
			LCD_voidWriteChar('.');
		}
	}
}

void LCD_voidWriteToCGRAM(uint8 *copy_uint8Charcontent, uint8 copy_uint8CGRAMCharAddress){

	copy_uint8CGRAMCharAddress*=8;

	LCD_voidWriteCommand(0x40+copy_uint8CGRAMCharAddress);

	for(uint8 i=0;i<LCD_CUSTOM_CHAR_ROWS_NO;i++){

		LCD_voidWriteChar(copy_uint8Charcontent[i]);

	}
	LCD_voidExecuteCommand(0x80+copy_uint8CGRAMCharAddress);
}

