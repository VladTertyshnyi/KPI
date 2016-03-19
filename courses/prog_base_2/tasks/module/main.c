#include <stdio.h>
#include <stdlib.h>

#include "module.h"

int main()
{
    cityList_t * new_list = Module_create_list(100);
    Module_set_city(new_list, 0, Module_new_city("Kyiv", 0 ,0));
    Module_set_city(new_list, 1, Module_new_city("Rivne", 0, 350));
    printf("The distance is %.2f", Module_get_distance(new_list, 0, 1));
    delete_city(new_list);
    return 0;
}
