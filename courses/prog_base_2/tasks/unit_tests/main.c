
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "module.h"


//unit-test functions


//�������� ���� �� ���� ����� ����� ������ �������, ���� ���� �� �� ������ ���� ����
const void setCity_oneCity_sizeOne(void** state)
{
    cityList_t * cityList = create_list(1);
    set_city(cityList, 0, new_city("test_name", 1, 2));
    assert_int_equal(get_listSize(cityList), 1);
    delete_list(cityList);
}
//�������� ���� �� ���� ����� ����� ���� ����� ���� ���� �� �� ������ ��� ����
const void setCity_twoCities_sizeTwo(void** state)
{
    cityList_t * cityList = create_list(5);
    set_city(cityList, 0, new_city("test_name", 1, 2));
    set_city(cityList, 0, new_city("test_name1", 0, 2));
    assert_int_equal(get_listSize(cityList), 2);
    delete_list(cityList);
}
//�������� ���� �� ���� ����� ����� ������ ���� �� ���� �� �� ������� �������� ����
const void CreateList_Void_ZeroSize(void** state)
{
    cityList_t * cityList = create_list(1);
    assert_int_equal(get_listSize(cityList), 0);
    delete_list(cityList);
}
//�������� ���� �� ���� �������� ������������ ����� ������
const void CreateList_Capacity5_listCapacity5(void** state)
{
    int testCapacity = 5;
    cityList_t * cityList = create_list(testCapacity);
    assert_int_equal(get_listCapacity(cityList), testCapacity);
    delete_list(cityList);
}
//�������� ���� �� ���� �������� ������� �� ������ �� �������� ������� � ������������
const void getDistance_twoCities_Distance10(void** state)
{
    cityList_t * cityList = create_list(5);
    set_city(cityList, 0, new_city("test_name", 0, 0));
    set_city(cityList, 1, new_city("test_name1", 0, 10));
    assert_true(get_distance(cityList, 0, 1) == 10);
    delete_list(cityList);
}
//�������� ���� �� ���� ������������ ����� ������ ���� ���� �� �� �������� ���� � ������
const void DeleteCity_twoCitiesOneCity_ChkingSize(void** state)
{
    cityList_t * cityList = create_list(5);
    set_city(cityList, 0, new_city("test_name", 0, 0));
    set_city(cityList, 1, new_city("test_name1", 0, 10));
    assert_true(get_listSize(cityList) == 2);
    delete_city(cityList, 1);
    assert_true(get_listSize(cityList) == 1);
    delete_list(cityList);
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
