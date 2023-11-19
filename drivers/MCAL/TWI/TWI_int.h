/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 1 NOV 2023                        */
/*  SWC : TWI                               */
/********************************************/



#ifndef		TWI_INT_H
#define		TWI_INT_H

// used only when node is set as a master

void   TWI_voidInit(void);

// master functions
uint8  TWI_uint8MasterSendStartCondition(void);

uint8  TWI_uint8MasterSendSlaveAddressPlusW(uint8 copy_uint8SlaveAddress);

uint8  TWI_uint8MasterSendData(uint8 copy_uint8Data);

void   TWI_voidMasterSendStopCondition(void);

uint8  TWI_uint8MasterSendRepeatedStartCondition(void);

uint8  TWI_uint8MasterSendSlaveAddressPlusR(uint8 copy_uint8SlaveAddress);

uint8  TWI_uint8MasterReceiveDataWithNACK(uint8* copy_puint8ReceivedData);

uint8  TWI_uint8MasterReceiveDataWithACK(uint8* copy_puint8ReceivedData);



uint8  TWI_uint8MasterTransmitSynch(uint8 copy_uint8SlaveAddress, uint8 copy_uint8Data);

uint8  TWI_uint8MasterReceiveSynch(uint8 copy_uint8SlaveAddress, uint8* copy_puint8Data);


#define		TWI_COMMUNICATION_SUCCESS		2

#define		TWI_OPERATION_SUCCESS			5
#define 	TWI_TIMEOUT_ERROR				7
#define 	TWI_STA_CON_ERROR				9
#define 	TWI_SLA_W_ERROR					11
#define 	TWI_SLA_R_ERROR					13
#define 	TWI_DATA_W_ERROR				15
#define 	TWI_DATA_R_ERROR				17
#define 	TWI_REP_STA_CON_ERROR			19




// used only when node is set as a slave

uint8  TWI_uint8SlaveTransmitSynch(uint8 copy_uint8Data);

// supports ability to respond to general calls

uint8  TWI_uint8SlaveReceiveSynch(uint8* copy_uint8Data);

uint8  TWI_uint8SlaveTransmitAsynch(uint8 copy_uint8Data);

uint8  TWI_uint8SlaveReceiveAsynch(uint8* copy_uint8Data);

#define		TWI_SPECIFIC_COMMUNICATION_SUCCESS 	4
#define		TWI_GENERAL_COMMUNICATION_SUCCESS	6


#endif
