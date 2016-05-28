#include <stddef.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/http.h"

http_request_t http_request_parse(char * request)
{
    http_request_t req;
    req.form = NULL;
    req.formLength = 0;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    // parse form data
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0)
    {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr)
        {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char * http_request_getArg(http_request_t * self, const char * key)
{
    for (int i = 0; i < self->formLength; i++)
    {
        if (strcmp(self->form[i].key, key) == 0)
        {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self)
{
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}

void http_sendHtml(socket_t *client, char *htmlPath)
{
    char pageContentToReceive[100000];
    FILE *f = fopen(htmlPath, "r");
    int len = fread(pageContentToReceive, 1, sizeof(pageContentToReceive), f);
    pageContentToReceive[len] = '\0';

    char pageContentToSend[1024];
    sprintf(pageContentToSend,
            "HTTP/1.1 %s\n"
            "Content-Type: text/html\n"
            "Content-Length: %d\n"
            "Connection: keep-alive\r\n\r\n"
            "\n%s",
            (strstr(pageContentToReceive, "404 page</title>") == NULL) ? "200 OK" : "404",
            strlen(pageContentToReceive),
            pageContentToReceive);
    socket_write_string(client, pageContentToSend);

    fclose(f);
    socket_close(client);
}

void http_sendXML(socket_t *client, char *xmlPath)
{
    char xmlContentToReceive[100000];
    FILE *f = fopen(xmlPath, "r");
    int len = fread(xmlContentToReceive, 1, sizeof(xmlContentToReceive), f);
    xmlContentToReceive[len] = '\0';

    char xmlContentToSend[1024] = "\0";
    sprintf(xmlContentToSend,
            "HTTP/1.1 %s\n"
            "Content-Type: application/xml\n"
            "Content-Length: %d\n"
            "Connection: keep-alive\r\n\r\n"
            "\n%s",
            (strstr(xmlContentToReceive, "404 page</title>") == NULL) ? "200 OK" : "404",
            strlen(xmlContentToReceive),
            xmlContentToReceive);
    socket_write_string(client, xmlContentToSend);

    fclose(f);
    socket_close(client);
}
