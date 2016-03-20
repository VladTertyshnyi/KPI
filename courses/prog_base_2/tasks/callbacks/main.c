#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (* Client_CB)(const char *, int);


void server(Client_CB func0, Client_CB func1, char *clients[]){
    int id;
    char * new_client[20];
    for (id = 0; id < 10; id++){
        if (clients[id] == '\0'){
            scanf("%s", &new_client);
            clients[id] = new_client;
            func0(clients[id], id);
        }
        else{
            func1(clients[id], id);
            clients[id] = '\0';
        }
    }
}

void  onClientConnectedCB(const char * client, int index){
    printf("*******************\nClient -- %s -- connected\nHis id: %i\n*******************\n", client, index);
}

void onClientDisconnected(const char * client, int index){
    printf("*******************\nClient -- %s -- disconnected\nHis id: %i\n*******************\n", client, index);
}

int main(){
    char * client_list[20] = {'\0'};
    client_list[0] = "Rob";
    client_list[1] = "Nick";
    client_list[8] = "Vlad";
    client_list[9] = "Ruslan";
    Client_CB conn_CB =  onClientConnectedCB;
    Client_CB discon_CB = onClientDisconnected;
    server(conn_CB, discon_CB, client_list);
    return 0;
}
