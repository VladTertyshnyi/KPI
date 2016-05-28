#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../headers/director.h"

//----------------------------------->>> Private structure <<<-----------------------------------
struct director_s
{
    int id;
    char name[NAME_LEN];
    char surname[SURNAME_LEN];
    int investments;
    double years;
    char birthDate[BIRTHDAY_LEN];
};

//----------------------------------->>> Public methods <<<-----------------------------------

director_t *director_new_empty()
{
    director_t *out = (director_t *) malloc ( sizeof ( struct director_s ) );
    director_setId(out, 0);
    director_setName(out, "Noname");
    director_setSurname(out, "Nosurname");
    director_setInvestments(out, 0);
    director_setYears(out, 0.0);
    director_setBirthDate(out, "1970-01-01");
    return (out);
}

director_t *director_new(int id, char *name, char *surname, int investments, double years, char *birthDate)
{
    director_t *out = (director_t *) malloc ( sizeof ( struct director_s ) );
    director_setId(out, id);
    director_setName(out, name);
    director_setSurname(out, surname);
    director_setInvestments(out, investments);
    director_setYears(out, years);
    director_setBirthDate(out, birthDate);
    return (out);
}

void director_delete(director_t *directorObj)
{
    free ( directorObj );
}

int director_getId(director_t *directorObj)
{
    return (directorObj->id);
}

char *director_getName(director_t *directorObj)
{
    return (directorObj->name);
}

char *director_getSurname(director_t *directorObj)
{
    return (directorObj->surname);
}

int director_getInvestments(director_t *directorObj)
{
    return (directorObj->investments);
}

double director_getYears(director_t *directorObj)
{
    return (directorObj->years);
}

char *director_getBirthDate(director_t *directorObj)
{
    return (directorObj->birthDate);
}

void director_setId(director_t *directorObj, int id)
{
    directorObj->id = id;
}

void director_setName(director_t *directorObj, char *name)
{
    sprintf(directorObj->name, "%s", name);
}

void director_setSurname(director_t *directorObj, char *surname)
{
    sprintf(directorObj->surname, "%s", surname);
}

void director_setInvestments(director_t *directorObj, int investments)
{
    directorObj->investments = investments;
}

void director_setYears(director_t *directorObj, double years)
{
    directorObj->years = years;
}

void director_setBirthDate(director_t *directorObj, char *birthDate)
{
    sprintf(directorObj->birthDate, "%s", birthDate);
}

void director_print(director_t * directorObj)
{
    printf("Name: %s\n"
           "Surname: %s\n"
           "Investments: %i\n"
           "Years: %.2f\n"
           "Birthdate: %s\n",
           directorObj->name,
           directorObj->surname,
           directorObj->investments,
           directorObj->years,
           directorObj->birthDate);
}

void director_printList(director_t **directorSetObj, int dirCount)
{
    for (int i = 0; i < dirCount; i++)
    {
        printf("%d.", i+1);
        director_print(directorSetObj[i]);
        puts("");
    }
}
