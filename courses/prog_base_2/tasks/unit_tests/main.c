
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "module.h"


//unit-test functions


//Перевірка того чи буде рівним розмір списку одиниці, після того як ми додамо одне місто
const void setCity_oneCity_sizeOne(void** state)
{
    cityList_t * cityList = Module_create_list(1);
    Module_set_city(cityList, 0, Module_new_city("test_name", 1, 2));
    assert_int_equal(Module_get_listSize(cityList), 1);
    Module_delete_list(cityList);
}
//Перевірка того чи буде рівним розмір міста двійці після того як ми додамо два міста
const void setCity_twoCities_sizeTwo(void** state)
{
    cityList_t * cityList = Module_create_list(5);
    Module_set_city(cityList, 0, Module_new_city("test_name", 1, 2));
    Module_set_city(cityList, 0, Module_new_city("test_name1", 0, 2));
    assert_int_equal(Module_get_listSize(cityList), 2);
    Module_delete_list(cityList);
}
//Перевірка того чи буде рівним розмір списку нулю до того як ми почнемо додавати міста
const void CreateList_Void_ZeroSize(void** state)
{
    cityList_t * cityList = Module_create_list(1);
    assert_int_equal(Module_get_listSize(cityList), 0);
    Module_delete_list(cityList);
}
//Перевірка того чи вірно задається максимальний розмір списку
const void CreateList_Capacity5_listCapacity5(void** state)
{
    int testCapacity = 5;
    cityList_t * cityList = Module_create_list(testCapacity);
    assert_int_equal(Module_get_listCapacity(cityList), testCapacity);
    Module_delete_list(cityList);
}
//Перевірка того чи вірно рахується відстань між містами на простому прикладі з координатами
const void getDistance_twoCities_Distance10(void** state)
{
    cityList_t * cityList = Module_create_list(5);
    Module_set_city(cityList, 0, Module_new_city("test_name", 0, 0));
    Module_set_city(cityList, 1, Module_new_city("test_name1", 0, 10));
    assert_true(Module_get_distance(cityList, 0, 1) == 10);
    Module_delete_list(cityList);
}
//Перевірка того чи буде зменшуватись розмір списку після того як ми видалимо місто зі списку
const void DeleteCity_twoCitiesOneCity_ChkingSize(void** state)
{
    cityList_t * cityList = Module_create_list(5);
    Module_set_city(cityList, 0, Module_new_city("test_name", 0, 0));
    Module_set_city(cityList, 1, Module_new_city("test_name1", 0, 10));
    assert_true(Module_get_listSize(cityList) == 2);
    Module_delete_city(cityList, 1);
    assert_true(Module_get_listSize(cityList) == 1);
    Module_delete_list(cityList);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(setCity_oneCity_sizeOne),
        cmocka_unit_test(CreateList_Void_ZeroSize),
        cmocka_unit_test(CreateList_Capacity5_listCapacity5),
        cmocka_unit_test(setCity_twoCities_sizeTwo),
        cmocka_unit_test(getDistance_twoCities_Distance10),
        cmocka_unit_test(DeleteCity_twoCitiesOneCity_ChkingSize)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
