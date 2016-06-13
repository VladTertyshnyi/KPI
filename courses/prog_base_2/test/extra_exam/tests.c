
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>
#include <cmocka_pbc.h>
#include <stdlib.h>


static void findWordsInString_stringWithNoLetters_zeroWords(void** state)
{
    char * test_string = "   !@#$! !3145234";
    assert_int_equal(0, findWordsInString(test_string));
}

static void findWordsInString_startsWithSpaceOneWord_oneWord(void** state)
{
    char * test_string = "    oneWord";
    assert_int_equal(1, findWordsInString(test_string));
}

static void findWordsInString_twoWordsDividedWithNumbers_twoWords(void** state)
{
    char * test_string = "Two4Words666";
    assert_int_equal(2, findWordsInString(test_string));
}

static void findWordsInString_OneWordStringEndsWithSpace_OneWord(void** state)
{
    char * test_string = "Word    ";
    assert_int_equal(1, findWordsInString(test_string));
}

static void findWordsInString_ThreeWordsDividedWithDifferentSymbols_ThreeWords(void** state)
{
    char * test_string = "&@$%^!First!  2485729!$$#@&Second&&&  &&&Third";
    assert_int_equal(3, findWordsInString(test_string));
}

static void findWordsInString_NormalMessageFrom6words_6Words(void** state)
{
    char * test_string = "This is message from six words.";
    assert_int_equal(6, findWordsInString(test_string));
}

static void findWordsInString_NULL_0words(void** state)
{
    char * test_string = NULL;
    assert_int_equal(0, findWordsInString(test_string));
}

void findWordsInString_runTests(void){
	const struct CMUnitTest tests[] =
	{
        cmocka_unit_test(findWordsInString_stringWithNoLetters_zeroWords),
        cmocka_unit_test(findWordsInString_startsWithSpaceOneWord_oneWord),
        cmocka_unit_test(findWordsInString_twoWordsDividedWithNumbers_twoWords),
        cmocka_unit_test(findWordsInString_OneWordStringEndsWithSpace_OneWord),
        cmocka_unit_test(findWordsInString_ThreeWordsDividedWithDifferentSymbols_ThreeWords),
        cmocka_unit_test(findWordsInString_NormalMessageFrom6words_6Words),
        cmocka_unit_test(findWordsInString_NULL_0words)
    };
	return cmocka_run_group_tests(tests, NULL, NULL);
}

