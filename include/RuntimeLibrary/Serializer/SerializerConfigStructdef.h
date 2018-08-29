/******************************************************************************
 * NAME:	    SerializerConfigStructdef.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file contains the struct definition of the
 *		    SerializerConfig type, in order to prevent circular
 *		    dependencies in other modules.
 *
 * CREATED:	    08/14/2018
 *
 * LAST EDITED:	    08/18/2018
 ***/

#ifndef __ET_SERIALIZERCONFIGSTRUCTDEF__
#define __ET_SERIALIZERCONFIGSTRUCTDEF__

/******************************************************************************
 * INCLUDES
 ***/

#include <sqlite3.h>
#include <stddef.h>

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

struct SerializerConfig {

  /* This serializer implementation uses SQLite3 to manage the server data. */
  sqlite3 * pDatabase;

  /* This is the path location of the database file on disk, and its
   * corresponding string length in bytes.
   */
  char * path;
  size_t pathLength;
};

#endif /* __ET_SERIALIZERCONFIGSTRUCTDEF__ */

/*****************************************************************************/
