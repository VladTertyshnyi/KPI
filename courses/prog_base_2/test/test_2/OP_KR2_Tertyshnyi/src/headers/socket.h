#pragma once

#include <windows.h>
#include <WinSock2.h>

#define MAXBUFLEN 20480
#define PORT 80
#define NO_FLAGS_SET 0

typedef struct socket_s socket_t;

void lib_init(void);
void lib_free(void);

socket_t * socket_new(void);
void socket_free(socket_t * self);

const char * socket_getIPAddress(socket_t * self);
int socket_getPortNumber(socket_t * self);

int socket_bind(socket_t * socket, int portNumber);
int socket_listen(socket_t * socket);
socket_t * socket_accept(socket_t * socket);
int socket_connect(socket_t * sock, const char * ipaddress, int portNumber);
int socket_read(socket_t * sock, char * recvBuff, int recvSize);
int socket_write(socket_t * conn, const char * msg, int msgSize);
int socket_write_string(socket_t * conn, const char * msg);
void socket_close(socket_t * conn);

int initDLL_v2(WSADATA Data);
SOCKET socket_create_v2();
void socket_connect_v2(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void socket_sendRequest_v2(const char * host_name, SOCKET recvSocket);
void socket_receiveInfo_v2(SOCKET recvSocket, char * maxBuff);
void socket_sendPost_v2(SOCKET recvSocket, char * host_name, char *avg);
