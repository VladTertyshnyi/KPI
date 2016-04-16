#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "post.h"

int main()
{
    srand(time(NULL));

    core_t * core1 = core_createCore(1);
    int i;
    for(i = 0; i <10; i++)
    core_addPost(core1, post_createPost(i));
    core_updateCore(core1);
    core_printCore(core1);
    core_deleteCore(core1);
    post_runTests();
    core_runTests();
    return 0;
}
