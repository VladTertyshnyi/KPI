#include "core.h"
#include "post.h"
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>
#include <cmocka_pbc.h>

static void createPost_One_idIsOne(void** state){
    const int test = 1;
    post_t * tPost = post_createPost(test);
    assert_int_equal(test, post_getPostID(tPost));
    post_deletePost(tPost);
}
static void createPost_WrngID_StatusIsNoActWrgId(void** state){
    post_t * tPost = post_createPost(-1);
    assert_int_equal(post_getPostStatus(tPost), NO_ACT_WRNG_ID);
    post_deletePost(tPost);
}

static void getPostStatus_OneAction_StatusIsOK(void** state){
    post_t * tPost = post_createPost(1);
    post_updatePost(tPost);
    int test_status = post_getPostStatus(tPost);
    assert_int_equal(test_status, POST_OK);
    post_deletePost(tPost);
}

static void updatePost_Default_SpeedIntervalIsOK(void** state){
    post_t * tPost = post_createPost(1);
    int i;
    for(i = 0; i < 1000; i ++){
    post_updatePost(tPost);
    assert_in_range(post_getCarSpeed(tPost), 0, 350);
    }
    post_deletePost(tPost);
}

static void getPostStatus_IdIsWrng_AfterCallStatusIsntOk(void** state){
    post_t * tPost = post_createPost(-11);
    assert_int_equal(post_getPostStatus(tPost), NO_ACT_WRNG_ID);
    assert_int_equal(post_getPostStatus(tPost), NO_ACT_WRNG_ID);
    post_deletePost(tPost);
}



void post_runTests(void){

	const struct CMUnitTest tests[] =
	{
        cmocka_unit_test(createPost_One_idIsOne),
        cmocka_unit_test(createPost_WrngID_StatusIsNoActWrgId),
        cmocka_unit_test(getPostStatus_OneAction_StatusIsOK),
        cmocka_unit_test(updatePost_Default_SpeedIntervalIsOK),
        cmocka_unit_test(getPostStatus_IdIsWrng_AfterCallStatusIsntOk),
    };
	return cmocka_run_group_tests(tests, NULL, NULL);
}
