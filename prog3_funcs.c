/*
 * File: prog3_funcs.c
 * Name: Luca Milletti
 * UID:  lpm222
 */
#include "prog3_funcs.h"
#include "globaldefs.h"
#include <stdlib.h> //exit
#include <stdio.h>
#include <string.h> //for strcpy

void parseArgs(int argc, char *argv[], char *sockName){ /* call help or set optional socket file name and optional path */
    switch(argc){
        case(1): //no socket file name specified
            strcpy(sockName,SOCK_PATH);
            break;
        case(2): //socket file name specified
            strcpy(sockName, argv[1]);
            break;
        default:
            help();
            exit(0);
    }
}
int queryMsg(char *input){             /* query user for message to send or disconnect */
    char *msgBuffer;
    size_t buffer_size = 0;
    int msgSize = 0;
    printf("\nEnter non-empty message to send or Cntl+D to send a parting message: ");
    msgSize = getline(&msgBuffer, &buffer_size, stdin); //reads in more that buffer size so that the print message for greater 
                                                            //than 140 characters entered can be printed
    strcpy(input,msgBuffer);
    if(msgSize == -1){
        return -1;
    }
    return msgSize - 1;
}
void help(void){                         /* print help message */
    fprintf(stdout, "\n\tUsage: prog3_server [socketFilename]\n");
    fprintf(stdout, "\tprog3_client [socketFilename]\n\n");
    fprintf(stdout, "\tprog3_server creates a socket file named \"socketoomee\" (or argument passed on command\n");
    fprintf(stdout, "\tline) and waits for a client to connect. Once connected, users can communicate via the socket.\n\n");
    fprintf(stdout, "\tprog3_client requests a connection to prog3_server using \"socketoomee\" (or passed argument).\n");
    fprintf(stdout, "\tOnce connected, users can communicate via the socket.\n\n");
    fprintf(stdout, "\tMaximum length of socketFilename (including optional path) is 108 characters.\n\n");
}