#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
extern char *getenv();
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s is %s\n", data, argv[i] ? argv[i] : "NULL");
   }
   //printf("\n");
   return 0;
}
 
int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data;
 
   /* Open database */
   rc = sqlite3_open("/data/db/test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }
 
   /* Create SQL statement */
   char sqlbuf[500];
   char *type;
   type=getenv("CGI_TYPE");
   printf("Content-type: text/html\n\n");
   //type="wifi_name";
   if(!type){
       printf("type is empty!");
       exit(0);
   }
   memset(sqlbuf,sizeof(sqlbuf),0);
   snprintf(sqlbuf,500,"select config_value from config where config_name='%s'",type);
   sql = sqlbuf;
   //printf("%s",sqlbuf);
   data=type;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
