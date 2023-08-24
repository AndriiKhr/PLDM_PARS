#include "global.h"
#include "json.h"
#include "pars.h"


FILE *fptrL;
FILE *fptrJ;

char log_str[SIZE_STRING] = {};

int size_str = 0;
int flag_ena_write = 0;

pldm pldm_struct;


/* */
int main(void)
{
    #if ENABLE_DEBUG == 1
        printf("-- START PARSING --"); 
    #endif
    
    /* Open a LOG file in read mode */
    fptrL = fopen( IN_FILE_LOG, "r" );

    /* Check file */
    if( fptrL == NULL ) {
        printf("Not able to open the file --> %s", IN_FILE_LOG);
        return -1;
    }

    /* Open a JSON file in writing mode */
    fptrJ = fopen( OUT_FILE_JSON, "w" );

    /* Check file */
    if( fptrJ == NULL ) {
        printf("Not able to open the file --> %s", OUT_FILE_JSON);
        return -1;
    }

    /* Init struct for HEADER */
    init_all_mem(&pldm_struct);

    /* Read new string from log file */
    while ( fgets(log_str, SIZE_STRING, fptrL) != NULL ) 
    {
         size_str = strlen(log_str);
         log_str[size_str+1] = '\0';

         /* Pars new string */
         flag_ena_write = pars_new_str(log_str, size_str, &pldm_struct);
         memset(log_str, 0, size_str);

         /* Write new packet to JSON */
         switch ( flag_ena_write ) {
              case (0) : { write_header_data_json(fptrJ, &pldm_struct, 0); } break;
              case (1) : { write_header_data_json(fptrJ, &pldm_struct, 1); } break;
              case (2) : { write_packet_data_json(fptrJ, &pldm_struct, 0); } break;
              case (3) : { write_packet_data_json(fptrJ, &pldm_struct, 1); } break;
              default:break;
         }
    }

    /* Free all memory */
    free_all_mem(&pldm_struct);

    /* Close files */
    fclose(fptrL);
    fclose(fptrJ);

    #if ENABLE_DEBUG == 1
        printf("-- END PARSING --"); 
    #endif

    return 0;
}
