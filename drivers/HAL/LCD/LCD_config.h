/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 5 SEP 2023	   					*/
/*  SWC : LCD                   			*/
/********************************************/


#ifndef  LCD_CONFIG_H
#define  LCD_CONFIG_H



/*
 * options:
 * LCD_FOUR_BIT_MODE
 * LCD_EIGHT_BIT_MODE
 */

#define LCD_INTERFACE_MODE   LCD_FOUR_BIT_MODE


#if 	LCD_INTERFACE_MODE==LCD_EIGHT_BIT_MODE

#define  LCD_PIN_RS     DIO_PIN_NO_2
#define  LCD_PIN_RW     DIO_PIN_NO_3
#define  LCD_PIN_E      DIO_PIN_NO_4

#define  LCD_PIN_D0     DIO_PIN_NO_5
#define  LCD_PIN_D1     DIO_PIN_NO_6
#define  LCD_PIN_D2     DIO_PIN_NO_7
#define  LCD_PIN_D3     DIO_PIN_NO_8
#define  LCD_PIN_D4     DIO_PIN_NO_9
#define  LCD_PIN_D5     DIO_PIN_NO_10
#define  LCD_PIN_D6     DIO_PIN_NO_11
#define  LCD_PIN_D7     DIO_PIN_NO_12

#elif	LCD_INTERFACE_MODE==LCD_FOUR_BIT_MODE

#define  LCD_PIN_RS     DIO_PIN_NO_3
//#define  LCD_PIN_RW     DIO_PIN_NO_3
#define  LCD_PIN_E      DIO_PIN_NO_2

#define  LCD_PIN_D4     DIO_PIN_NO_8
#define  LCD_PIN_D5     DIO_PIN_NO_9
#define  LCD_PIN_D6     DIO_PIN_NO_10
#define  LCD_PIN_D7     DIO_PIN_NO_12


#endif


/*
 * options:
 * LCD_5X7_FONT 		>> corresponds to 8 characters written to CGRAM
 * LCD_5X10_FONT        >> corresponds to 4 characters written to CGRAM
 */

#define	LCD_FONT_SIZE 		LCD_5X7_FONT

/*
 * options:
 * LCD_2_LINES
 * LCD_1_LINE
 */
#if LCD_FONT_SIZE == LCD_5X7_FONT

#define LCD_CUSTOM_CHAR_ROWS_NO 	8

#else

#define LCD_CUSTOM_CHAR_ROWS_NO     11

#endif

#define LCD_ACTIVATED_LINES		LCD_2_LINES

/*
 * options:
 * LCD_CURSOR_DISPLAYED
 * LCD_CURSOR_HIDDEN
 */

#define	LCD_CURSOR_OPERATION  	LCD_CURSOR_HIDDEN


/*options:
 * LCD_CURSOR_BLINK
 * LCD_CURSOR_STATIC
 */

#define	LCD_CURSOR_APPEARANCE	LCD_CURSOR_STATIC


#endif
