#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <winsock2.h>

#include "sqlite3.h"
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

void server_send(socket_t * clientSocket, char * text);
void server_count(socket_t * clientSocket, sqlite3 * db);
char * teacher_toJSON (teacher_t self);

http_request_t http_request_parse(const char * const request);
const char * http_request_getArg(http_request_t * self, const char * key);

void server_answer(http_request_t req, socket_t * clientSocket, sqlite3 * db);
void server_GET_all(http_request_t req, socket_t * clientSocket, sqlite3 * db);
void server_DELETE_all(http_request_t req, socket_t * clientSocket, sqlite3 * db);
void server_GET_id(http_request_t req, socket_t * clientSocket, sqlite3 * db);
void server_DELETE_id(http_request_t req, socket_t * clientSocket, sqlite3* db);
void server_POST(http_request_t req, socket_t * clientSocket, sqlite3 * db);

void server_start_page(socket_t* clientSocket);
void server_GET_html(socket_t* clientSocket, sqlite3 * db);
void server_Paste_html(http_request_t req, socket_t* clientSocket, sqlite3 * db);
void server_GET_id_html(http_request_t req, socket_t* clientSocket, sqlite3 * db);
void server_GET_filt_html(http_request_t req, socket_t* clientSocket, sqlite3 * db, int filtSubj, int filtYears);
void server_GET_filt(http_request_t req, socket_t * clientSocket, sqlite3 * db, int filtSubj, int filtYears);


int db_countTeachers (sqlite3 * db);
teacher_t db_getTeacher (sqlite3_stmt * stmt);
teacher_t db_getTeacherById (sqlite3 * db, int id);
char* db_deleteAll (sqlite3 * db);
int db_deleteTeacherById (sqlite3* db, int id);
int db_insertTeacher(sqlite3 * db, char * name, double rate, int subjects, int years, char * birthdate);
int db_checkId (sqlite3* db, int id);


#endif // SERVER_H_INCLUDED
