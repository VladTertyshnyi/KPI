#include "SupaDive.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>

struct data_s
{
    char dName[MAX_NAME_LEN];
    char data[MAX_DATA_LEN];
};

struct user_s
{
    list_t *dataList;
    char uName[MAX_NAME_LEN];
};

struct sub_s{
    user_t * userSub;
    callback notification[2];
};

sub_t * sub_new(user_t * user){
    sub_t * sub = malloc(sizeof(struct sub_s));
    sub->userSub = user;

    sub->notification[0] = success;
    sub->notification[1] = failure;
}

struct dataShelter_s
{
    list_t * subsList;
    list_t * userList;
    char * shName[MAX_NAME_LEN];
};

data_t * data_create(char * selfName, char * selfData){
    data_t * self = malloc(sizeof(struct data_s));

    memset(self->dName, 0, MAX_NAME_LEN);
    memset(self->data, 0, MAX_DATA_LEN);

    strncpy(self->dName, selfName, MAX_NAME_LEN);
    strncpy(self->data, selfData, MAX_DATA_LEN);
    return self;
}

void data_delete(data_t * self){
    memset(self->dName, 0, MAX_NAME_LEN);
    memset(self->data, 0, MAX_DATA_LEN);

    strncpy(self->dName, EMPTY_STRING, MAX_NAME_LEN);
    strncpy(self->data, EMPTY_STRING, MAX_DATA_LEN);
}

user_t * user_create(char * selfName){
    user_t * self = malloc(sizeof(struct user_s));
    self->dataList = list_new();
    memset(self->uName, 0, MAX_NAME_LEN);
    strncpy(self->uName, selfName, MAX_NAME_LEN);
    return self;
}

void user_delete(user_t* self){
    if(self == NULL){
        return;
    }
    int size = list_getSize(self->dataList);
    while(size>0){
       data_delete((data_t *)(list_getNodeValueByIndex(self->dataList, size -1)));
       size--;
    }
    list_delete(self->dataList);
    free(self);
}

void user_addData(user_t * user, data_t * data){
    if(user == NULL)
        return 0;
    list_insertLast(user->dataList, (void*) data);

}

void user_delData(user_t * user, data_t * data){
    if(user == NULL)
        return 0;
    list_removeLast(user->dataList);
}

dataShelter_t * shelter_create(char * selfName){
    dataShelter_t * self = malloc(sizeof(struct dataShelter_s));
    memset(self->shName, 0, MAX_NAME_LEN);
    self->userList = list_new();
    self->subsList = list_new();
    strncpy(self->shName, selfName, MAX_NAME_LEN);
    return self;
}

void shelter_delete(dataShelter_t * self){
    if(self == NULL)
        return;
    int size = list_getSize(self->userList);
    while(size > 0){
    user_delete(list_getNodeValueByIndex(self->userList, size-1));
    size--;
    }
    list_delete(self->subsList);
    list_delete(self->userList);
    free(self);
}




void shelter_addUser(dataShelter_t * shelter, user_t * user){
    if(user == NULL || shelter == NULL)
        return;
    if(list_getSize(shelter->userList) > MAX_USER_COUNT){
        //do notification 'failure'
        return;
    }
    list_insertLast(shelter->subsList,  (void*)sub_new(user));

    list_insertLast(shelter->userList,  (void*)user);

    printf("\nSuccessfully added user '%s' to data shelter '%s';", ((user_t *)list_getLast(shelter->userList))->uName, shelter->shName);
    printf("\nUser '%s' subscribed to notifications;\n", user->uName);
    int i;
    sub_t * tempSub;
    if(list_getSize(shelter->subsList) > 0){
        puts("\n=============CALLBACK NOTIFICATION START==================");
        for(i = 0; i < list_getSize(shelter->subsList); i++){
            tempSub = list_getNodeValueByIndex(shelter->subsList, i);
            tempSub->notification[SUCCESS](tempSub->userSub, user, shelter); //do notification success
        }
        puts("\n=============CALLBACK NOTIFICATION END==================");
    }
}

void shelter_deleteUser(dataShelter_t * shelter, user_t * user){
    if(user == NULL || shelter == NULL)
        return;
    int size = list_getSize(shelter->userList);
    int index;
    int i = 0;
    user_t * temp_user;
    for(i = 0; i < size; i++){
        temp_user = (user_t *)list_getNodeValueByIndex(shelter->userList, i);
        if(temp_user->uName == user->uName){
            index = i;
            break;
        }
    }
    user_t * userUn = (user_t *)list_removeByIndex(shelter->userList, index);
    ////

    list_removeByIndex(shelter->subsList, index);
    printf("\nSuccessfully deleted user '%s' from shelter '%s';", temp_user->uName, shelter->shName);
    printf("\nUser '%s' unsubscribed from notifications;\n", temp_user->uName);

    sub_t * tempSub;
    if(list_getSize(shelter->subsList)>0){
        puts("\n=============CALLBACK NOTIFICATION START==================");
        for(i = 0; i < list_getSize(shelter->subsList); i++){
            tempSub = list_getNodeValueByIndex(shelter->subsList, i);
            tempSub->notification[FAILURE](tempSub->userSub, userUn, shelter); //do notification success
        }
        puts("\n=============CALLBACK NOTIFICATION END==================");
    }
}

void shelter_printData(dataShelter_t * shelter){
    if(shelter == NULL)
        return;
    printf("\nData from of shelter '%s':\n", shelter->shName);
    int i, j;
    data_t * tempData;
    user_t * temp;
    for(i = 0; i < list_getSize(shelter->userList); i++){
        temp = (user_t *)list_getNodeValueByIndex(shelter->userList, i);
        printf(" %d. User '%s':\n", i+1, temp->uName);
        for(j = 0; j < list_getSize(temp->dataList); j++){
            tempData = list_getNodeValueByIndex(temp->dataList, j);
            printf("  %d. Name: '%s', value:'%s';\n", j+1, tempData->dName, tempData->data);
        }
    }
}


void success(user_t * reciever, user_t * subscriber, dataShelter_t * shelter){
    //printf stuff
    printf("\nSubscriber '%s' got notification that '%s' just have joined shelter '%s'\n",
        reciever->uName, subscriber->uName, shelter->shName);
}

void failure(user_t * reciever, user_t * unsubscriber, dataShelter_t * shelter){
    //printf stuff
    printf("\nSubscriber '%s' got notification that '%s' just have left shelter '%s'\n",
        reciever->uName, unsubscriber->uName, shelter->shName);
}
