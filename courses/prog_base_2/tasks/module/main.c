#include <stdio.h>
#include <stdlib.h>

#include "module.h"

int main()
{
    cityList_t * test_list = create_list(100);
    struct city test_city1 = {"test_city1", 10, 11};
    set_city(test_list, 0, test_city1);
    int mount = get_listSize(test_list);
    printf("%i\n", mount);
    struct city test_city2 = {"test_city2", 13, 15};
    set_city(test_list, 1, test_city2);
    double test_distance = get_distance(test_list, 0, 1);
    printf("%f ", test_distance);

    return 0;
}
