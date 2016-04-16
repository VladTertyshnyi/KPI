#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include "post.h"

typedef enum core_status_e core_status;
typedef struct core_s core_t;

enum core_status_e{
    CORE_OK = 0,
    NO_POSTS,
    CORE_FAILED,
    CORE_WRONG_ID
};

core_t * core_createCore(int id);
void core_deleteCore(core_t * self_core);
void core_addPost(core_t * self_core, post_t * self_post);
post_t * core_getPostByID(core_t * self_core, int id);
void core_updateCore(core_t * self_core);
void core_printCore(core_t * self_core);
int core_getPostsCon(core_t * self_core);
int core_GetCoreStatus(core_t * self_core);


#endif // CORE_H_INCLUDED
