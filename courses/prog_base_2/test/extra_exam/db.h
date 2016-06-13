#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct db_s db_t;

db_t * db_new(char *);
void db_delete(db_t *);
int db_count(db_t * self);
void db_delete(db_t * self);

#endif // DB_H_INCLUDED
