#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include "../headers/socket.h"

struct socket_s {
    SOCKET winsock;
};

static socket_t *
socket_new_winsock(SOCKET winsocket) {
    socket_t * self = malloc(sizeof(struct socket_s));
    self->winsock = winsocket;
    return self;
}

socket_t *
socket_new(void) {
    SOCKET winsock = socket(AF_INET, SOCK_STREAM, 0);
    // == INVALID_SOCKET; WSAGetLastError()
    socket_t * self = socket_new_winsock(winsock);
    return self;
}

void
socket_free(socket_t * self) {
    closesocket(self->winsock);
    free(self);
}

const char *
socket_getIPAddress(socket_t * self) {
    return "(null)";  // @todo
}

int
socket_getPortNumber(socket_t * self) {
    return -1;  // @todo
}

int
socket_bind(socket_t * self, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = bind(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo == SOCKET_ERROR
    return status;
}

int
socket_listen(socket_t * self) {
    listen(self->winsock, 10);  // @todo param
    return 0; // @todo ?
}

socket_t *
socket_accept(socket_t * self) {
    struct sockaddr_in clientaddr;
    int size = sizeof(struct sockaddr_in);
    SOCKET winsock = accept(self->winsock, (struct sockaddr *)&clientaddr, &size);
    if (INVALID_SOCKET == winsock) {
        return NULL;
    }
    socket_t * socket = socket_new_winsock(winsock);
    return socket;
}

int
socket_connect(socket_t * self, const char * ipaddress, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = inet_addr(ipaddress),
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = connect(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo if < 0
    return status;
}

int
socket_read(socket_t * self, char * recvBuff, int recvBuffSize) {
    int recvSize = recv(self->winsock, recvBuff, recvBuffSize, 0);
    // @todo == SOCKET_ERROR
    recvBuff[recvSize] = '\0';
    return recvSize;
}

int
socket_write(socket_t * self, const char * msg, int msgSize) {
    int status = send(self->winsock, msg, msgSize, 0);
    // @todo < 0
    return status;
}

int
socket_write_string(socket_t * self, const char * msg) {
    return socket_write(self, msg, strlen(msg));
}

void
socket_close(socket_t * self) {
    closesocket(self->winsock);
}

/* STATIC */

static WSADATA wsa;

void
lib_init(void) {
    int status = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (status == 1)
    {
        fprintf(stderr, "Cannot initialize dll - WSAStartup failed.");
        exit(1);
    }
}

void
lib_free(void) {
    WSACleanup();
}

SOCKET socket_create_v2()
{
    SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (recvSocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed.");
        WSACleanup();
        return (0);
    }
    return (recvSocket);
}

void socket_connect_v2(SOCKET recvSocket, SOCKADDR_IN recvSockAddr)
{
    if (connect(recvSocket, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Socket connection failed.");
        closesocket(recvSocket);
        WSACleanup();
    }
}

void socket_sendRequest_v2(const char * host_name, SOCKET recvSocket)
{
    char request[200];
    sprintf(request, "GET /var/4 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);
    send(recvSocket, request, strlen(request), 0);
}

void socket_sendPost_v2(    SOCKET recvSocket, char * host_name, char *avg)
{
    char result[30];
    char request[200];
    sprintf(result, "result=%s", avg);
    sprintf(request, "POST /var/4 HTTP/1.1\r\nHost: %s\r\nContent-length: %d\r\n\r\n%s\r\n", host_name, strlen(result), result);
    send(recvSocket, request, strlen(request), 0);
}

void socket_receiveInfo_v2(SOCKET recvSocket, char * maxBuff)
{
    int status;
    int numrcv = recv(recvSocket, maxBuff, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        fprintf(stderr, "Socket failed receiving info.");
        status = closesocket(recvSocket);
        if (status == SOCKET_ERROR)
        {
            fprintf(stderr, "Socket closing failed.");
        }
        status = WSACleanup();
        if (status == SOCKET_ERROR)
        {
            fprintf(stderr, "WSACleanup failed.");
        }
    }
}

int initDLL_v2(WSADATA Data)
{
    int status = WSAStartup(MAKEWORD(2, 2), &Data);
    if (status != 0)
    {
        printf("ERRIR IN WSASTARTUP\n");
        exit(1);
    }
    return (status);
}
