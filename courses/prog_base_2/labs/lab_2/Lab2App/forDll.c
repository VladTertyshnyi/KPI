#include "forDll.h"

const char * chooseLib(void) {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        fflush(stdin);
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n >>> ");
        scanf("%i", &dllNum);
        fflush(stdin);
        if (dllNum == 1) {
            return "Lab2DLL1.dll";
        } else if (dllNum == 2) {
            return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->check = NULL;
    dyn->reaction = NULL;
    if (NULL != dyn->hLib) {
        dyn->check = (check_cb)GetProcAddress(dyn->hLib, "check");
        dyn->reaction = (reaction_cb)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}
