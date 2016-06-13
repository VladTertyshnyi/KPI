#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

#define MAX_NAME 100
#define MAX_DATE 11

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct teacher_s  * teacher_t;

teacher_t teacher_new (char* name, char* birthdate, int salary, double rate, int subjects, int id);
void teacher_free (teacher_t self);
char* teacher_getName (teacher_t self);
char* teacher_getBirthdate (teacher_t self);
int teacher_getYears (teacher_t self);
double teacher_getRate (teacher_t self);
int teacher_getSubjects (teacher_t self);
int teacher_getId (teacher_t self);
list_t * teacher_toList (teacher_t arr[], int size);


#endif // TEACHER_H_INCLUDED
