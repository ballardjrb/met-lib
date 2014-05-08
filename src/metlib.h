
#include <sqlite3.h>

/*  
** database types
*/
#define FLATFILE 0
#define SQLITEDB 1
#define MONGODB 2

typedef struct DB_HANDLES
{
   FILE *fd;
   sqlite3 *sq3_db;
} DB_Handle_Struct;



/*
** Function defines
*/
extern int metlib_open( int , char *, int *);
extern int metlib_close( int );
