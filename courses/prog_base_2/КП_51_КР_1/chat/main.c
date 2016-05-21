#include "list.h"
#include "chat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct chat_s{
    char * chatName;
    list_t * usersConnected;
    list_t * messages;
    int usersCount;
};

struct user_s{
    char * name;
    char * chatConnTo;
};

struct message_s{
    char * data;
    char * sender;
};

///////////////////////////////////////////////////////////////////

chat_t * chat_new(char * selfName){
    chat_t * selfChat = malloc(sizeof(struct chat_s));
    selfChat->chatName = selfName;
    selfChat->usersConnected = list_new();
    selfChat->messages = list_new();
    selfChat->usersCount = 0;
    return selfChat;
}

user_t * user_new(char * selfName){
    user_t * selfUser = malloc(sizeof(struct user_s));
    selfUser->name = selfName;
    selfUser->chatConnTo = EMPTY_CHAT;
    return selfUser;
}

void chat_delete(chat_t * selfChat){
    if(selfChat != NULL){
        list_delete(selfChat->usersConnected);
        list_delete(selfChat->messages);
        free(selfChat);
    }
}

void user_delete(user_t * selfUser){
    if( selfUser != NULL){
        free(selfUser);
    }
}

void chat_addUser(chat_t * selfChat, user_t * selfUser){
    if(selfChat != NULL && selfUser != NULL){
        selfUser->chatConnTo = selfChat -> chatName;
        list_insertLast(selfChat->usersConnected, (void*)selfUser);
        selfChat->usersCount += 1;
    }
}

void chat_deleteUser(chat_t * selfChat, int index){
    if(selfChat != NULL && index > 0){
        list_removeByIndex(selfChat->usersConnected, index);
        selfChat->usersCount -= 1;
    }
}

void chat_getName(chat_t * selfChat){
    if(selfChat != NULL){
        puts(selfChat->chatName);
    }
}

void chat_printUserList(chat_t * selfChat){
    if(selfChat != NULL){
        if(list_isEmpty(selfChat->usersConnected)){
            puts("No users connected");
            return;
        }
        printf("\n Users connected to chat %s:\n", selfChat->chatName);
        user_t * tempUser;
        for(int i = 0; i < selfChat->usersCount; i++){
            tempUser = (user_t*)list_getNodeByIndex(selfChat->usersConnected, i);
            printf("%d. %s\n", i, tempUser->name);
        }
    }
}

int chat_getUsersCount(chat_t * selfChat){
    if(selfChat != NULL){
        return selfChat->usersCount;
    }
}

void chat_sendMessage(chat_t * selfChat, user_t * selfUser, char * message){
    if(selfChat != NULL && selfUser != NULL){
        if(selfUser->chatConnTo == selfChat->chatName){
        message_t * tempMessage;
        tempMessage-> data = message;
        tempMessage->sender = selfUser->name;
        list_insertLast(selfChat->messages, tempMessage);
    }
}
}


