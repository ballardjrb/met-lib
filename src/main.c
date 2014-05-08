

#include <stdio.h>
#include <stdlib.h>

#include "metlib.h"

int main(int argc, char **argv)
{
  int status, error;

  status = 0;
  error = 0;

  /*
  **  test opening a sqlite3 database
  */
  status = metlib_open( SQLITEDB, "test.db", &error );


  /*
  ** close the sqlite3 database
  */
  status = metlib_close( SQLITEDB );

exit(0);
}
