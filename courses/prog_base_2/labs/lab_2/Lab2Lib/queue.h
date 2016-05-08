#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct queue_s queue_t;

typedef int(*check_cb)(queue_t * selfQueue);
typedef void(*reaction_cb)();
queue_t * queue_newQueue(int QUEUE_MAX_SIZE);
void queue_delQueue(queue_t * selfQueue);

void queue_add (int value, queue_t * selfQueue);
int queue_returnByInd(queue_t * selfQueue, int index);
int queue_del (queue_t * selfQueue);
int queue_size (queue_t * selfQueue);
int queue_isEmpty(queue_t * selfQueue);
int queue_front (queue_t * selfQueue);
void queue_printQueue(queue_t * selfQueue);



#endif
