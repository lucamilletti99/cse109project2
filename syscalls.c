/*
 * File: syscalls.c
 * Name: Luca Milletti
 * UID:  lpm222
 */
#include "syscalls.h"
#include <stdio.h>       /* for fprintf */
#include <sys/socket.h>  /* PF_FILE, SOCK_STREAM */
#include <errno.h> 
#include <stdlib.h>
#include <sys/wait.h> 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
int Socket(int domain, int type, int protocol){
    int socketDescriptor = 0;
    if((socketDescriptor = socket(domain, type, protocol)) == -1){ //01 if failed socket created, descriptor returned if sucessful
        fprintf(stderr, "Socket error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return socketDescriptor; 
}
int Bind(int socket, const struct sockaddr *address, socklen_t address_len){
    if(bind(socket, address, address_len) == -1){ //-1 if failed bind, 0 if success
        fprintf(stderr, "Bind error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return 0; 
}
int Listen(int sockfd, int backlog){
    if(listen(sockfd, backlog) == -1){ //-1 if failed listen, 0 if success
        fprintf(stderr, "Listen error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return 0;
}
int Connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen){
    if(connect(sockfd, addr, addrlen) == -1){ //-1 if failed connection, 0 if success
        fprintf(stderr, "Connect error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return 0;
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int fileDescriptor = 0;
    if((fileDescriptor = accept(sockfd, addr, addrlen)) == -1){ /*-1 if failed connection acceptance, accepted socket
                                                                file descriptor returned if successful*/ 
        fprintf(stderr, "Socket Connection Acceptance error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return fileDescriptor;
}
ssize_t Recv(int sockfd, void *buf, size_t len, int flags){
    ssize_t msgLength = 0;
    if((msgLength = recv(sockfd, buf, len, flags)) == -1){ //-1 if failed connection, 0 if success
        fprintf(stderr, "Message Receive error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return msgLength;
}
ssize_t Send(int sockfd, const void *buf, size_t len, int flags){
    ssize_t msgLength = 0;
    if((msgLength = send(sockfd, buf, len, flags)) == -1){ //-1 if failed connection, 0 if success
        fprintf(stderr, "Message Sent error %d - %s\n", errno, strerror(errno));
        exit(errno);
    }
    return msgLength;;
}
int Socketpair(int domain, int type, int protocol, int socket_vector[2]){
  if(socketpair(domain, type, protocol, socket_vector) == -1){
    fprintf(stderr, "Socketpair error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return 0;
}
int Pipe(int pfd[2]) {
  int rc;
  if ((rc = pipe(pfd)) == -1) {
    fprintf(stderr, "Pipe error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return rc;  /* ok if student just returns 0 */
}
pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) == -1) {        /* for error msg */
    fprintf(stderr, "Fork error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return pid;
}
pid_t Wait(int *stat_loc){
  pid_t returnPid = 0;
  if((returnPid = wait(stat_loc)) == -1){
    fprintf(stderr, "wait error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return returnPid;
}
int Open(const char *charHolder, int randInt, mode_t mode){ //unnecessary because we use Socket to open a file 
    charHolder = charHolder, mode = mode; randInt = randInt;
    return 0;
}
int Close(int pfd) {
  int rc;
  if ((rc = close(pfd)) == -1) {       /* for error msg */
    fprintf(stderr, "Close error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return rc;  /* ok if students just returns 0 */
}
ssize_t Write(int pfd, const void *buffer, size_t nbytes) {
  ssize_t numBytes;
  if ((numBytes = write(pfd, buffer, nbytes)) == -1) {
    fprintf(stderr, "Write error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return numBytes;
}
ssize_t Read(int pfd, void *buffer, size_t nbytes) {
  ssize_t numBytes;
  if ((numBytes = read(pfd, buffer, nbytes)) == -1) {
    fprintf(stderr, "Read error %d - %s\n", errno, strerror(errno));
    exit(errno);
  }
  return numBytes;
}
FILE *Fopen(const char *path, const char *mode){ 
  FILE *fp = NULL;
  if((fp=fopen(path, mode)) != NULL) return fp; //error checks that fp is not Null
  else{ //if it is null, this file open error is printed to stderr
    fprintf(stderr," Unable to open %s with mode %s (%d) - %s\n", path,mode,errno, strerror(errno));
    exit(errno);
  }
}
void Fclose(FILE *fp){ 
  if(fclose(fp)!= 0){ //error checks to see if fclocse(fp) correctly closes File *fp
    fprintf(stderr,"File close error %d - %s\n",errno, strerror(errno));
    exit(errno); 
  }
}
int Fseek(FILE *lFile, long offset, int whence){
  if(fseek(lFile, offset, whence)!= 0){ //-1L is the value set if ftell isn't set correct
    fprintf(stderr,"Seek error %d - %s",errno, strerror(errno));
    exit(errno);
  }
	return Ftell(lFile);
}
long Ftell(FILE *lFile){    
	long filePosition = 0;
    if((filePosition = ftell(lFile))==-1L){ //-1L is the value set if ftell isn't set correct
        fprintf(stderr,"Tell error %d - %s\n",errno, strerror(errno));
        exit(errno);
    }
	return filePosition; //random return value until we use this function
}
size_t Fread(void *ptr, size_t numBytes, size_t numMembers, FILE *rFile){
	size_t numElementsRead = 0;
	if((numElementsRead = fread(ptr, numBytes, numMembers, rFile))!= 0){
		return numElementsRead;
	}
	else if((!feof(rFile) && ferror(rFile))){
		fprintf(stderr,"Read error %d - %s\n",errno, strerror(errno));
        exit(errno); 
	}
	return numElementsRead;
}
size_t Fwrite(const void *ptr, size_t numBytes, size_t numMembers, FILE *lFile){
	size_t numElementsWritten = 0;
	if((numElementsWritten = fwrite(ptr, numBytes, numMembers, lFile))!= 0){
		return numElementsWritten;
	}
	else if((!feof(lFile) && ferror(lFile))){
		fprintf(stderr,"Write error %d - %s\n",errno, strerror(errno));
        exit(errno);
	}
	return numElementsWritten;
}
void *Malloc(size_t numBytes){                                            
  void *ptr = NULL;                                                      
  if ((ptr = malloc(numBytes)) == NULL){//Steven's Style wrapper function                            
    fprintf(stderr,"Memory Allocation error %d - %s\n",errno, strerror(errno));
    exit(errno);                                                            
  }
  return ptr;
}
int Uname(struct utsname *buffer){
    if(uname(buffer) != 0){
        fprintf(stderr,"Uname error %d - %s\n",errno, strerror(errno));
        exit(errno); 
    }
    return 0;
}
int Unlink(const char *path){                                                   
  if (unlink(path)==-1){//Steven's Style wrapper function                            
    fprintf(stderr,"Unlinking error %d - %s\n",errno, strerror(errno));
    exit(errno);                                                            
  }
  return 0;
}
