#include "cJSON.h"
#include "parse.h"

list_t* parse (const char* fileName) {
    FILE * file = fopen(fileName, "r");
    char text[10000];
    char line[100];

    while(fgets(line, 100, file) != NULL)
    {
        strcat(text, line);
    }
    fclose(file);

    cJSON * jList = cJSON_Parse(text);
    if (!jList)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return NULL;
    }

    teacher_t teacherArray[cJSON_GetArraySize(jList)];

    for (int i = 0; i < cJSON_GetArraySize(jList); i++)
    {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        char * name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char * birthdate = cJSON_GetObjectItem(jItem, "birthdate")->valuestring;
        int subjects = cJSON_GetObjectItem(jItem, "subjects")->valueint;
        int salary = cJSON_GetObjectItem(jItem, "salary")->valueint;
        double rate = cJSON_GetObjectItem(jItem, "rate")->valuedouble;

        teacherArray[i] = teacher_new(name, birthdate, salary, rate, subjects);
    }

    list_t * teacherList = list_new();
    teacherList = teacher_toList(teacherArray, cJSON_GetArraySize(jList));



    cJSON_Delete(jList);
    return teacherList;
}
