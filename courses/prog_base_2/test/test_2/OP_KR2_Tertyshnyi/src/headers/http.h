#pragma once

#include "socket.h"

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct htpp_request_s
{
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
} http_request_t;

http_request_t http_request_parse(char * request);
const char * http_request_getArg(http_request_t * self, const char * key);
const char * keyvalue_toString(keyvalue_t * self);

void http_sendHtml(socket_t *client, char *htmlPath);
void http_sendXML(socket_t *client, char *xmlPath);
