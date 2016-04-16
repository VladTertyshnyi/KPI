#include "core.h"
#include <windows.h>

void Setcolor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}



struct core_s{
    int core_id;
    post_t ** postList;
    core_status CORE_STATUS;
    unsigned int posts_connected;
};

core_t * core_createCore(int id){
        core_t * self_core= malloc(sizeof(struct core_s));
        self_core->posts_connected = 0;
        self_core->core_id = id;
        self_core->postList = malloc(sizeof(struct post_s *) * self_core->posts_connected);
        if(id < 0){
            self_core->CORE_STATUS = CORE_WRONG_ID;
        }else{
        self_core->CORE_STATUS = NO_POSTS;
        }
        return  self_core;
}

void core_deleteCore(core_t * self_core){
    if(self_core != NULL){
        free(self_core->postList);
        free(self_core);
    }else{
        printf("NULL ERROR");
        exit(-1);
    }
}

void core_addPost(core_t * self_core, post_t * self_post){
    if(self_core != NULL && self_post != NULL){
        self_core->posts_connected ++;
        self_core->postList = realloc(self_core->postList, sizeof(struct post_s *) * self_core->posts_connected);
        if(self_core->postList !=NULL){
        self_core->postList[self_core->posts_connected - 1] = self_post;
        self_core->CORE_STATUS = CORE_OK;
        }else{
            printf("NULL ERROR");
            exit(-1);
        }
    }else{
    printf("NULL ERROR");
        exit(-1);
    }

}

post_t * core_getPostByID(core_t * self_core, int id){
    if(id>-1 && id < self_core->posts_connected){
        self_core->CORE_STATUS = CORE_OK;
        return self_core->postList[id];
    }else{
        return;
    }
}
void core_updateCore(core_t * self_core){
    if(self_core != NULL) {
        if(self_core->CORE_STATUS != NO_POSTS){
            int i;
        for(i = 0; i < self_core->posts_connected; i ++)
            post_updatePost(self_core->postList[i]);
        self_core->CORE_STATUS = CORE_OK;
        }else{
        printf("No posts, add something");
        return;}
    }else{
        printf("NULL ERROR");
        exit(-1);
    }
}

void core_printCore(core_t * self_core){
    if(self_core != NULL){
    int i;
    //printf("You're connected to core %i\n", self_core->core_id);
    for(i = 0; i < self_core->posts_connected; i++){
        if(post_getCarSpeed(self_core->postList[i])>150)
            Setcolor(192);
        printf("POST ID|CAR SPEED|CAR ID\n%7d %9i %6s\n",
        post_getPostID(self_core->postList[i]), post_getCarSpeed(self_core->postList[i]), post_getCarId(self_core->postList[i]));
        Setcolor(7);

    }
        self_core->CORE_STATUS = CORE_OK;
    }else{
        printf("NULL ERROR");
        exit(-1);
    }
}
int core_getPostsCon(core_t * self_core){
    if(self_core != NULL){
        if(self_core->CORE_STATUS != NO_POSTS){
            self_core->CORE_STATUS = CORE_OK;
            return self_core->posts_connected;
        }
    }else{
        printf("NULL  ERROR");
        exit(-1);
    }
}
 int core_GetCoreStatus(core_t * self_core){
    if(self_core != NULL){
        return self_core ->CORE_STATUS;
    }
}
//post_get_id(self->


