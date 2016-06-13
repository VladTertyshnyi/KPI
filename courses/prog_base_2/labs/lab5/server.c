#include "server.h"


void server_answer(http_request_t req, socket_t * clientSocket, sqlite3 * db) {
    puts(req.method);
    puts(req.uri);
    if (!strcmp(req.uri, "/Teacher-count"))
    {
        server_count(clientSocket, db);
    }
    else

        if (strncmp(req.uri, "/api/Teacher/", 13) == 0)
    {
        if(!strcmp(req.method, "GET"))
            server_GET_id(req, clientSocket, db);
        else if(!strcmp(req.method,"DELETE"))
            server_DELETE_id(req, clientSocket, db);
        else if(!strcmp(req.method,"POST"))
        {
            puts("1");
            server_POST(req, clientSocket, db);
        }
    }
    else


    if (!strncmp(req.uri, "/api/Teacher", 12))
    {
        if (!strcmp(req.method, "GET")) {
            if (!strncmp(req.uri, "/api/Teacher?", 13))  {
                int filtSubj, filtYears;
                char* str = req.uri;
                sscanf (str, "/api/Teacher?subjects=%i|years=%i", &filtSubj, &filtYears);
                server_GET_filt(req, clientSocket, db, filtSubj, filtYears);
            }
        else
            server_GET_all(req, clientSocket, db);
        }
        else if(!strcmp(req.method, "DELETE"))
            server_DELETE_all(req, clientSocket, db);
        else
            socket_write_string(clientSocket, "Method not allowed!\n");

    }
    else




    if(!strncmp(req.uri,"/Teacher/delete/",16))
    {
        server_DELETE_id(req, clientSocket, db);
    }
    else
    if (!strncmp(req.uri, "/Teacher?", 9)) {
        int filtSubj, filtYears;
        char* str = req.uri;
        sscanf (str, "/api/Teacher?subjects=%i|years=%i", &filtSubj, &filtYears);
        server_GET_filt_html(req, clientSocket, db, filtSubj, filtYears);
    }
    else  if(!strcmp(req.uri,"/Teacher"))
    {
        server_start_page(clientSocket);
    }
    else if(!strcmp(req.uri,"/Teacher/"))
    {
        server_GET_html(clientSocket, db);
    }
    else if(!strcmp(req.uri,"/Teacher/paste"))
    {
        server_Paste_html(req, clientSocket, db);
    }
    else if(!strncmp(req.uri, "/Teacher/", 9))
    {
        server_GET_id_html(req, clientSocket, db);
    }
    else
        socket_write_string(clientSocket,"\nHTTP1.1 404 NOT FOUND\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n""Teacher not found\n");
}




const char * http_request_getArg(http_request_t * self, const char * key) {
    for (int i = 0; i < self->formLength; i++) {
        if (strcmp(self->form[i].key, key) == 0) {
            return self->form[i].value;
        }
    }
    return NULL;
}

void server_send (socket_t * clientSocket, char * text) {
    char buf[10000];
    sprintf(buf, "\nHTTP1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "%s\n", strlen(text), text);
    socket_write_string(clientSocket,buf);
}

void server_count (socket_t * clientSocket, sqlite3 * db) {
    int count = db_countTeachers (db);
    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "count", cJSON_CreateNumber(count));
    char * text = cJSON_Print(SM);
    server_send(clientSocket,text);
}

char * teacher_toJSON (teacher_t self) {
    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "name", cJSON_CreateString(teacher_getName(self)));
    cJSON_AddItemToObject(SM, "birthdate", cJSON_CreateString(teacher_getBirthdate(self)));
    cJSON_AddItemToObject(SM, "years", cJSON_CreateNumber(teacher_getYears(self)));
    cJSON_AddItemToObject(SM, "rate", cJSON_CreateNumber(teacher_getRate(self)));
    cJSON_AddItemToObject(SM, "subjects", cJSON_CreateNumber(teacher_getSubjects(self)));
    char * jsonSM = cJSON_Print(SM);
    return jsonSM;
}

http_request_t http_request_parse(const char * const request) {
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

void server_GET_all(http_request_t req, socket_t * clientSocket, sqlite3 * db) {
    char text[10000] = "";
    char * buf = NULL;
    int count = 0, check = 0;
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Teacher";
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, 0);

    count = db_countTeachers(db);

    strcat(text, "[");

    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select teachers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            buf = teacher_toJSON(db_getTeacher(stmt));
            strcat(text, buf);
            if(check != count - 1) {
                strcat(text, ",");
                check++;
            }
        }
    }
    strcat(text, "]");
    server_send(clientSocket, text);
}

void server_DELETE_all(http_request_t req, socket_t * clientSocket, sqlite3 * db) {
    server_send(clientSocket, db_deleteAll(db));
}

