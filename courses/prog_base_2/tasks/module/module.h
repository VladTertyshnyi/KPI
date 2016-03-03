#pragma once

struct city{
    char* name;
    int x;
    int y;
};


struct cityList_s{
    struct city* list;
    int listSize;
    int listCapacity;
};

typedef struct cityList_s cityList_t;

cityList_t * create_list(int capacity);

typedef struct cityList_s cityList_t;

void set_city(cityList_t * selfList, int index, struct city selfCity);

void delete_city(cityList_t, int index);

int get_listSize(cityList_t * selfList);

double get_distance(cityList_t * selfList, int index1, int index2);


