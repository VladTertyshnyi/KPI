#ifndef SUPADIVE_H_INCLUDED
#define SUPADIVE_H_INCLUDED

#define MAX_DATA_LEN 100
#define MAX_NAME_LEN 20

#define SUCCESS 0
#define FAILURE 1

#include "list.h"
#define EMPTY_STRING "hello_there"
#define MAX_USER_COUNT 20

typedef struct data_s data_t;
typedef struct user_s user_t;
typedef struct dataShelter_s dataShelter_t;
typedef struct sub_s sub_t;

typedef void (*callback) (user_t * user, data_t * data, dataShelter_t * shelter);

data_t * data_create(char * dataName, char * dataValue);
void data_delete(data_t * dataPtr);

user_t * user_create(char * userName);
void user_delete(user_t* userPtr);

dataShelter_t * shelter_create(char * shelterName);
void shelter_delete(dataShelter_t * shelterPtr);

void shelter_addUser(dataShelter_t * shelter, user_t * user);
void shelter_deleteUser(dataShelter_t * shelter, user_t * user);
void user_addData(user_t * user, data_t * data);
void shelter_printData(dataShelter_t * shelter);

//callback functions
void success(user_t * reciever, user_t * subscriber, dataShelter_t * shelter);
void failure(user_t * reciever, user_t * subscriber, dataShelter_t * shelter);





#endif // SUPADIVE_H_INCLUDED
