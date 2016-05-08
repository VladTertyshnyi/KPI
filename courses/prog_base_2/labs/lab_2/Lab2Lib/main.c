#include "queue.h"
#include <stddef.h>

struct queue_s {
    int * array;
    int f;
    int r;
    int max_size;
};

queue_t * queue_newQueue(int QUEUE_MAX_SIZE){
    queue_t * selfQueue = malloc(sizeof(queue_t));
    selfQueue->array = malloc(sizeof(int)* QUEUE_MAX_SIZE);
    selfQueue->max_size = QUEUE_MAX_SIZE;
    selfQueue->f=0;
    selfQueue->r=0;
    return selfQueue;
};

void queue_delQueue(queue_t * selfQueue){
    if(selfQueue != NULL){
    free(selfQueue->array);
    free(selfQueue);
    }
    else return;
}
int queue_isEmpty (queue_t * selfQueue){
    if(selfQueue != NULL){
    return selfQueue->f==selfQueue->r;
    }else{
    printf("NULL POINTER");
    exit(-1);
    }
}
int queue_size (queue_t * selfQueue){
    if(selfQueue != NULL){
    return (selfQueue->max_size - selfQueue->f + selfQueue->r) % selfQueue->max_size;
    }else{
    printf("NULL POINTER");
    exit(-1);
    }
}
void queue_add (int value, queue_t * selfQueue){
    if(selfQueue != NULL){
    if(queue_size(selfQueue) == selfQueue->max_size - 1){
        printf("Queue is FULL!");
        exit(-1);
    }
    selfQueue->array[selfQueue->r] = value;
    selfQueue->r = (selfQueue->r + 1)%selfQueue->max_size;
    }else{
    printf("NULL POINTER");
    exit(-1);
    }
}

int queue_returnByInd(queue_t * selfQueue, int index){
    return (selfQueue->array[selfQueue->f + index]);
}
int queue_del(queue_t * selfQueue){
    if(selfQueue != NULL){
    if(queue_isEmpty(selfQueue)){
        printf("Queue is empty. \n");
        return;
    }else{
        int temp = selfQueue->array[selfQueue->f];
        selfQueue->array[selfQueue->f] = -1;
        selfQueue->f = (selfQueue->f + 1) % selfQueue->max_size;
        return temp;
    }
    }else{
    printf("NULL POINTER");
    exit(-1);
    }
}

void queue_printQueue(queue_t * selfQueue){
    if(selfQueue != NULL){
    for(int i = 0; i <= queue_size(selfQueue) -1; i++){
        printf("%i. - %d\n", i+1, selfQueue->array[selfQueue->f+i]);
    }
    }else{
    printf("NULL POINTER");
    exit(-1);
    }
}
