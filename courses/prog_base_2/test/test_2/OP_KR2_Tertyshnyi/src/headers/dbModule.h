#pragma once

#include "../headers/director.h"

#define DATABASE_FILE_PATH "src/data/Directors.db"
#define INITIAL_DIRECTORS_AMOUNT 5

#define MAX_DIRECTORS_AMOUNT 100

typedef struct db_s db_t;

// Constructor and destructor.
db_t * database_new(char *dbPath);
void database_delete(db_t * self);

// CRUD functions.
void database_insertDirector(db_t * self, director_t * director);
director_t * database_getDirectorById(db_t * self, int id);
void database_updateDirector(db_t * self, director_t * director, int id);
void database_deleteDirectorById(db_t * self, int id);

// Additional functions.
int database_countDirectors(db_t * self);
int database_filterDirectors(db_t * self, int K, double P, director_t **directorSet, int setMaxLen);
