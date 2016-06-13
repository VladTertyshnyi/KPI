#include "train.h"

struct train_s{
    wagon_t * wagons;
    STATE state;
    int cargoCount;
    int passCount;
};

struct wagon_s{
    TYPE type;
};

train_t train_new(){
    train_t self = malloc(sizeof(struct train_s));
    self->state = STOP;
    self->wagons = malloc(sizeof(struct wagon_s));
    self->cargoCount = 0;
    self->passCount = 0;
    return self;
}

void train_clear(train_t self){
    free(self->wagons);
    free(self);
}

wagon_t wagon_new(TYPE type){
    wagon_t self = malloc(sizeof(struct wagon_s));
    self->type = type;
    return self;
}

void train_addWagon(train_t train, TYPE type){
    if(train->state == GOING){puts("Can't add wagon to train while it's going."); return;}
    wagon_t wagon = wagon_new(type);
    if(type == CARGO)train->cargoCount++;else train->passCount++;
    int size = train->cargoCount + train->passCount;
    train->wagons = realloc(train->wagons, sizeof(struct wagon_s)*size);
    train->wagons[size-1] = wagon;
    puts("Wagon successfully added.");
}

void train_popWagon(train_t train){
    if(train->state == GOING){puts("Can't pop wagons while train's going."); return;}
    if(train->cargoCount + train->passCount == 0){puts("Can't pop wagons - train is empty."); return;}
    int size = train->cargoCount + train->passCount;
    if(train->wagons[size-1]->type == CARGO)train->cargoCount--;else train->passCount--;
    size = train->cargoCount + train->passCount;
    if(size == 0)size = 1;
    train->wagons = realloc(train->wagons, sizeof(struct wagon_s)*size);
    puts("Wagon successfully popped.");
}

void train_print(train_t train){
    puts("\nThere are wagons added to your train:");
    int size = train->cargoCount + train->passCount;
    for(int i = 0; i < size; i++){
        if(train->wagons[i]->type == CARGO){
            printf("%d. Cargo type wagon;\n", i);
        }else{
            printf("%d. Passenger type wagon;\n", i);
        }
    }
    puts("");
}

int train_getSits(train_t train){
    return train->passCount * PASS_WAGON_SIT_PLACES;
}

void train_go(train_t train){
    if(train->state == GOING){puts("Cant start the train because it's already going."); return;}
    int weight = train->passCount * PASS_WAGON_WEIGHT + train->cargoCount * CARGO_WAGON_WEIGHT;
    if(weight > 100){
        puts("Cant start the train because it's weight is to high.");
        return;
        }
    train->state = GOING;
    puts("Train was started.");
}

void train_stop(train_t train){
    if(train->state == STOP){puts("Cant stop the train because it's already stopped."); return;}
    train->state = STOP;
    puts("Train was stopped.");
}

void train_printCargo(train_t train){
    puts("\nThere are cargo wagons added to your train:");
    int size = train->cargoCount + train->passCount;
    for(int i = 0; i < size; i++){
        if(train->wagons[i]->type == CARGO)
            printf("%d. Cargo type wagon;\n", i);
    }
}

void train_printPass(train_t train){
    puts("\nThere are passenger wagons added to your train:");
    int size = train->cargoCount + train->passCount;
    for(int i = 0; i < size; i++){
        if(train->wagons[i]->type == PASS){
            printf("%d. Passenger type wagon;\n", i);
        }
    }
}
