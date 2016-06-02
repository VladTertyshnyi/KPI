#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> //  ptrdiff_t
#include <ctype.h>
#include "socket.h"
#include "teacher.h"
#include "cJSON.h"

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
} http_request_t;

http_request_t http_request_parse(const char * const request);

void server_send(socket_t * clientSocket, char * text) ;
void server_count(socket_t * clientSocket, list_t * TeacherList);
char * teacher_toJSON(teacher_t  self);
void server_GET_all(http_request_t req, socket_t * clientSocket,list_t * teacherList);

void server_DELETE_all(http_request_t req,socket_t * clientSocket,list_t* teacherList);
void server_GET_id(http_request_t req, socket_t * clientSocket, list_t * teacherList);
void server_DELETE_id(http_request_t req,socket_t * clientSocket,list_t * teacherList);

const char * http_request_getArg(http_request_t * self, const char * key);

void server_start_page(socket_t* clientSocket);
void server_POST(http_request_t req,socket_t * clientSocket,list_t * teacherList);
void server_GET_html(socket_t* clientSocket, list_t * teacherList);
void server_Paste_html(http_request_t req,socket_t* clientSocket,list_t * teacherList);

void server_GET_id_html(http_request_t req,socket_t* clientSocket,list_t * teacherList);
void server_answer(http_request_t req, socket_t * clientSocket,list_t * teacherList);





#endif
