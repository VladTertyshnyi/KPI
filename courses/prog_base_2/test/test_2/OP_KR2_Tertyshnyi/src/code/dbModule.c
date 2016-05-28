#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../headers/sqlite3.h"
#include "../headers/dbModule.h"
#include "../headers/director.h"

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#define MAX_DB_PATHSIZE 1024

//----------------------------------->>> Private structure <<<-----------------------------------

typedef struct db_s
{
    char dbPath[MAX_DB_PATHSIZE];
    sqlite3 *db;
} db_t;

//----------------------------------->>> Private methods <<<-----------------------------------

static void errorHandler_NotEqual(int returnCode, int errorToCmp, const char *errorMsg)
{
    if(errorToCmp != returnCode)
    {
        fprintf(stderr, "ERROR: [%s].\n", errorMsg);
        exit(1);
    }
}

static void errorHandler_Equal(int returnCode, int errorToCmp, const char *errorMsg)
{
    if(errorToCmp == returnCode)
    {
        fprintf(stderr, "ERROR: [%s].\n", errorMsg);
        exit(1);
    }
}

static void _directorFill(sqlite3_stmt * stmt, director_t *director)
{
    // Get data from the database.
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char *name = sqlite3_column_text(stmt, 1);
    const unsigned char *surname = sqlite3_column_text(stmt, 2);
    int investments = sqlite3_column_int(stmt, 3);
    int years = sqlite3_column_double(stmt, 4);
    const unsigned char *birthDate = sqlite3_column_text(stmt, 5);
    // Paste data into director structure.
    director_setId(director, id);
    director_setName(director, (char *)name);
    director_setSurname(director, (char *)surname);
    director_setInvestments(director, investments);
    director_setYears(director, years);
    director_setBirthDate(director, (char *)birthDate);
}

//----------------------------------->>> Public methods <<<-----------------------------------

db_t * database_new(char *dbPath)
{
    db_t * out = (db_t *) malloc( sizeof ( struct db_s ) );
    sprintf(out->dbPath, "%s", dbPath);
    int returnCode = sqlite3_open(dbPath, &out->db);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Cannot open database.");
    return (out);
}

void database_delete(db_t * self)
{
    int returnCode = sqlite3_close(self->db);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Cannot close database.");
    free(self);
}

void database_insertDirector(db_t * self, director_t * director)
{
    sqlite3_stmt *stmt = NULL;
    const char *sqlInsertCommand = "INSERT INTO Directors ('Name', 'Surname', 'Investments', 'Years', 'Birthdate') VALUES (?,?,?,?,?);";
    int returnCode = 0;

    // Prepare statement for inserting data into db.
    returnCode = sqlite3_prepare_v2(self->db, sqlInsertCommand, strlen(sqlInsertCommand) + 1, &stmt, NULL);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Sql insert command wasn`t prepared.");
    // Bind unknown fields.
    sqlite3_bind_text(stmt, 1, director_getName(director), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, director_getSurname(director), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, director_getInvestments(director));
    sqlite3_bind_double(stmt, 4, director_getYears(director));
    sqlite3_bind_text(stmt, 5, director_getBirthDate(director), -1, SQLITE_STATIC);
    // Paste data into database.
    returnCode = sqlite3_step(stmt);
    errorHandler_NotEqual(returnCode, SQLITE_DONE, "Data wasn`t inserted.");
    // Director id was empty (0). Will be filled now.
    director_setId(director, (int)sqlite3_last_insert_rowid(self->db));
    sqlite3_reset(stmt);
}

