/******************************************************************************
 * NAME:	    SerializerConfig.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file contains an API for interacting with the
 *		    Serializer on a lower level. This API contains
 *		    implementation details of the Serializer.
 *
 * CREATED:	    08/04/2018
 *
 * LAST EDITED:	    08/07/2018
 ***/

#ifndef __ET_SERIALIZERCONFIG__
#define __ET_SERIALIZERCONFIG__

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

/* This is the name of the table in the database which contains Autoscrum data
 */
#define AUTOSCRUM_DB_TABLE "AUTOSCRUM_DB"

/* This macro contains the list of fields which are contained in the Autoscrum
 * database table. More fields will be added to this parameter as development
 * continues. When development has finished, no more fields will be added.
 */
#define AUTOSCRUM_DB_FIELD "id int"

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

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Initializes `cfg' with the remaining data passed to it. This function is
 * used when `path' points to an existing Autoscrum database.
 */
int SerializerConfig_initExistingDb(struct SerializerConfig * cfg,
				    size_t pathLength, char * path);

/* Initializes `cfg' with the remaining data passed to it. This function
 * creates a new Autoscrum database at `path.'
 */
int SerializerConfig_initNewDb(struct SerializerConfig * cfg,
			       size_t pathLength, char * path);

/* Closes all resources contained by the Serializer. Any subsequent calls to
 * the Serializer functions will result in error return codes and no action
 * taken.
 */
int SerializerConfig_free(struct SerializerConfig * cfg);

#endif /* __ET_SERIALIZERCONFIG__ */

/*****************************************************************************/
