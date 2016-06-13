#include "server.h"

int db_countTeachers (sqlite3 * db) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM Teacher;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

teacher_t db_getTeacher (sqlite3_stmt * stmt) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    double rate = sqlite3_column_double(stmt, 2);
    int subjects = sqlite3_column_int(stmt, 3);
    int years = sqlite3_column_int(stmt, 4);
    const unsigned char* birthdate = sqlite3_column_text(stmt, 5);
    teacher_t res = teacher_new(name, birthdate, years, rate, subjects, id);
    return res;
}

char* db_deleteAll (sqlite3 * db) {
    sqlite3_stmt * stmt = NULL;
    char* result;
    int rc;
    const char * sqlQuery = "DELETE FROM Teacher";
    rc = sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    if (rc != SQLITE_OK) {
        sprintf (result, "Not prepared\n");
        sqlite3_finalize(stmt);
        return result;
    }
    rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        sprintf(result, "can't delete teacher!\n");
        sqlite3_finalize(stmt);
        return result;
    }
    sqlite3_finalize(stmt);
    sprintf(result, "delete success");
    return result;
}

teacher_t db_getTeacherById (sqlite3 * db, int id) {
    teacher_t res;
    const char * sqlScript = "SELECT * FROM Teacher where id = ?";
    static sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(db, sqlScript, strlen(sqlScript) + 1, &stmt, 0)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select teacher!\n");
        return NULL;
    }
    else {
        res = db_getTeacher(stmt);
    }

    sqlite3_finalize(stmt);

    return res;
}

int db_deleteTeacherById (sqlite3* db, int id) {
    const char * sqlScript = "DELETE FROM Teacher WHERE id = ?";
    static sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(db, sqlScript, strlen(sqlScript) + 1, &stmt, 0)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't delete teacher!\n");
        return 1;
    }
    sqlite3_finalize(stmt);
    return 0;
}

int db_insertTeacher(sqlite3 * db, char * name, double rate, int subjects, int years, char * birthdate){
    sqlite3_stmt * stmt =  NULL;

    int last = -1;
    const char * sql = "INSERT INTO Teacher (name, rate, subjects, years, birthdate) VALUES (?, ?, ?, ?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, rate);
    sqlite3_bind_int(stmt, 3, subjects);
    sqlite3_bind_int(stmt, 4, years);
    sqlite3_bind_text(stmt, 5, birthdate, strlen(birthdate), SQLITE_TRANSIENT);
    if(SQLITE_OK != rc)
    {
        printf("Not prepared!\n");
    }
    if (SQLITE_DONE != (rc = sqlite3_step(stmt)))
    {
        printf("Not inserted! %i\n", rc);
    }
    last = (int) sqlite3_last_insert_rowid (db);
    sqlite3_finalize(stmt);
    return last;
 }

int db_checkId (sqlite3* db, int id) {
    int curId = -1;
    const char * sqlScript = "SELECT * FROM Teacher";
    static sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(db, sqlScript, strlen(sqlScript) + 1, &stmt, 0)) {
        printf("Not prepared!\n");
    }
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select teachers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            curId = sqlite3_column_int(stmt, 0);
            if (curId == id)
                return 1;
        }
    }
    return 0;
}
