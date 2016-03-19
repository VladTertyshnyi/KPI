#include <stdio.h>
#include <stdlib.h>

#include "module.h"

int main()
{
    cityList_t * new_list = create_list(100);
    set_city(new_list, 0, new_city("Kyiv", 0 ,0));
    set_city(new_list, 1, new_city("Rivne", 0, 350));
    printf("The distance is %.2f", get_distance(new_list, 0, 1));
    return 0;
}
