/* 
 * File:   main.cpp
 * Author: Haris
 *
 * Created on October 5, 2013, 7:25 PM
 */


#include <stdlib.h>
#include <sqlite3.h> 
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  /* int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");*/
   return 0;
}

static int callback2(void *NotUsed, int argc, char **argv, char **azColName){
   /*int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");*/
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char const *sql;

   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }
   
   sql="DROP TABLE NETWORKS";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table deleted successfully\n");
   }
   
   
   
   sql = "CREATE TABLE NETWORKS("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NETWORK        TEXT    NOT NULL);";

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
   
   
   
   
   /*
   sqlite3_stmt * stmt;
            
   for(int i=1;i<10000;i++)
   {
       if (sqlite3_prepare( db, "INSERT INTO NETWORKS (ID,NETWORK) VALUES (?,?);", -1, &stmt, NULL )!=SQLITE_OK)
        {
            std::cerr<<sqlite3_errmsg(db);
            return -1;
        }
       stringstream ss;
       unsigned int ip, mask, m=-1;
       ip=random();
       mask=random()%33;
       m<<=32-mask;
       ip&=m;
       ss <<((ip>>24)&0xFF)<<"."<<((ip>>16)&0xFF)<<"."<<((ip>>8)&0xFF)<<"."<<(ip&0xFF)<<"/"<<mask;
       sql=ss.str().c_str();
       
       sqlite3_bind_int(stmt, 1, i);
       sqlite3_bind_text(stmt, 2, sql,strlen(sql), SQLITE_TRANSIENT);
       
       
       
       //fprintf(stderr, "\n%s\n", sql);
        if( sqlite3_step( stmt ) != SQLITE_DONE ){
           fprintf(stderr, "SQL error: %s\n", zErrMsg);
           sqlite3_free(zErrMsg);
           
        }else{
           //fprintf(stdout, "Records created successfully\n");
        }
       sqlite3_finalize(stmt);
        
   }
    */
    
        
        
        
        
        
        
        
        

   sql = "INSERT INTO NETWORKS (ID,NETWORK) "  \
         "VALUES (1, '127.1.1.0/16' ); " \
         "INSERT INTO NETWORKS (ID,NETWORK) "  \
         "VALUES (2, '10.4.200.0/18'); "     \
         "INSERT INTO NETWORKS (ID,NETWORK)" \
         "VALUES (3, '10.5.0.0/16');" \
         "INSERT INTO NETWORKS (ID,NETWORK)" \
         "VALUES (4, '10.0.0.0/8');";

   rc = sqlite3_exec(db, sql, callback2, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
   
   
   sqlite3_close(db);
   return 0;
}


