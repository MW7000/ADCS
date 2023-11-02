/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 5 SEP 2023	   					*/
/*  SWC : LCD                   			*/
/********************************************/


#ifndef   LCD_PRIV_H
#define   LCD_PRIV_H



#define   LCD_FOUR_BIT_MODE   0
#define   LCD_EIGHT_BIT_MODE  16

#define   LCD_2_LINES         8
#define   LCD_1_LINE          0

#define   LCD_5X7_FONT        0
#define   LCD_5X10_FONT       4

#define   LCD_CURSOR_DISPLAYED		2
#define   LCD_CURSOR_HIDDEN         0

#define	  LCD_CURSOR_BLINK		1
#define   LCD_CURSOR_STATIC     0

#define	  LCD_CLEAR_DISPLAY_CMD		1
#define	  LCD_ENTRY_MODE_SET_CMD	6
#define	  LCD_RETURN_HOME_CMD		0x02


static void  LCD_voidExecuteCommand(uint8 copy_uint8Command);

#endif
