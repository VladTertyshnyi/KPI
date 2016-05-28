#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>

#include "../headers/sqlite3.h"
#include "../headers/dbModule.h"
#include "../headers/director.h"
#include "../headers/list.h"
#include "../headers/xmlModule.h"
#include "../headers/http.h"
#include "../headers/socket.h"
#include "../headers/FSHelper.h"

#ifndef TRUE
#define TRUE
#endif // TRUE

#define CURL_STATICLIB

int main(void)
{
    // Begin work with sockets.
    lib_init();

    // Initialize server socket.
    socket_t *server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);

    // Create directors set.
    int directorsAmount = INITIAL_DIRECTORS_AMOUNT;
    director_t *directorsSet[MAX_DIRECTORS_AMOUNT];
    for (int i = 0; i < MAX_DIRECTORS_AMOUNT; i++)
    {
        directorsSet[i] = director_new_empty();
    }
    xmlModule_parseDirector(directorsSet);

    // Create database entity.
    db_t *testDB = database_new(DATABASE_FILE_PATH);

    // Buffer for socket messages.
    char socketBuffer[10000] = "\0";

    while (TRUE)
    {
        printf("Waiting for connection...");

        // Get message from server.
        socket_t *client = socket_accept(server);
        socket_read(client, socketBuffer, sizeof(socketBuffer));
        printf("%s", socketBuffer);

        // Parse message from server to structure http_request_t.
        http_request_t request = http_request_parse(socketBuffer);

        // Invoke certain http request method.
        if (!strcmp(request.method, "GET"))
        {
            if (!strcmp(request.uri, "/info"))
            {
                http_sendXML(client, "src/data/Info.xml");
            }
            else if (!strcmp(request.uri, "/external"))
            {
                http_sendHtml(client, "src/data/NotDone.xml");
            }
        }
        else if (!strcmp(request.method, "KEEPALIVE"))
        {
            // Handler for empty request.
            // Program shouldn't do anything in this case.
            http_sendHtml(client, "src/html/emptyMethod.html");
        }
        else
        {
            http_sendHtml(client, "src/html/incorrectMethod.html");
        }
        socket_free(client);
    }

    // At the end of the program, free allocated memory.
    socket_free(server);
    lib_free();

    // End of the program.
    return 0;
}