void server_GET_id(http_request_t req, socket_t * clientSocket, sqlite3 * db) {
    char text[1000] = "";
    char * buf = NULL;
    int id, count = db_countTeachers(db);

    if(strpbrk(req.uri, "-0123456789")) {
        id = atoi(strpbrk(req.uri, "-0123456789"));
        if(!db_checkId (db, id)) {
            socket_write_string(clientSocket,"HTTP1.1 404 NOT FOUND\n"
            "Content-Type: json\n"
            "Content-Length: %i\r\n\r\n"
            "Id not found");
            return;
        }
    }
    else {
        socket_write_string(clientSocket,"Wrong id");
        return;
    }
    buf = teacher_toJSON(db_getTeacherById(db, id));
    strcat(text, buf);
    server_send(clientSocket, text);
}

void server_DELETE_id(http_request_t req, socket_t * clientSocket, sqlite3* db) {
    char buf[1000] = "";
    int id;

    if(strpbrk(req.uri,"-0123456789"))
    {
        id = atoi(strpbrk(req.uri,"-0123456789"));
        if(!db_checkId(db, id))
        {
            socket_write_string(clientSocket,"HTTP1.1 404 NOT FOUND\n"
            "Content-Type: json\n"
            "Content-Length: %i\r\n\r\n"
            "%s\n""<body>Id not found<br>"
                                  "<a href=\"/Teacher/\">To Teachers</a></body>");
            return;
        }
    }
    else
    {
        socket_write_string(clientSocket,"<body>Wrong id<br>"
                                  "<a href=\"/Teacher/\">To Teachers</a></body>");
        return;
    }
    db_deleteTeacherById (db, id);




    server_send(clientSocket, "<body>Delete success<br>"
                                  "<a href=\"/Teacher/\">To Teachers</a></body>");
}

void server_POST(http_request_t req, socket_t * clientSocket, sqlite3 * db) {
    const char * name = http_request_getArg(&req, "name");
    const char * birthdate = http_request_getArg(&req, "birthdate");
    const char * years = http_request_getArg(&req, "years");
    const char * rate = http_request_getArg(&req, "rate");
    const char * subjects = http_request_getArg(&req, "subjects");

    if(name == NULL || birthdate == NULL || years == NULL || rate == NULL || subjects == NULL)
    {
        socket_write_string(clientSocket,"<body> POST argument/arguments is/are empty<br>"
                                  "<a href=""/Teacher/"">To Teachers</a></body>");
        return;
    }

    char buf[1000] = "";
    int id;



    int check = 0;
    int dot = 0;

    for(int i = 0; i < strlen(rate); i++)
        if(!isdigit(rate[i]))
        {
            if(rate[i]=='.'||dot==0)
                dot++;
            else
                check++;
        }

    for(int i = 0; i < strlen(years); i++)
        if(!isdigit(years[i]))
            check++;

    for(int i = 0; i < strlen(subjects); i++)
        if(!isdigit(subjects[i]))
            check++;

    for(int i = 0; i < 4; i++)
        if(!isdigit(birthdate[i]))
            check++;

    if(birthdate[4]!='-')
        check++;

    for(int i = 5; i < 7; i++)
        if(!isdigit(birthdate[i]))
            check++;

    if(birthdate[7] != '-')
        check++;

    for(int i = 8; i < strlen(birthdate); i++)
        if(!isdigit(birthdate[i]))
            check++;

    if(atoi(birthdate+5) > 12)
        check++;

    if(dot > 1 || dot < 0)
    {
        socket_write_string(clientSocket,"<body>Invalid POST argument<br>"
                                  "<a href=""/Teacher/"">To Teachers</a></body>");
        return;
    }

    if(check == 0)
    {
        db_insertTeacher(db, name, atof(rate), atoi(subjects), atoi(years),  birthdate);



        socket_write_string(clientSocket, "<body>Post success<br>"
                                  "<a href=\"/Teacher/\">To Teachers</a></body>");
    }
    else
        socket_write_string(clientSocket,"<body>Invalid POST argument<br>"
                                  "<a href=\"/Teacher/\">To Teachers</a></body>");
}

void server_start_page(socket_t* clientSocket) {
    char text[]="<html>"
                "<head>"
                "<title>Lab4</title>"
                "</head>"
                "<body>"
                "<h1>HELLO Word</h1>"
                "<p><a href=""/Teacher/"">Teachers</a></p>"
                "</body>"
                "</html>";
    socket_write_string(clientSocket,text);
}

void server_GET_html(socket_t* clientSocket, sqlite3 * db) {
    char buf[10000]="<html>"
                    "<head>"
                    "<title>Lab4</title>"
                    "</head>"
                    "<body>"
                    "<h1>Teachers</h1>";
    char text [1000] = "";
    int count = db_countTeachers(db);
    int i = 0;
    teacher_t temp;

    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Teacher";
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, 0);

    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select teachers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            temp = db_getTeacher(stmt);
            sprintf(text, "<p><a href=""/Teacher/%i"">%s %s</a></p>", teacher_getId(temp), teacher_getName(temp), teacher_getBirthdate(temp));
            strcat(buf,text);
        }
        i++;
    }

    strcat(buf, "<p><a href=""/Teacher/paste"">New Teacher</a></p>");
    strcat(buf, "</body>"
           "</html>");
    socket_write_string(clientSocket, buf);
}

