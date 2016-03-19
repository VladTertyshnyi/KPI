#pragma once

typedef struct city_s city_t;

typedef struct cityList_s cityList_t;

city_t * Module_new_city(char * name, int x, int y);

cityList_t * Module_create_list(int capacity);

void Module_delete_list(cityList_t * selfList);

void Module_set_city(cityList_t * selfList, int index, city_t * selfCity);

void Module_delete_city(cityList_t * selfList, int index);

int Module_get_listSize(cityList_t * selfList);

double Module_get_distance(cityList_t * selfList, int index1, int index2);


