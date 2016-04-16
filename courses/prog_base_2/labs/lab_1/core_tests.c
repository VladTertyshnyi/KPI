#include "core.h"
#include "post.h"
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>
#include <cmocka_pbc.h>

static void createCore_Deafault_StatusIsNoPost(void** state){
    core_t * tCore = core_createCore(1);
    assert_int_equal(1, core_GetCoreStatus(tCore));
    core_deleteCore(tCore);
}
static void addPost_OnePost_PostsConIsOne(void** state){
    core_t * tCore = core_createCore(1);
    core_addPost(tCore, post_createPost(1));
    assert_int_equal(1, core_getPostsCon(tCore));
    core_deleteCore(tCore);
}

static void addPost_OnePost_StatusIsOk(void** state){
    core_t * tCore = core_createCore(1);
    core_addPost(tCore, post_createPost(1));
    assert_int_equal(CORE_OK, core_GetCoreStatus(tCore));
    core_deleteCore(tCore);

}


static void getPostByID_OnePost_testIdIsEqual(void** state){
    core_t * tCore = core_createCore(1);
    int testID = 777;
    core_addPost(tCore, post_createPost(testID));
    post_t * tPost = core_getPostByID(tCore, 0);
    assert_int_equal(testID, post_getPostID(tPost));
    core_deleteCore(tCore);
}

void core_runTests(void){

	const struct CMUnitTest tests[] =
	{
	    cmocka_unit_test(createCore_Deafault_StatusIsNoPost),
	    cmocka_unit_test(addPost_OnePost_PostsConIsOne),
	    cmocka_unit_test(addPost_OnePost_StatusIsOk),
	    cmocka_unit_test(getPostByID_OnePost_testIdIsEqual),

    };
	return cmocka_run_group_tests(tests, NULL, NULL);
}
