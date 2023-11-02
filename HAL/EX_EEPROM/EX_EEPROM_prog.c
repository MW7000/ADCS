/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 31 OCT 2023                       */
/*  SWC : EX_EEPROM                         */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EX_EEPROM_int.h"
#include "EX_EEPROM_priv.h"
#include "TWI_int.h"
#include <util/delay.h>

void EX_EEPROM_voidWriteByte(uint16 copy_uint16ByteAddress, sint8 copy_sint8ByteData){

	uint8 local_uint8AddressSegment = (copy_uint16ByteAddress>>8) | EX_EEPROM_FIXED_ADDRESS;

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendStartCondition());

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendSlaveAddressPlusW(local_uint8AddressSegment));

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendData(copy_uint16ByteAddress));

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendData(copy_sint8ByteData));

	TWI_voidMasterSendStopCondition();

	_delay_ms(10);
}


uint8 EX_EEPROM_uint8WritePageBytes(uint16 copy_uint16FirstByteAddress, uint8* copy_uint8ByteTrain, uint8 copy_uint8trainSize){

	uint8 local_uint8ErrorStatus = EX_EEPROM_OPERATION_SUCCESS;
	uint8 local_uint8FirstAddressMSBs = copy_uint16FirstByteAddress>>4;
	uint8 local_uint8MaxAddressMSBs = (copy_uint8trainSize+copy_uint16FirstByteAddress-1)>>4;

	if((local_uint8FirstAddressMSBs!=local_uint8MaxAddressMSBs)||copy_uint8trainSize>16||((copy_uint16FirstByteAddress+copy_uint8trainSize)>1024)){

		local_uint8ErrorStatus = EX_EEPROM_WRITE_ERROR;

	}
	else{

		uint8 local_uint8AddressSegment = (copy_uint16FirstByteAddress>>8) | EX_EEPROM_FIXED_ADDRESS;

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendStartCondition());

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendSlaveAddressPlusW(local_uint8AddressSegment));

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendData(copy_uint16FirstByteAddress));

		for(uint8 i=0;i<copy_uint8trainSize;i++){

			while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendData(copy_uint8ByteTrain[i]));

		}

		TWI_voidMasterSendStopCondition();

		_delay_ms(10);

	}
	return local_uint8ErrorStatus;
}



uint8 EX_EEPROM_uint8ReadByte(uint16 copy_uint16ByteAddress){

	uint8 local_uint8ByteToBeRead;

	uint8 local_uint8AddressSegment = (copy_uint16ByteAddress>>8) | EX_EEPROM_FIXED_ADDRESS;

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendStartCondition());

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendSlaveAddressPlusW(local_uint8AddressSegment));

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendData(copy_uint16ByteAddress));

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendRepeatedStartCondition());

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendSlaveAddressPlusR(local_uint8AddressSegment));

	while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterReceiveDataWithNACK(&local_uint8ByteToBeRead));

	TWI_voidMasterSendStopCondition();

	return local_uint8ByteToBeRead;

}


uint8 EX_EEPROM_uint8ReadMultipleBytes(uint16 copy_uint16ByteAddress, uint8* copy_puint8ReceiverDataTrain, uint16 copy_uint8BytesToReceiveNo){

	uint8 local_uint8ErrorStatus = EX_EEPROM_OPERATION_SUCCESS;

	if((copy_uint8BytesToReceiveNo+copy_uint16ByteAddress)<=EX_EEPROM_24C08_SIZE){

		uint8 local_uint8AddressSegment = (copy_uint16ByteAddress>>8) | EX_EEPROM_FIXED_ADDRESS;

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendStartCondition());

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendSlaveAddressPlusW(local_uint8AddressSegment));

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendData(copy_uint16ByteAddress));

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendRepeatedStartCondition());

		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterSendSlaveAddressPlusR(local_uint8AddressSegment));

		for(uint8 i=0;i<copy_uint8BytesToReceiveNo-1;i++){

			// reading bytes and sending ACK
			while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterReceiveDataWithACK(&copy_puint8ReceiverDataTrain[i]));

		}

		// reading the last byte and sending NACK
		while(TWI_OPERATION_SUCCESS!=TWI_uint8MasterReceiveDataWithNACK(&copy_puint8ReceiverDataTrain[copy_uint8BytesToReceiveNo-1]));

		TWI_voidMasterSendStopCondition();

	}
	else{

		local_uint8ErrorStatus = EX_EEPROM_READ_ERROR;
	}

	return local_uint8ErrorStatus;
}


