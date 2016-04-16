#include "core.h"
#include "post.h"
#include <string.h>
#define CAR_ID_MAX_SYMB 5


struct post_s{
    int id;
    char  last_car_id[6];
    unsigned int last_car_speed;
    //core id connected to
    post_status status_code;
};

post_t * post_createPost(int id){
    post_t * self_post = malloc(sizeof(struct post_s));
    self_post->id = id;
    self_post->last_car_speed = 0;
    sprintf(self_post->last_car_id, "A0000");
    if(id < 0){
        self_post->status_code = NO_ACT_WRNG_ID;
    }else{
    self_post->status_code = NO_ACTIONS;
    }
    return self_post;
}

void post_deletePost(post_t * self_post){
    if(self_post != NULL){
        free(self_post);
    }else{
        self_post -> status_code = NULL_ERROR;
        printf("NULL ERROR");
        exit(-1);
    }
}

int post_getPostStatus(post_t * self_post){
    if(self_post != NULL){
        post_status temp_status = self_post -> status_code;
        if(self_post->status_code == POST_WRONG_ID || self_post->status_code == NO_ACT_WRNG_ID || self_post->status_code == NO_ACTIONS){
            return temp_status;
        }
        self_post->status_code  = POST_OK;
        return temp_status;
    }else{
        printf("NULL ERROR");
        exit(-1);
    }
}

void post_updatePost(post_t * self_post){
    if(self_post != NULL){
        self_post->last_car_speed = rand()%CAR_MAX_SPEED;
        int rand1 = rand()%10000;
        int rand2 = rand()%25 + 65;
        sprintf(self_post->last_car_id,"%d%d", rand2, rand1);
        if(self_post->status_code == NO_ACT_WRNG_ID || self_post->status_code == CORE_WRONG_ID){
            self_post->status_code == CORE_WRONG_ID;
        }else{
        self_post -> status_code = POST_OK;
        }
    }else{
        self_post -> status_code = NULL_ERROR;
        printf("NULL ERROR");
        exit(-1);
    }
}
int  post_getPostID(post_t * self_post){
    if(self_post!=NULL){
    self_post->status_code = POST_OK;
    return self_post->id;
    }else{
        self_post -> status_code = NULL_ERROR;
        printf("NULL ERROR");
        exit(-1);
    }
}
char * post_getCarId(post_t * self_post){
    if(self_post!=NULL){
    self_post->status_code = POST_OK;
    return self_post->last_car_id;
    }else{
        self_post -> status_code = NULL_ERROR;
        printf("NULL ERROR");
        exit(-1);
    }
}

int  post_getCarSpeed(post_t * self_post){
    if(self_post!=NULL){
    self_post->status_code = POST_OK;
    return self_post->last_car_speed;
    }else{
        self_post -> status_code = NULL_ERROR;
        printf("NULL ERROR");
        exit(-1);
    }
}
