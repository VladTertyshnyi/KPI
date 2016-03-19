#pragma once

typedef struct city_s city_t;

typedef struct cityList_s cityList_t;

city_t * new_city(char * name, int x, int y);

cityList_t * create_list(int capacity);

void delete_list(cityList_t * selfList);

void set_city(cityList_t * selfList, int index, city_t * selfCity);

void delete_city(cityList_t * selfList, int index);

int get_listSize(cityList_t * selfList);

int get_listCapacity(cityList_t * selfList);

double get_distance(cityList_t * selfList, int index1, int index2);


