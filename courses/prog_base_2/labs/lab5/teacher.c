#include "teacher.h"

struct teacher_s {
    char name[MAX_NAME];
    char birthdate[MAX_DATE];
    int years;
    double rate;
    int subjects;
    int id;
};

teacher_t teacher_new (char* name, char* birthdate, int years, double rate, int subjects, int id) {
    teacher_t self = malloc (sizeof(struct teacher_s));
    memset(self->name, 0, MAX_NAME);
    strncpy(self->name, name, MAX_NAME);
    memset(self->birthdate, 0, MAX_DATE);
    strncpy(self->birthdate, birthdate, MAX_DATE);
    self->years = years;
    self->rate = rate;
    self->subjects = subjects;
    self->id = id;
    return self;
}

void teacher_free (teacher_t self) {
    free(self);
}

char* teacher_getName (teacher_t self) {
    return self->name;
}

char* teacher_getBirthdate (teacher_t self) {
    return self->birthdate;
}

int teacher_getYears (teacher_t self) {
    return self->years;
}

double teacher_getRate (teacher_t self) {
    return self->rate;
}

int teacher_getSubjects (teacher_t self) {
    return self->subjects;
}

int teacher_getId (teacher_t self) {
    return self->id;
}

list_t * teacher_toList (teacher_t arr[], int size) {
    list_t * teacherList = list_new ();
    if (size <= 0) {
        printf("Teacher array size invalid\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        list_insertLast(teacherList, (void*)arr[i]);
    }
    return teacherList;
}


