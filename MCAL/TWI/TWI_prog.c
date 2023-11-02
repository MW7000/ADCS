/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 1 NOV 2023                        */
/*  SWC : TWI                               */
/********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_int.h"
#include "TWI_config.h"
#include "TWI_priv.h"
#include "TWI_reg.h"



void TWI_voidInit(void){

	
#if TWI_NODE_TYPE==TWI_MASTER_NODE

	// with TWPS cleared as it's their initial value
	TWBR = (((uint32)CPU_FREQ_IN_KHZ/TWI_COMMUNICATION_SPEED)-16)/2;

#endif

	TWAR = TWI_NODE_ADDRESS<<1 | TWI_GENERAL_CALL_RECOGNITION;

//	SET_BIT(TWCR, TWCR_TWEA);			// Enabling ACK
	SET_BIT(TWCR, TWCR_TWEN);

}


#if 	TWI_NODE_TYPE == TWI_MASTER_NODE

uint8  TWI_uint8MasterSendStartCondition(void){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWCR = TWI_START_CONDITION;

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			break;
		}
	}

	if(TWI_START_CONDITION_TRANSMITTED!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){
		local_uint8ErrorStatus = TWSR & TWI_TWSR_MASK;
	}

	return local_uint8ErrorStatus;
}






uint8  TWI_uint8MasterSendSlaveAddressPlusW(uint8 copy_uint8SlaveAddress){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWDR = copy_uint8SlaveAddress << 1 | TWI_WRITE_OPERATION;

	TWCR = TWI_MASTER_TRANSMIT;		// clearing START CONDITION and INT bits

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			break;
		}
	}


	if(TWI_SLA_W_TRANSMITTED_ACK_RECEIVED!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){

		local_uint8ErrorStatus = TWI_SLA_W_ERROR;

	}

	return local_uint8ErrorStatus;
}




uint8  TWI_uint8MasterSendSlaveAddressPlusR(uint8 copy_uint8SlaveAddress){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWDR = copy_uint8SlaveAddress<<1 | TWI_READ_OPERATION;

	TWCR = TWI_MASTER_TRANSMIT;		// clearing START CONDITION and INT bits

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			break;
		}
	}

	if(TWI_SLA_R_TRANSMITTED_ACK_RECEIVED!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){

		local_uint8ErrorStatus = TWI_SLA_R_ERROR;
	}

	return local_uint8ErrorStatus;
}


uint8  TWI_uint8MasterSendData(uint8 copy_uint8Data){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWDR = copy_uint8Data;
	TWCR = TWI_MASTER_TRANSMIT;

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			break;
		}
	}

	if(TWI_DATA_TRANSMITTED_ACK_RECEIVED_AS_MASTER!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){

		local_uint8ErrorStatus = TWI_DATA_W_ERROR;
	}

	return local_uint8ErrorStatus;
}



uint8  TWI_uint8MasterReceiveDataWithNACK(uint8* copy_puint8ReceivedData){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWCR = TWI_MASTER_TRANSMIT;

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			return local_uint8ErrorStatus;
		}
	}

	if(TWI_DATA_RECEIVED_WITH_NACK_RETURNED!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){

		local_uint8ErrorStatus = TWI_DATA_R_ERROR;

	}

	*copy_puint8ReceivedData=TWDR;

	return local_uint8ErrorStatus;

}

uint8  TWI_uint8MasterReceiveDataWithACK(uint8* copy_puint8ReceivedData){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWCR = TWI_MASTER_TRANSMIT_WITH_ACK;

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			return local_uint8ErrorStatus;
		}
	}

	if(TWI_DATA_RECEIVED_WITH_ACK_RETURNED!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){

		local_uint8ErrorStatus = TWI_DATA_R_ERROR;

	}

	*copy_puint8ReceivedData=TWDR;

	return local_uint8ErrorStatus;

}


void   TWI_voidMasterSendStopCondition(void){

	TWCR = TWI_STOP_CONDITION;
}



uint8  TWI_uint8MasterSendRepeatedStartCondition(void){

	uint8 local_uint8ErrorStatus=TWI_OPERATION_SUCCESS;
	uint16 local_uint16Counter=0;

	TWCR = TWI_START_CONDITION;

	while(GET_BIT(TWCR , TWCR_TWINT)==0){
		local_uint16Counter++;
		if(local_uint16Counter==TWI_COUNTER_TIMEOUT){
			local_uint8ErrorStatus = TWI_TIMEOUT_ERROR;
			break;
		}
	}


	if(TWI_REPEATED_START_CONDITION_TRANSMITTED!=(TWSR & TWI_TWSR_MASK)&&(local_uint8ErrorStatus==TWI_OPERATION_SUCCESS)){

		local_uint8ErrorStatus = TWI_REP_STA_CON_ERROR;

	}

	return local_uint8ErrorStatus;
}




uint8  TWI_uint8MasterTransmitSynch(uint8 copy_uint8SlaveAddress, uint8 copy_uint8Data){

	uint8 local_uint8ErrorStatus;

	if(TWI_uint8MasterSendStartCondition()!=TWI_OPERATION_SUCCESS){

		SET_BIT(TWCR,TWCR_TWINT);				// leaving bus
		local_uint8ErrorStatus = TWI_STA_CON_ERROR;
	}
	else{
		if(TWI_uint8MasterSendSlaveAddressPlusW(copy_uint8SlaveAddress)!=TWI_OPERATION_SUCCESS){		// SLA+W

			local_uint8ErrorStatus = TWI_SLA_W_ERROR;
			SET_BIT(TWCR,TWCR_TWINT);				// leaving bus

		}
		else{

			if(TWI_uint8MasterSendData(copy_uint8Data)!=TWI_OPERATION_SUCCESS){

				local_uint8ErrorStatus = TWI_DATA_W_ERROR;
				SET_BIT(TWCR,TWCR_TWINT);				// leaving bus

			}
			else{

				TWI_voidMasterSendStopCondition();
				local_uint8ErrorStatus = TWI_COMMUNICATION_SUCCESS;
			}

		}

	}

	return local_uint8ErrorStatus;
}

uint8  TWI_uint8MasterReceiveSynch(uint8 copy_uint8SlaveAddress, uint8* copy_puint8Data){

	uint8 local_uint8ErrorStatus;


	if(TWI_uint8MasterSendStartCondition()!=TWI_OPERATION_SUCCESS){

		SET_BIT(TWCR,TWCR_TWINT);				// leaving bus
		local_uint8ErrorStatus = TWI_STA_CON_ERROR;
	}
	else{

		if(TWI_uint8MasterSendSlaveAddressPlusR(copy_uint8SlaveAddress)!=TWI_OPERATION_SUCCESS){			// SLA+R

			local_uint8ErrorStatus = TWI_SLA_R_ERROR;
			SET_BIT(TWCR,TWCR_TWINT);				// leaving bus

		}
		else{

			if(TWI_OPERATION_SUCCESS==TWI_uint8MasterReceiveDataWithNACK(copy_puint8Data)){

				TWI_voidMasterSendStopCondition();
				local_uint8ErrorStatus = TWI_COMMUNICATION_SUCCESS;
			}
			else{

				local_uint8ErrorStatus = TWI_DATA_R_ERROR;
				SET_BIT(TWCR,TWCR_TWINT);				// leaving bus

			}

		}

	}

	return local_uint8ErrorStatus;

}




#elif	TWI_NODE_TYPE == TWI_SLAVE_NODE

uint8  TWI_uint8SlaveTransmitSynch(uint8 copy_uint8Data){

	uint8 local_uint8ErrorStatus;

	TWCR = TWI_SLAVE_RECEIVE;		// setting acknowledge and TWEN bits

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if((TWSR&TWI_TWSR_MASK)==TWI_SLA_R_RECEIVED_ACK_RETURNED){

		TWDR = copy_uint8Data;
		SET_BIT(TWCR,TWCR_TWINT);

		while(GET_BIT(TWCR,TWCR_TWINT)==0);			// waiting for the master response

		if((TWSR&TWI_TWSR_MASK)==TWI_DATA_TRANSMITTED_NACK_RECEIVED_AS_SLAVE){

			CLEAR_BIT(TWCR,TWCR_TWEA);		// disable Ack
			SET_BIT(TWCR,TWCR_TWINT);
			local_uint8ErrorStatus = TWI_COMMUNICATION_SUCCESS;
		}else
		{
			CLEAR_BIT(TWCR,TWCR_TWEA);		// disable Ack
			SET_BIT(TWCR,TWCR_TWINT);		// until now, we will transmit only one byte
		}

	}
	else{
		local_uint8ErrorStatus = TWSR&TWI_TWSR_MASK;
		SET_BIT(TWCR,TWCR_TWINT);

	}

	return local_uint8ErrorStatus;

}

uint8  TWI_uint8SlaveReceiveSynch(uint8* copy_uint8Data){

	uint8 local_uint8ErrorStatus;

	TWCR = TWI_SLAVE_RECEIVE;		// setting acknowledge and TWEN bits

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if((TWSR&TWI_TWSR_MASK)==TWI_SLA_W_RECEIVED_WITH_ACK_RETURNED||(TWSR&TWI_TWSR_MASK)==TWI_GENERAL_CALL_RECEIVED_ACK_RETURNED){

		SET_BIT(TWCR,TWCR_TWINT);

		while(GET_BIT(TWCR,TWCR_TWINT)==0);			// waiting for the data to be received

		if((TWSR&TWI_TWSR_MASK)==TWI_SLA_W_RECEIVED_DATA_RECEIVED_ACK_RETURNED){

			*copy_uint8Data = TWDR;

			SET_BIT(TWCR,TWCR_TWINT);

			while(GET_BIT(TWCR,TWCR_TWINT)==0);

			if((TWSR&TWI_TWSR_MASK)==TWI_STOP_OR_REPEATED_START_CONDITION_RECEIVED){

				SET_BIT(TWCR,TWCR_TWINT);
				local_uint8ErrorStatus = TWI_SPECIFIC_COMMUNICATION_SUCCESS;		// to indicate whether the communication is a specific addressing or general call

			}else{
				local_uint8ErrorStatus = TWSR&TWI_TWSR_MASK;
				SET_BIT(TWCR,TWCR_TWINT);
			}

		}
		else if((TWSR&TWI_TWSR_MASK)==TWI_GENERAL_CALL_RECEIVED_DATA_RECEIVED_ACK_RETURNED){

			*copy_uint8Data = TWDR;

			SET_BIT(TWCR,TWCR_TWINT);

			while(GET_BIT(TWCR,TWCR_TWINT)==0);

			if((TWSR&TWI_TWSR_MASK)==TWI_STOP_OR_REPEATED_START_CONDITION_RECEIVED){

				SET_BIT(TWCR,TWCR_TWINT);
				local_uint8ErrorStatus = TWI_GENERAL_COMMUNICATION_SUCCESS;		// to indicate whether the communication is a specific addressing or general call

			}else{
				local_uint8ErrorStatus = TWSR&TWI_TWSR_MASK;
				SET_BIT(TWCR,TWCR_TWINT);
			}

		}
		else{

			local_uint8ErrorStatus = TWSR&TWI_TWSR_MASK;
			SET_BIT(TWCR,TWCR_TWINT);		// leaving communication
		}

	}
	else{

		local_uint8ErrorStatus = TWSR&TWI_TWSR_MASK;
		SET_BIT(TWCR,TWCR_TWINT);		// leaving communication

	}
	return local_uint8ErrorStatus;

}

uint8  TWI_uint8SlaveTransmitAsynch(uint8 copy_uint8Data){

	uint8 local_uint8ErrorStatus;

	return local_uint8ErrorStatus;
}

uint8  TWI_uint8SlaveReceiveAsynch(uint8* copy_uint8Data){

	uint8 local_uint8ErrorStatus;

	return local_uint8ErrorStatus;
}

#endif


void __vector_19(void)	__attribute__((signal));

void __vector_19(void){


}


