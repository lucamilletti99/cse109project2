/*
 * File: syscalls.h
 * Name: Mark Erle
 * UID:  mae5
 */

#ifndef SYSCALLS
#define SYSCALLS

#include <sys/utsname.h>   /* for utsname */
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>

int Socket(int, int, int); 
int Bind(int, const struct sockaddr *, socklen_t);
int Listen(int, int);
int Connect(int, const struct sockaddr *, socklen_t);
int Accept(int, struct sockaddr *, socklen_t *);
ssize_t Recv(int, void *, size_t, int);
ssize_t Send(int, const void *, size_t, int);
int Socketpair(int, int, int, int []);
int Pipe(int []);
pid_t Fork(void);
pid_t Wait(int *);
int Open(const char *, int, mode_t);
int Close(int);
ssize_t Write(int, const void *, size_t);
ssize_t Read(int, void *, size_t);
FILE *Fopen(const char *, const char *);
void Fclose(FILE *);
int Fseek(FILE *, long, int);
long Ftell(FILE *);
size_t Fread(void *, size_t, size_t, FILE *);
size_t Fwrite(const void *, size_t, size_t, FILE *);
void *Malloc(size_t);
int Uname(struct utsname *);
int Unlink(const char *);
#endif
