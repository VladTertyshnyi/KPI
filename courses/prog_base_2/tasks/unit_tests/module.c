#include "module.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

//INCAPSUALTION
struct city_s{
    char* name;
    int x;
    int y;
};

struct cityList_s{
    city_t * list;
    int listSize;
    int listCapacity;
};
//CONSTRUCTOR OF CITY_T
city_t * new_city(char * name, int x, int y){
    city_t * selfcity = malloc(sizeof(struct city_s));
    selfcity->name = name;
    selfcity->x = x;
    selfcity->y = y;
    return selfcity;
}

//CONSTRUCTOR
cityList_t * create_list(int capacity){
    cityList_t * selfList = malloc(sizeof(cityList_t));
    selfList->list = malloc(sizeof(city_t) * capacity);
    selfList->listSize = 0;
    selfList->listCapacity = capacity;
    return selfList;
}
//DESTRUCTOR
void delete_list(cityList_t * selfList){
    free(selfList->list);
    free(selfList);
}
// GETS A POINTER TO THE CITY_T AND COPYING IT TO THE LIST
void set_city(cityList_t * selfList, int index, city_t * selfCity){
    if(0 <= index && index <= selfList->listSize && index <= selfList->listCapacity){ //SETTING CITY TO THE INDEX WICH ALLREADY HAVE CITY WILL REWRITE IT WITH NEW CITY
        selfList->list[index] = *selfCity;
        selfList->listSize++;
    }else{
        exit(1);
    }
}

void delete_city(cityList_t * selfList, int index){
    if(0 >= index && index < selfList->listSize){
        int i;
        for(i = selfList->listSize - 1; i > index; i--)
            selfList->list[i - 1] = selfList->list[i];
        selfList->listSize--;
    }else{
    exit(1);
    }
}

int get_listSize(cityList_t * selfList){
    return selfList->listSize;
}

int get_listCapacity(cityList_t * selfList){
    return selfList->listCapacity;
}

double get_distance(cityList_t * selfList, int index1, int index2){
        if(index1<selfList->listSize && index2<selfList->listSize
           && index1 >= 0 && index2 >= 0)
        return sqrt(pow(selfList->list[index2].x - selfList->list[index1].x, 2) +
                    pow(selfList->list[index2].y - selfList->list[index1].y, 2));
        else
            exit(1);
}

