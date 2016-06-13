#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "train.h"

int main()
{
    //task_UnitTests();
    //task_module();

    return 0;
}

void task_UnitTests(){
    char  * string = "  This4 str ing 1235  #!!$";
    printf("Using example:\n/%s/ has %d words. \nRunning tests:\n", string, findWordsInString(string));
    findWordsInString_runTests();
}

void task_module(){
    train_t train1 = train_new();

    train_addWagon(train1, CARGO);
    train_print(train1);
    train_addWagon(train1, CARGO);
    train_print(train1);
    train_go(train1);
    train_addWagon(train1, PASS);
    train_print(train1);
    train_stop(train1);
    train_addWagon(train1, PASS);
    train_print(train1);
    train_addWagon(train1, CARGO);
    train_print(train1);

    train_addWagon(train1, PASS);
    train_addWagon(train1, PASS);
    train_addWagon(train1, PASS);
    train_print(train1);
    train_addWagon(train1, CARGO);
    train_addWagon(train1, CARGO);
    train_addWagon(train1, CARGO);
    train_go(train1);

    train_popWagon(train1);
    train_print(train1);
    train_go(train1);
    train_popWagon(train1);
    train_print(train1);
    train_stop(train1);
    train_popWagon(train1);
    train_print(train1);

    train_clear(train1);
}
