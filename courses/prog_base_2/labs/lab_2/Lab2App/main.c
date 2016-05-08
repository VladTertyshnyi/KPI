#include <stdio.h>
#include <stdlib.h>

#include "forDll.h"


int main()
{
    /* TESTING QUEUE
    queue_t * Queue = queue_newQueue(100);
    queue_add(2, Queue);
    queue_add(3, Queue);
    queue_add(4, Queue);
    queue_add(5, Queue);
    queue_printQueue(Queue);
    queue_del(Queue);
    queue_del(Queue);
    queue_printQueue(Queue);
    int test_1 = queue_returnByInd(Queue, 0);
    printf("Item with index 0 is %d", test_1);
    queue_delQueue(Queue);
    */
    int queue_size = 7;
    queue_t * queue = queue_newQueue(queue_size+1);
    printf("<<< Lab 2 >>>\n");
    const char * dllName = chooseLib();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->check) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->reaction) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    srand(time(NULL));

    puts("Filling the queue...");
    for(int i = 0; i < queue_size; i++)
        queue_add(rand()%25, queue);
    puts("Queue is filled:");
    queue_printQueue(queue);
    puts("Checking and reacting...");
    if (dll->check(queue)){
            dll->reaction();
    }else{
    printf("Everything is good.\n");
    }

    queue_delQueue(queue);



    return 0;
}
