#include "main.h"

int check(queue_t * Queue){
    if(Queue != NULL){
        int sum = 0;
        for(int i = 0; i < 7; i ++){
            sum += queue_del(Queue);
        }
        return (sum<=40)?1:0;
    }else{
        printf("NULL Error\n");
        exit(-1);
    }
}

void reaction(){
    printf("\nWarning!!!\n");
}


extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
