#ifndef _JSON_H_
#define _JSON_H_

#include "global.h"

void write_header_data_json(FILE *fptr, pldm *pldm_p, int enable_curl);
void write_packet_data_json(FILE *fptr, pldm *pldm_p, int enable_curl);

#endif
