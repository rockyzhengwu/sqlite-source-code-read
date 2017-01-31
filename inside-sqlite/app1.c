#include <stdio.h>
#include "sqlite3.h"

int main(void){
    sqlite3* db = 0;
    sqlite3_stmt* stmt = 0;
    int retcode;
    // create a databse connection
    retcode = sqlite3_open("test.db", &db);

    if(retcode != SQLITE_OK){
        printf("%d,%d\n", retcode,SQLITE_OK);
        sqlite3_close(db);
        fprintf(stderr, "Could not open testdb\n");
        return retcode;
    }

    //sqlite3_prepare compile sql statement. referred to as prepare statement
    retcode = sqlite3_prepare(db, "select SID from Students order by SID", -1, &stmt, 0);

    if(retcode!=SQLITE_OK){
        sqlite3_close(db);
        fprintf(stderr, "Cound not execute Select\n");
        return retcode;
    }
    // sqlite3_step execute bytecode program
    while(sqlite3_step(stmt)==SQLITE_ROW){
        // retrieve the value
        int i= sqlite3_column_int(stmt, 0);
        printf("SID = %d\n", i);
    }
    // destroys the prepared
    sqlite3_finalize(stmt);
    // close connection
    sqlite3_close(db);
    return SQLITE_OK;
}
