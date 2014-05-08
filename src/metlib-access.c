
/*
**  functions/routines for opening and checking databases
*/

#include <stdio.h>
#include "metlib.h"

/*
**  Global database handler struct
*/
DB_Handle_Struct db_handle;

/*
**  local function prototpes
*/
int sql_db_exists(char *);


/*
**  Open a database or file that contains meterological data for the
**   model.  Return the filehandle (if one exists) and error status
*/
int metlib_open( int type, char* filename, int *error )
{
   sqlite3 *sq3_db_handle;
   int sql_error = 0;

   switch ( type )
   {
      case FLATFILE:
                db_handle.fd = fopen( filename, "r");
                if ( db_handle.fd == NULL ) {
                   fprintf(stderr,"ERROR: Unable to open met file : %s\n", 
                              filename);
                }
                *error = 0;
                return(1);
             break;

      case SQLITEDB:
                fprintf(stderr,"opening sqlite database (%s).\n", filename);
                if ( sql_db_exists( filename ) )
                {
                   sql_error = sqlite3_open( filename, &(db_handle.sq3_db) );
                   /*
                   **  check sql_error result.  
                   **    errors are defined in sqlite3.h
                   */
                   switch (sql_error)
                   {
                      case SQLITE_OK:
                         fprintf(stderr," database %s opened\n", filename);
                         break;
                      case SQLITE_ERROR:
                         fprintf(stderr," ERROR: error or missing database\n");
                         sqlite3_close(db_handle.sq3_db);
                         return(-1);
                         break;
                      case SQLITE_PERM:
                         fprintf(stderr," ERROR: denied database access\n");
                         sqlite3_close(db_handle.sq3_db);
                         return(-1);
                         break;
                      case SQLITE_LOCKED:
                         fprintf(stderr," ERROR: locked database access\n");
                         sqlite3_close(db_handle.sq3_db);
                         return(-1);
                         break;
                   }
                   return(1);
                }
                else {
                   fprintf(stderr," ERROR: database file missing.\n");
                   return(-1);
                }
             break;

      case MONGODB:
                *error = -1;
                return(-1);
             break;

      default:
                fprintf(stderr,"Unknown database/file format requested.\n");
                *error = -1;
                return(-1);
             break;
   } /* end switch */
}


int metlib_close( int type )
{

   switch ( type )
   {
      case FLATFILE:
                fclose(db_handle.fd);
                return(0);
             break;

      case SQLITEDB:
                fprintf(stderr,"closing sqlite database.\n" );
                sqlite3_close( db_handle.sq3_db );
                return(0);
             break;

      case MONGODB:
                return(-1);
             break;

      default:
                fprintf(stderr,"Unknown database/file format requested.\n");
                return(-1);
             break;
   } /* end switch */
}

/*
** Test for database existance
*/
int sql_db_exists(char *filename)
{
   sqlite3 *db;
   int rc;

   rc = sqlite3_open_v2( filename, &db, SQLITE_OPEN_READONLY, NULL);
   sqlite3_close(db);

   if ( rc != SQLITE_OK )
   {
      return(0);
   }
   return(1);
}

