/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 2 NOV 2023                        */
/*  SWC : APP                               */
/********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_int.h"
#include "DIO_int.h"
#include "TIM0_int.h"
#include "TIM1_int.h"
#include "TIM2_int.h"
#include "GI_int.h"
#include "TWI_int.h"

#include "LCD_int.h"
#include "EX_EEPROM_int.h"
#include "KEYPAD_int.h"
#include "SRVM_interface.h"
#include "BUZZ_int.h"


// This address holds initially non-zero value which then decides whether it's the user first time to login the system or not
#define		APP_FIRST_TIME_FLAG_ADDRESS		10

#define		APP_PASS_CHARACTERS_NUMBER		8
#define		APP_PASS_FIRST_CHAR_ADDRESS		13
#define		APP_PASS_MATCH					1
#define		APP_PASS_MISMATCH				2
#define		APP_PASS_ENTRIES_MAX_COUNT		3
#define		APP_SIREN_TIME					80
#define		APP_CLOSURE_TIMEOUT				30


static uint8 private_APPuint8KeypadReading;
void APP_voidSetKeypadReading(void);

void main(void){

	uint8 local_uint8firstTimeFlag, local_uint8PassTemp[8], local_uint8PasswordConformity=APP_PASS_MATCH, local_uint8PassEntriesCount=0;
	uint8 local_uint8DoorClosureCounter=0;

	PORT_voidInit();
	TIM2_voidInit();
	TIM1_voidInit();
	TIM0_voidInit();
	TWI_voidInit();
	GI_voidEnable();

	LCD_voidInit();
	KEYPAD_voidInit();
	SRVM_voidOn(45);				// Door initially closed
	private_APPuint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;

	TIM0_voidSetCallBackFunc(&APP_voidSetKeypadReading);
	TIM0_voidSetDelayAsynch_ms(100,TIM0_DELAY_CONTINUOUS);		// every 100ms we get the keypad reading
	TIM0_voidStart();
	TIM2_voidStart();

	while(1){

		if(private_APPuint8KeypadReading!=KEYPAD_KEY_NOT_PRESSED){

			private_APPuint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;
			LCD_voidGoToLocation(1,5);
			LCD_voidWriteString("Automated");
			LCD_voidGoToLocation(2,8);
			LCD_voidWriteString("Door");
			LCD_voidGoToLocation(3,6);
			LCD_voidWriteString("Control");
			LCD_voidGoToLocation(4,7);
			LCD_voidWriteString("System");
			TIM2_voidSetBusyWaitSynch(2000);			// welcome message

			LCD_voidClearScreen();
			LCD_voidGoToLocation(1,8);
			LCD_voidWriteString("ADCS");
			LCD_voidGoToLocation(2,0);

			local_uint8firstTimeFlag=EX_EEPROM_uint8ReadByte(APP_FIRST_TIME_FLAG_ADDRESS);
			if(local_uint8firstTimeFlag!=0){

				EX_EEPROM_voidWriteByte(APP_FIRST_TIME_FLAG_ADDRESS,0);					// first time entrance

				LCD_voidWriteString("Create Your Password");
				LCD_voidGoToLocation(3,0);
				LCD_voidWriteString("> ");
				for(uint8 i=0;i<APP_PASS_CHARACTERS_NUMBER;i++){

					while(private_APPuint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
					EX_EEPROM_voidWriteByte(APP_PASS_FIRST_CHAR_ADDRESS+i, private_APPuint8KeypadReading);
					LCD_voidWriteChar(private_APPuint8KeypadReading);
					BUZZER_voidOutputTune(70);

					private_APPuint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;

				}
				TIM2_voidSetBusyWaitSynch(1000);
				LCD_voidClearScreen();
				LCD_voidGoToLocation(1,2);
				LCD_voidWriteString("Password Created");
				LCD_voidGoToLocation(2,4);
				LCD_voidWriteString("Successfully");
				TIM2_voidSetBusyWaitSynch(2000);
			}
			else{

				do
				{
					LCD_voidGoToLocation(1,8);
					LCD_voidWriteString("ADCS");
					LCD_voidGoToLocation(2,0);
					LCD_voidWriteString("Enter Your Password");							// second time logging
					LCD_voidGoToLocation(3,0);
					LCD_voidWriteString("> ");
					for(uint8 i=0;i<APP_PASS_CHARACTERS_NUMBER;i++){

						while(private_APPuint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
						local_uint8PassTemp[i]=private_APPuint8KeypadReading;
						LCD_voidWriteChar(private_APPuint8KeypadReading);
						BUZZER_voidOutputTune(70);

						private_APPuint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;

					}
					TIM2_voidSetBusyWaitSynch(1000);

					for(uint8 i=0;i<APP_PASS_CHARACTERS_NUMBER;i++){									// Comparing user input against the stored pass

						if(local_uint8PassTemp[i]!=EX_EEPROM_uint8ReadByte(APP_PASS_FIRST_CHAR_ADDRESS+i)){
							LCD_voidClearScreen();
							LCD_voidGoToLocation(2,1);
							LCD_voidWriteString("Password mismatch!");
							TIM2_voidSetBusyWaitSynch(1000);
							local_uint8PasswordConformity=APP_PASS_MISMATCH;
							break;
						}
						else{
							local_uint8PasswordConformity=APP_PASS_MATCH;
						}

					}
					LCD_voidClearScreen();
					local_uint8PassEntriesCount++;

				}while((local_uint8PasswordConformity==APP_PASS_MISMATCH)&&local_uint8PassEntriesCount<APP_PASS_ENTRIES_MAX_COUNT);

				local_uint8PassEntriesCount=0;
				if(local_uint8PasswordConformity==APP_PASS_MISMATCH){

					LCD_voidGoToLocation(2,4);
					LCD_voidWriteString("UNAUTHORIZED");
					LCD_voidGoToLocation(3,5);
					LCD_voidWriteString("ENTRANCE!");

					for(uint8 i=0;i<APP_SIREN_TIME;i++){

						DIO_voidSetPinValue(DIO_PIN_NO_5,DIO_PIN_HIGH);
						DIO_voidSetPinValue(DIO_PIN_NO_15,DIO_PIN_LOW);
						DIO_voidSetPinValue(DIO_PIN_NO_22,DIO_PIN_HIGH);
						TIM2_voidSetBusyWaitSynch(1000);
						DIO_voidSetPinValue(DIO_PIN_NO_5,DIO_PIN_LOW);				// toggling LED
						DIO_voidSetPinValue(DIO_PIN_NO_15,DIO_PIN_HIGH);
						DIO_voidSetPinValue(DIO_PIN_NO_22,DIO_PIN_LOW);				// toggling Buzzer
						TIM2_voidSetBusyWaitSynch(1000);

					}
				}
				else{

					LCD_voidGoToLocation(1,4);
					LCD_voidWriteString("Welcome Home");
					SRVM_voidOn(0);						// open the Door
					TIM2_voidSetBusyWaitSynch(5000);
					LCD_voidClearScreen();
					LCD_voidWriteString("Please, Press \'#\' to");
					LCD_voidGoToLocation(2,0);
					LCD_voidWriteString("close the door");
					while(private_APPuint8KeypadReading!='#'&&local_uint8DoorClosureCounter<APP_CLOSURE_TIMEOUT){
						TIM2_voidSetBusyWaitSynch(100);
						local_uint8DoorClosureCounter++;
					}
					if(private_APPuint8KeypadReading=='#'){
						BUZZER_voidOutputTune(70);
					}
					local_uint8DoorClosureCounter=0;
					SRVM_voidOn(45);
					LCD_voidClearScreen();
					LCD_voidGoToLocation(1,4);
					LCD_voidWriteString("Door closed");
					TIM2_voidSetBusyWaitSynch(1500);
				}


			}
			LCD_voidClearScreen();
		}
	}


}

void APP_voidSetKeypadReading(void){

	private_APPuint8KeypadReading=KEYPAD_uint8GetPressedKey();
}
