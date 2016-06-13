#ifndef TRAIN_H_INCLUDED
#define TRAIN_H_INCLUDED
#define CARGO_WAGON_WEIGHT 20
#define PASS_WAGON_WEIGHT 5
#define TRAIN_MAX_WEIGHT 100
#define PASS_WAGON_SIT_PLACES 80

#include <stdio.h>
#include <stdlib.h>

enum STATE_E
{
    GOING,
    STOP
};

enum TYPE_E
{
    PASS,
    CARGO
};

typedef struct train_s * train_t;
typedef struct wagon_s * wagon_t;
typedef enum STATE_E STATE;
typedef enum TYPE_E TYPE;

train_t train_new();
void train_clear(train_t self);
wagon_t wagon_new(TYPE type);
void train_addWagon(train_t train, TYPE type);
void train_popWagon(train_t train);
void train_print(train_t train);
int train_getSits(train_t train);
void train_go(train_t train);
void train_stop(train_t train);
void train_printCargo(train_t train);
void train_printPass(train_t train);

#endif // TRAIN_H_INCLUDED
