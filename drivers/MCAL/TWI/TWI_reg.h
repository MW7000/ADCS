/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 1 NOV 2023                        */
/*  SWC : TWI                               */
/********************************************/


#ifndef		TWI_REG_H
#define		TWI_REG_H


#define		TWCR		*((volatile uint8*) 0x56 )
#define		TWCR_TWIE		0
#define		TWCR_TWEN   	2
#define		TWCR_TWWC   	3
#define		TWCR_TWSTO  	4
#define		TWCR_TWSTA  	5
#define		TWCR_TWEA   	6
#define		TWCR_TWINT  	7


#define		TWDR		*((volatile uint8*) 0x23 )


#define		TWAR		*((volatile uint8*) 0x22 )
#define		TWAR_TWGCE		0


#define		TWSR		*((volatile uint8*) 0x21 )
#define		TWSR_TWPS0      0
#define		TWSR_TWPS1      1
#define		TWSR_TWS3       3
#define		TWSR_TWS4       4
#define		TWSR_TWS5       5
#define		TWSR_TWS6       6
#define		TWSR_TWS7       7


#define		TWBR		*((volatile uint8*) 0x20 )



#endif
