/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 31 OCT 2023                       */
/*  SWC : EX_EEPROM                         */
/********************************************/


#ifndef  EX_EEPROM_INT_H
#define  EX_EEPROM_INT_H



void EX_EEPROM_voidWriteByte(uint16 copy_uint16ByteAddress, sint8 copy_sint8ByteData);

// copy_uint8trainSize param is limited to 16
uint8 EX_EEPROM_uint8WritePageBytes(uint16 copy_uint16FirstByteAddress, uint8* copy_uint8ByteTrain, uint8 copy_uint8trainSize);

uint8 EX_EEPROM_uint8ReadByte(uint16 copy_uint16ByteAddress);	// read only one byte not multiple sequential ones

// copy_uint8BytesToReceiveNo param is limited to the EEPROM size
uint8 EX_EEPROM_uint8ReadMultipleBytes(uint16 copy_uint16ByteAddress, uint8* copy_puint8ReceiverDataTrain, uint16 copy_uint8BytesToReceiveNo);



#define		EX_EEPROM_WRITE_ERROR			7
#define		EX_EEPROM_OPERATION_SUCCESS		9



#endif
