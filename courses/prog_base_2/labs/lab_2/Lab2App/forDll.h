#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "queue.h"

const char * chooseLib(void);


typedef struct dynamic_s {
    HANDLE hLib;
    check_cb check;
    reaction_cb reaction;
} dynamic_t;

const char * chooseLib(void);
dynamic_t * dynamic_init(const char * dllName);
