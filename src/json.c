#include "json.h"


void write_header_data_json(FILE *fptr, pldm *pldm_p, int enable_curl)
{
     fprintf(fptr, "{\n");
     fprintf(fptr, "  \"DIRECTION\":\"%s\"", pldm_p->header.dir ? "<--" : "-->");  
     fprintf(fptr, ",\n  \"MCTP DEST\":%s", pldm_p->header.mctp_dest_eid);       
     fprintf(fptr, ",\n  \"MCTP TYPE\":%s", pldm_p->header.mctp_mess_type);      
     fprintf(fptr, ",\n  \"PCIE ADDR\":%s", pldm_p->header.pcie_addr);       
      
     fprintf(fptr, ",\n  \"PACKET\":\n  [");
     fprintf(fptr, " %s", pldm_p->packet.pldm_packet);

     if( enable_curl == 1 ) {
         fprintf(fptr, "  ]");
         fprintf(fptr, "\n}\n");
     }
}


void write_packet_data_json(FILE *fptr, pldm *pldm_p, int enable_curl)
{
     fprintf(fptr, "    %s", pldm_p->packet.pldm_packet);

     if( enable_curl == 1 ) {
         fprintf(fptr, "  ]");
         fprintf(fptr, "\n}\n");
     }
}
