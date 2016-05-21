#include <stdio.h>
#include <stdlib.h>
#include "chat.h"
#include "list.h"
int main()
{
    chat_t * chat = chat_new("Chat 1");
    user_t * user = user_new("Vasya");
    chat_addUser(chat, user);
    chat_getName(chat);
    chat_printUserList(chat);
    //chat_sendMessage(chat, user, "Privet");




    user_delete(user);
    chat_delete(chat);
    return 0;
}
