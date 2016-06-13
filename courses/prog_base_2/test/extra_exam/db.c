#include "database.h"

struct db_s{
    sqlite3 * db;
};

db_t * db_new(char *dbPath){
    db_t * out = (db_t *) malloc(sizeof(struct db_s));
    int returnCode = sqlite3_open(dbPath, &out->db);
    if(returnCode != SQLITE_OK){
            puts("Cannot open database.\n");
    return (out);
}

void db_delete(db_t * self){
    int returnCode = sqlite3_close(self->db);
    if(returnCode != SQLITE_OK) puts("Cannot close database.\n");
    free(self);
}


int db_count(db_t * self){
    sqlite3_stmt * stmt = NULL;
    const char *sqlCountCommand = "SELECT COUNT(*) FROM Student";
    int returnCode = 0;
    int teachersCount = 0;
    returnCode = sqlite3_prepare_v2(self->db, sqlCountCommand, strlen(sqlCountCommand) + 1, &stmt, NULL);
    if(returnCode!= SQLITE_OK)
    puts("Error preparing statement by COUNT(*) command.\n");

    returnCode = sqlite3_step(stmt);

    if(returnCode!=SQLITE_ERROR)
    puts("Error by stepping with COUNT(*) command.\n");
    teachersCount = sqlite3_column_int(stmt, 0);
    return (teachersCount);
}

void db_addStudent(db_t * db){
    char * Surname, Name, MiddleName, Birthdate, Hometown;
    int Document;
    puts("Adding student to Table 'Student':");
    puts("Enter Surname:");
    gets(Surname);
    puts("Enter Name:");
    gets(Name);
    puts("Enter MiddleName:");
    gets(Birthdate);
    puts("Enter Birthdate:");
    gets(Hometown);
    puts("Enter Hometown:");
    gets(Hometown);
    puts("Enter zachetka's number:");
    scanf("%d", &Document);

    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "INSERT INTO Student ('Surname','Name','MiddleName','Birthdate', 'Hometown', 'Document') VALUES (?,?,?,?,?,?);";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery) + 1,&stmt,NULL);

    sqlite3_bind_text(stmt,1,Surname,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,Name,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,MiddleName,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,Birthdate,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,5,Hometown,-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,6,Document);

    int rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
    {
        puts("ERROR inserting student");

    }else
        {
            sqlite3_finalize(stmt);
        }


}
