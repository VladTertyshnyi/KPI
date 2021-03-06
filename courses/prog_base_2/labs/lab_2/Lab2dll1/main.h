#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>




#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int DLL_EXPORT check(queue_t * Queue);
void DLL_EXPORT reaction();

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
