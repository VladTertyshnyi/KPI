#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

#define EMPTY_CHAT "empty_chat"

typedef struct chat_s chat_t;

typedef struct user_s user_t;

typedef struct message_s message_t;

chat_t * chat_new(char * selfName);

user_t * user_new(char * selfName);

void chat_delete(chat_t * selfChat);

void user_delete(user_t * selfUser);

void chat_addUser(chat_t * selfChat, user_t * selfUser);

void chat_deleteUser(chat_t * selfChat, int index);

void chat_getName(chat_t * selfChat);


void chat_printUserList(chat_t * selfChat);

int chat_getUsersCount(chat_t * selfChat);

void chat_sendMessage(chat_t * selfChat, user_t * selfUser, char * message);

#endif // CHAT_H_INCLUDED
