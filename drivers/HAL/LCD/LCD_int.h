/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 5 SEP 2023	   					*/
/*  SWC : LCD                   			*/
/********************************************/


#ifndef  LCD_INT_H
#define  LCD_INT_H


void LCD_voidInit(void);

void LCD_voidWriteCommand(uint8 copy_uint8Command);

void LCD_voidWriteChar(char copy_uint8Char);

void LCD_voidWriteToCGRAM(uint8 *copy_uint8Charcontent, uint8 copy_uint8CGRAMCharAddress);

void LCD_voidWriteString(char * copy_pcharStr);

void LCD_voidGoToLocation(uint8 copy_uint8Row , uint8 copy_uint8_colmun);

void LCD_voidClearScreen(void);

// max of 5 digits to print

void LCD_voidWriteNumber(uint32 copy_uint16No);

//max of 3 digits after . sign and 6 digits before

void LCD_voidWriteFloatingNumber(f32 copy_uintf32No);

#endif
