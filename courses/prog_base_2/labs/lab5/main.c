#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "teacher.h"
#include "server.h"

int main()
{
    lib_init();

    //list_t * TeacherList = parse("teachers.json");

    sqlite3* db;

    if (SQLITE_ERROR == sqlite3_open("database.db", &db)) {
        printf("can't open database\n");
        exit(1);
    }



    socket_t * serverSocket = socket_new();
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);

    while (1) {
        socket_t * clientSocket = socket_accept(serverSocket);

        char buf[10000] = "";

        if (!socket_read(clientSocket, buf, sizeof(buf))) {
            puts("Skipping empty request");
            socket_close(clientSocket);
            socket_free(clientSocket);
            continue;
        }

        http_request_t req = http_request_parse(buf);
        server_answer(req, clientSocket, db);



        socket_close(clientSocket);
        socket_free(clientSocket);
    }

    socket_close(serverSocket);
    socket_free(serverSocket);

    lib_free();
    return 0;
}
