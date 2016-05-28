#pragma once

#define NAME_LEN 256
#define SURNAME_LEN 256
#define BIRTHDAY_LEN 256

// Private structure.
typedef struct director_s director_t;

// Constructor and destructor.
director_t *director_new_empty();
director_t *director_new(int id, char *name, char *surname, int investments, double years, char *birthDate);
void director_delete(director_t *directorObj);

// Getters.
int director_getId(director_t *directorObj);
char *director_getName(director_t *directorObj);
char *director_getSurname(director_t *directorObj);
int director_getInvestments(director_t *directorObj);
double director_getYears(director_t *directorObj);
char *director_getBirthDate(director_t *directorObj);

// Setters.
void director_setId(director_t *directorObj, int id);
void director_setName(director_t *directorObj, char *name);
void director_setSurname(director_t *directorObj, char *surname);
void director_setInvestments(director_t *directorObj, int investments);
void director_setYears(director_t *directorObj, double years);
void director_setBirthDate(director_t *directorObj, char *birthDate);

// Other functions.
void director_print(director_t * directorObj);
void director_printList(director_t **directorSetObj, int dirCount);
