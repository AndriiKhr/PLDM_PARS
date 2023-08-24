#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define   ENABLE_DEBUG    ( 0 )
#define   SIZE_STRING     ( 100 )

#define   IN_FILE_LOG     "../in_out/mclog.log"
#define   OUT_FILE_JSON   "../in_out/mcout.json"


typedef enum {
    FROM_CONTROLLER = 1,
    TO_CONTROLLER
} direction;


typedef struct {
    direction dir;
    char *pcie_addr;
    char *mctp_dest_eid;
    char *mctp_mess_type;
} header_pldm;


typedef struct {
    char *pldm_packet;
    int size;
} packet_pldm;


typedef struct {
    header_pldm header;
    packet_pldm packet;
} pldm;


#endif
