/*
 * File: prog3_server.c
 * Name: Luca Milletti
 * UID:  lpm222
 */
#include "globaldefs.h"
#include "prog3_funcs.h"
#include "syscalls.h"
#include <sys/utsname.h> //utsname 
#include <sys/un.h> //unix domain socket
#include <stdbool.h>
#include <stdlib.h> //free

int main(int argc, char *argv[]){
    struct utsname uBuffer;
    struct sockaddr_un servAddress;
    char introMessage [512]; char goodbye[11] = "Good Bye!"; char message[BUFFER_SIZE];// all messages
    ssize_t msgSize = 0; //num of bytes sent or received
    char *sock_path = (char *)Malloc(sizeof(char *)); //socket name to set sockaddr path
    bool communication_check = true; bool server_check = true; //for infinite while loop of server
    parseArgs(argc, argv, sock_path); //set sock_name in parseargs 
    int server_fd = Socket(DOMAIN, TYPE, PROTOCOL);
        printf("Creating initial/unbound socket...\n");   
    Unlink(sock_path); //unlinks socket address to allow binding of new socket
    servAddress.sun_family = DOMAIN; //sets path domain of sock address
    strcpy(servAddress.sun_path,sock_path); //sets path name of sock address
    int servLength = sizeof(servAddress);
    Bind(server_fd, (struct sockaddr *)&servAddress, servLength);
        printf("Binding initial/unbound socket to local socket address ...\n");
    Listen(server_fd, BACKLOG);
        printf("Marking initial/unbound socket as accepting connections...\n");
    do{ //infinite loop
        printf("Extracting (or waiting to extract) connection on queue of pending connections...\n");
        int client_fd = Accept(server_fd, (struct sockaddr *)&servAddress, (socklen_t *)&servLength);
        Uname(&uBuffer);
        pid_t pid = getpid();
        sprintf(introMessage,"Welcome to server %s (process %d) running %s release %s on %s platform" //print hello message
                                    ,uBuffer.nodename, (int)pid, uBuffer.sysname,uBuffer.release,uBuffer.machine);
        printf("Connected to client, sending welcome message...\n");
        Send(client_fd, introMessage, strlen(introMessage),FLAGS); //send initial connection message
        while(communication_check){ //loop until conneciton b/w server and client is broken
            memset(message, '\0', sizeof(message));//reset all bytes of message to zero to allow recvMessage to be used again
            msgSize = Recv(client_fd, message, BUFFER_SIZE,FLAGS);
            if(strcmp(message,"Later!")==0){
                printf("Received message (%ld bytes): '%s'\n", msgSize, message); //print goodbye message and leave
                break; //client message was empty or was cntl+d
            }
            else printf("Received message (%ld bytes): '%s'", msgSize, message); //if read works , read message;
            if(queryMsg(message) == -1){ //ctrl + d is entered (returned from getline
                Send(client_fd, goodbye, strlen(goodbye),FLAGS);
                communication_check = false;
                printf("\n"); //formatting 
                Close(client_fd);
                break;
            }
            if(strlen(message) <= 140){
                msgSize = strlen(message)-1;
                Send(client_fd, message, msgSize,FLAGS); //strlen -1 removes unncessary null terminators 
                printf("Sent Message (%ld bytes); waiting for reply...",msgSize);
                printf("\n"); /*don't know why this is necessary but it was the only that that allowed me to get the print statement correctly printing at the correct time*/
            } 
            else{ //entered message is greater than 140
                printf("Truncating message to 140 characters.\n");
                Send(client_fd, message, BUFFER_SIZE,FLAGS); //strlen -1 removes unncessary null terminators 
                printf("Sent Message (%d bytes); waiting for reply...",BUFFER_SIZE);
                printf("\n"); /*don't know why this is necessary but it was the only that that allowed me to get the print statement correctly 
                            printing at the correct time*/
                msgSize = strlen(message); 
            }
        }
        Close(client_fd);
    }while(server_check);
    Unlink(sock_path);
    if (sock_path) free(sock_path);
    return 0;
}