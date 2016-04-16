#ifndef POST_H_INCLUDED
#define POST_H_INCLUDED

#define CAR_MAX_SPEED 350
#include <stdio.h>
#include <stdlib.h>

typedef struct post_s post_t;
typedef enum post_status_error post_status;

enum post_status_error{
    POST_OK,
    FAILED,
    NO_ACTIONS,
    NULL_ERROR,
    POST_WRONG_ID,
    NO_ACT_WRNG_ID
};


post_t * post_createPost(int id);
void post_deletePost(post_t * self_post);
int post_getPostStatus(post_t * self_post);
void post_updatePost(post_t * self_post);
int  post_getPostID(post_t * self_post);
char * post_getCarId(post_t * self_post);
int  post_getCarSpeed(post_t * self_post);


#endif // POST_H_INCLUDED