void server_Paste_html(http_request_t req, socket_t* clientSocket, sqlite3 * db) {
    char buf[5000] = "";
    char text[5000] = "";
    int id = (int) sqlite3_last_insert_rowid(db);

    sprintf(text, "<html>"
            "<body>"
            "<form action=""http://127.0.0.1:5000/api/Teacher/%i"" method=""POST"">"
            "Name:<br>"
            "<input type=""text"" name=""name""><br>"
            "Birthdate:<br>"
            "<input type=""text"" name=""birthdate"" ><br>"
            "Years:<br>"
            "<input type=""text"" name=""years""><br>"
            "Rate:<br>"
            "<input type=""text"" name=""rate""><br>"
            "Subjects:<br>"
            "<input type=""text"" name=""subjects""><br>"
            "<input type=""submit"" value='Send POST request' />"
            "</form>"
            "</body>", id);
    strcat(buf, text);
    socket_write_string(clientSocket, buf);
}

void server_GET_id_html(http_request_t req, socket_t* clientSocket, sqlite3 * db) {
    int id;

    if(strpbrk(req.uri,"-0123456789"))
    {
        id = atoi(strpbrk(req.uri,"-0123456789"));
        if (!db_checkId (db, id))
        {
            socket_write_string(clientSocket,"Id not found");
            return;
        }
    }
    else
    {
        socket_write_string(clientSocket,"Wrong id");
        return;
    }
    char text[1000] = "";
    char buf[10000] = "<html>"
                    "<head>"
                    "<title>Lab4</title>"
                    "</head>"
                    "<body>"
                    "<h1>Teacher</h1>";

    teacher_t temp = db_getTeacherById(db, id);
    sprintf(text,"<p>Name:\t\t%s</p>"
            "<p>Birthdate:\t%s</p>"
            "<p>Years:\t\t%i</p>"
            "<p>Rate:\t\t%.2f</p>"
            "<p>\tSubjects:\t\t%i\n\n\n</p>"
            "<p><a href=""/Teacher/"">To prev page</a></p>",
            teacher_getName(temp),
            teacher_getBirthdate(temp),
            teacher_getYears(temp),
            teacher_getRate(temp),
            teacher_getSubjects(temp)
           );
    strcat(buf, text);
    sprintf(text, "<p><a href=\"/Teacher/\" onclick=\"doDelete()\">Delete Teacher</a></p>"
                 "<script>"
                 "function doDelete(){"
                 "var xhttp=new XMLHttpRequest();"
                 "xhttp.open(\"DELETE\",\"/api/Teacher/%i\",true);"
                 "xhttp.send();"
                 "}"
                 "</script>", id);
    strcat(buf, text);
    strcat(buf, "</body>"
           "</html>");
    socket_write_string(clientSocket, buf);
}







void server_GET_filt_html(http_request_t req, socket_t* clientSocket, sqlite3 * db, int filtSubj, int filtYears) {
    char buf[10000]="<html>"
                    "<head>"
                    "<title>Lab5</title>"
                    "</head>"
                    "<body>"
                    "<h1>Teachers</h1>";
    char text [1000] = "";
    teacher_t temp;

    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Teacher WHERE subjects > ? OR years > ?";
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, filtSubj);
    sqlite3_bind_int(stmt, 2, filtYears);

    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't filt teachers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            temp = db_getTeacher(stmt);
            sprintf(text, "<p><a href=""/Teacher/%i"">%s %s</a></p>", teacher_getId(temp), teacher_getName(temp), teacher_getBirthdate(temp));
            strcat(buf,text);
        }
    }

    strcat(buf, "<p><a href=""/Teacher/paste"">New Teacher</a></p>");
    strcat(buf, "</body>"
           "</html>");
    socket_write_string(clientSocket, buf);

}

void server_GET_filt(http_request_t req, socket_t * clientSocket, sqlite3 * db, int filtSubj, int filtYears) {
    char text[10000] = "";
    char * buf = NULL;
    int count = 0, check = 0;
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Teacher WHERE subjects > ? OR years > ?";
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, filtSubj);
    sqlite3_bind_int(stmt, 2, filtYears);

    count = db_countTeachers(db);

    strcat(text, "[");

    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select teachers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            buf = teacher_toJSON(db_getTeacher(stmt));
            strcat(text, buf);
            if(check != count - 1) {
                strcat(text, ",");
                check++;
            }
        }
    }
    strcat(text, "]");
    server_send(clientSocket, text);
}