director_t * database_getDirectorById(db_t * self, int id)
{
    director_t *out = director_new_empty();
    sqlite3_stmt * stmt = NULL;
    const char *sqlGetCommand = "SELECT * FROM Directors WHERE Id=?;";
    int returnCode = 0;

    // Prepare statement for selecting data from db.
    sqlite3_prepare_v2(self->db, sqlGetCommand, strlen(sqlGetCommand) + 1, &stmt, NULL);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Sql select command wasn`t prepared.");
    // Bind unknown 'id' field.
    sqlite3_bind_int(stmt, 1, id);
    // Step into database.
    returnCode = sqlite3_step(stmt);
    // If certain director wasn`t found - return an empty Director object.
    if(returnCode != SQLITE_ROW)
    {
        return (out);
    }
    // Paste data into director structure, that will be returned.
    director_setId(out, id);
    director_setName(out, (char *)sqlite3_column_text(stmt, 1));
    director_setSurname(out, (char *)sqlite3_column_text(stmt, 2));
    director_setInvestments(out, sqlite3_column_int(stmt, 3));
    director_setYears(out, sqlite3_column_double(stmt, 4));
    director_setBirthDate(out, (char *)sqlite3_column_text(stmt, 5));

    sqlite3_reset(stmt);
    return (out);
}

void database_updateDirector(db_t * self, director_t * director, int id)
{
    sqlite3_stmt *stmt = NULL;
    const char *sqlUpdateCommand = "UPDATE Directors SET "
                                   "Name=?,"
                                   "Surname=?,"
                                   "Investments=?,"
                                   "Years=?,"
                                   "Birthdate=? "
                                   "WHERE Id=?;";
    int returnCode = 0;

    returnCode = sqlite3_prepare_v2(self->db, sqlUpdateCommand, strlen(sqlUpdateCommand) + 1, &stmt, NULL);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Error preparing update command.");

    sqlite3_bind_text(stmt, 1, director_getName(director), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, director_getSurname(director), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, director_getInvestments(director));
    sqlite3_bind_double(stmt, 4, director_getYears(director));
    sqlite3_bind_text(stmt, 5, director_getBirthDate(director), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, id);

    sqlite3_step(stmt);
    sqlite3_reset(stmt);
}

void database_deleteDirectorById(db_t * self, int id)
{
    sqlite3_stmt *stmt = NULL;
    const char *sqlDeleteCommand = "DELETE FROM Directors WHERE Id=?";
    int returnCode = 0;

    returnCode = sqlite3_prepare_v2(self->db, sqlDeleteCommand, strlen(sqlDeleteCommand) + 1, &stmt, NULL);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Error preparing delete command.");

    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_reset(stmt);
}

int database_countDirectors(db_t * self)
{
    sqlite3_stmt * stmt = NULL;
    const char *sqlCountCommand = "SELECT COUNT(*) FROM Directors";
    int returnCode = 0;
    int studentsCount = 0;

    // Prepare select statement.
    returnCode = sqlite3_prepare_v2(self->db, sqlCountCommand, strlen(sqlCountCommand) + 1, &stmt, NULL);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Error preparing statement by COUNT(*) command.");
    // Prepare stepping function.
    returnCode = sqlite3_step(stmt);
    errorHandler_Equal(returnCode, SQLITE_ERROR, "Error by stepping with COUNT(*) command.");
    // Get amount of students in table.
    studentsCount = sqlite3_column_int(stmt, 0);

    return (studentsCount);
}

int database_filterDirectors(db_t * self, int K, double P, director_t **directorSet, int setMaxLen)
{
    sqlite3_stmt *stmt = NULL;
    const char *sqlCommand = "SELECT * FROM Directors WHERE Investments < ? AND Years > ?;";
    int returnCode = 0;
    int directorSetIndex = 0;

    // Prepare select statement.
    sqlite3_prepare_v2(self->db, sqlCommand, strlen(sqlCommand) + 1, &stmt, NULL);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Error preparing statement by SELECT * command.");
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_double(stmt, 2, P);

    // Go through database and find students by statement.
    while(TRUE)
    {
        int returnCode2 = sqlite3_step(stmt);
        if(returnCode2 == SQLITE_ERROR)
        {
            fprintf(stderr, "Can`t select directors.\n");
            exit(1);
        }
        if(SQLITE_DONE == returnCode2)
        {
            // If function reached end of the table.
            break;
        }
        else
        {
            _directorFill(stmt, directorSet[directorSetIndex]);
            directorSetIndex++;
        }
    }
    returnCode = sqlite3_finalize(stmt);
    errorHandler_NotEqual(returnCode, SQLITE_OK, "Error destroying statement.");

    // Return how much students belong to searched query.
    return (directorSetIndex);
}
