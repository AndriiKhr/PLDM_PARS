#include "pars.h"


/* Local function for read all ":" in the string */
static int read_dots(const char *str)
{
    int counter = 0;

    while( *str != '\0' ) {
        if( *str++ == ':' )
             counter++;
    }

    return counter;
}


/* Local function for read START of packet */
static int read_dir_symbol(const char *str)
{
    int ret = -1;
    char dir[SIZE_DIR+1] = {};
 
    strncpy(dir, str, SIZE_DIR);
    dir[SIZE_DIR] = '\0';

    if ( strcmp(dir, "-->") == 0 )
         ret = FROM_CONTROLLER;
       
    else if (strcmp(dir, "<--") == 0)
         ret = TO_CONTROLLER;   

    return ret;
}


/* Local function for write packet to main struct */
static void write_data_packet(char *ptrData, pldm *pldm_main, type_packet tp, int size)
{
     memset(pldm_main->packet.pldm_packet, '\0', SIZE_PACKET);
     strncpy(pldm_main->packet.pldm_packet, ptrData, size); 
     pldm_main->packet.size = 1;
}


/* Local function for write header to main struct */
static void write_data_header(char *pch, type_packet_header type_data, int size, pldm *pldm_main)
{
    switch( type_data )
    {
        case( MCTP_DEST_EID ):
        {
            memset(pldm_main->header.mctp_dest_eid, '\0', SIZE_FIELDS_HEADER);
            strncpy(pldm_main->header.mctp_dest_eid, pch, size); 
        }
        break;
        case( MCTP_MESS_TYPE ):
        {
            memset(pldm_main->header.mctp_mess_type, '\0', SIZE_FIELDS_HEADER);
            strncpy(pldm_main->header.mctp_mess_type, pch, size); 
        }
        break;
        case( PCIE_ADDR ):
        {
            memset(pldm_main->header.pcie_addr, '\0', SIZE_FIELDS_HEADER);
            strncpy(pldm_main->header.pcie_addr, pch, size);
        }
        break;
        default: break;
    }
}

/* Local function for parsing HEADER */
static void pars_header(const char *str, pldm *pldm_main)
{
    char sep[3] = " :";
    char dest[SIZE_FIELDS_HEADER] = {};
    char *ptrC = NULL;
    char *newPTR = NULL;
    int size = strlen(str);

    ptrC = (char *)malloc(size);

    if( ptrC ) 
    { 
        memset(ptrC, '\0', size); 
        strncpy(ptrC, str, size);

        for( int t=0; t<3; t++ )
        {
             memset(dest, '\0', sizeof(dest)); 

             newPTR = strchr(ptrC, '[');
             strncpy(dest, (newPTR + 8*t), SIZE_FIELDS_HEADER);
             dest[SIZE_FIELDS_HEADER] = '\0';

             #if ENABLE_DEBUG == 1
                printf("%s \n", dest);
             #endif

             write_data_header(dest, t, SIZE_FIELDS_HEADER, pldm_main);
        }
    }

    free(ptrC);
}


/* Function for parsing */
int pars_new_str(char *str, int size, pldm *pldm_main)
{
    static int enable_write_long_packet = 0; 
    int ret = -1;
    int dir = 0;
    int size_packet = 0;
    char *ptrD = NULL;
    char *newPTR = NULL;

    char dest[SIZE_FIELDS_HEADER] = {};

    /* String is empty or not */
    if( size > SIZE_DIR )
    {
        #if ENABLE_DEBUG == 1
            printf("size = %d, NEW STRING = %s", size, str); 
        #endif
        
        /* Check first sumbol of string */
        dir = read_dir_symbol(str);
        if ( dir > 0 ) 
        {
              /* Read type of packet */
              enable_write_long_packet = read_dots(str);

              /* Write direction to struct */
              pldm_main->header.dir = dir; 

              /* Pars HEADER */
              pars_header(str+SIZE_DIR, pldm_main);

              /* Pars PACKET of DATA */
              if( enable_write_long_packet == COUNTER_SHORT_DOT ) {
                  
                  newPTR = strrchr(str, ':');
              
                  if( newPTR )  {
                      ptrD = (char *)malloc(strlen(newPTR)); 
                      if( ptrD ) {
                         memset(ptrD, '\0', strlen(newPTR)); 
                         strncpy(ptrD, newPTR+2, strlen(newPTR));
                         write_data_packet(ptrD, pldm_main, SHORT_PACKET, strlen(newPTR));
                     }
                  }

                  ret = 1;
              }
              else {
                  ret = 0;
              }

              free(ptrD);
        } 
        else 
        {
              if( enable_write_long_packet == COUNTER_LONG_DOT ) {
                  size_packet = size;
                  write_data_packet(str, pldm_main, LONG_PACKET, size_packet);
                  ret = 2;
              }
        }
    }
    else
    {
        if( enable_write_long_packet == COUNTER_SHORT_DOT ) { ret = 1; } 
        else if( enable_write_long_packet == COUNTER_LONG_DOT ) { ret = 3; }
    }

    return ret;
}


/* */
void init_all_mem(pldm *pldm_main)
{
    pldm_main->header.mctp_dest_eid = (char *)malloc(SIZE_FIELDS_HEADER);
    pldm_main->header.mctp_mess_type = (char *)malloc(SIZE_FIELDS_HEADER);
    pldm_main->header.pcie_addr = (char *)malloc(SIZE_FIELDS_HEADER);

    pldm_main->packet.pldm_packet = (char *)malloc(SIZE_PACKET);
}


/* */
void free_all_mem(pldm *pldm_main)
{
    free(pldm_main->header.mctp_dest_eid);
    free(pldm_main->header.mctp_mess_type);
    free(pldm_main->header.pcie_addr);

    free(pldm_main->packet.pldm_packet);
}
