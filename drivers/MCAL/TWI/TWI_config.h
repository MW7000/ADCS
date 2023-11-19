/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 1 NOV 2023                        */
/*  SWC : TWI                               */
/********************************************/


#ifndef		TWI_CONFIG_H
#define		TWI_CONFIG_H


#define		CPU_FREQ_IN_KHZ  	16000


/*
 * Options:
 * 		TWI_MASTER_NODE
 * 		TWI_SLAVE_NODE
 */


#define 	TWI_NODE_TYPE		TWI_MASTER_NODE

/*
 * Options:
 * 		Range from 1 to 119
 * 		120 : 127 and 0 are reserved
 */

#define		TWI_NODE_ADDRESS		3


/*
 * Options:
 * 		TWI_GC_ENABLED
 * 		TWI_GC_DISABLED
 */


#define 	TWI_GENERAL_CALL_RECOGNITION		TWI_GC_DISABLED


/* Options:
 * 		TWI_SPEED_400KH
 *		TWI_SPEED_300KH
 *		TWI_SPEED_200KH
 *		TWI_SPEED_100KH
 */

#define 	TWI_COMMUNICATION_SPEED			TWI_SPEED_100KHZ


#endif
