#ifndef _PARS_H_
#define _PARS_H_

#include "global.h"

#define  SIZE_DIR               ( 3 )
#define  SIZE_FIELDS_HEADER     ( 7 )
#define  SIZE_HEADER            ( 27 )
#define  SIZE_PACKET            ( 100 )
#define  COUNTER_SHORT_DOT      ( 4 )
#define  COUNTER_LONG_DOT       ( 3 )


typedef enum 
{
    SHORT_PACKET = 0,
    LONG_PACKET
}type_packet;


typedef enum{
    MCTP_DEST_EID = 0,
    MCTP_MESS_TYPE,
    PCIE_ADDR
}type_packet_header;


int pars_new_str(char *str, int size, pldm *pldm_main);
void init_all_mem(pldm *pldm_main);
void free_all_mem(pldm *pldm_main);

#endif
