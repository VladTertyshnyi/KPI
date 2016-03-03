#include "module.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>





cityList_t * create_list(int capacity){
    cityList_t * selfList = malloc(sizeof(struct cityList_s));
    selfList->list=malloc(sizeof(struct city)* capacity);
    selfList->listSize = 0;
    return selfList;
}

void set_city(cityList_t * selfList, int index, struct city selfCity){
    if(index<selfList->listCapacity){
        selfList->list[index] = selfCity;
        selfList->listSize++;
    }else{
        exit(1);
    }
}

void delete_city(cityList_t selfList, int index){
    char* empty_name = "empty_city";
    if(index<selfList.listCapacity){
        strcpy(selfList.list[index].name, empty_name);
        selfList.list[index].x = 0;
        selfList.list[index].y = 0;
        selfList.listSize--;
    }else{
    exit(1);
    }
}

int get_listSize(cityList_t * selfList){
    return selfList->listSize;
}

double get_distance(cityList_t * selfList, int index1, int index2){
        if(index1<selfList->listCapacity && index2<selfList->listCapacity)
        return sqrt(pow(selfList->list[index2].x - selfList->list[index1].x, 2) +
                    pow(selfList->list[index2].y-selfList->list[index1].y, 2));
        else
            exit(1);
}

