/******************************************************************************
 * NAME:	    SerializerConfig.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the implementation of the API presented in
 *		    SerializerConfig.h.
 *
 * CREATED:	    08/04/2018
 *
 * LAST EDITED:	    08/12/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

/* C Standard Library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External/System Libraries */
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sqlite3.h>

/* Autoscrum Headers */
#include "CompileConfig.h"
#include "RuntimeLibrary/Serializer/SerializerConfig.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

/* Set this to 1 to enable debugging of this module. */
/* #define SERIALIZERCONFIG_DEBUG 0 */

/* If global debug is defined, debug this module. */
#if defined(CONFIG_DEBUG) && !defined(SERIALIZERCONFIG_DEBUG)
#   define SERIALIZERCONFIG_DEBUG 1
#endif

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int openDatabase(struct SerializerConfig * cfg,
			size_t pathLength, char * path);
static int tableExists(void *, int, char **, char **);

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    SerializerConfig_initExistingDb
 *
 * DESCRIPTION:	    Intitializes the SerializerConfig struct with the remaining
 *		    data passed. This function is used when `path' points to an
 *		    existing Autoscrum database.
 *
 * ARGUMENTS:	    cfg: (struct SerializerConfig *) The config object.
 *		    pathLength: (size_t) The length of the string at `path'.
 *		    path: (char *) The location of the file on disk.
 *
 * RETURN:	    int -- SCRUM_OK on success, SCRUM_ERROR otherwise.
 ***/
int SerializerConfig_initExistingDb(struct SerializerConfig * cfg,
				    size_t pathLength, char * path)
{
  if (openDatabase(cfg, pathLength, path) != SCRUM_OK)
    return SCRUM_ERROR;

  /* TODO: Update debug fprintfs to logging calls */

  const char * query = "SELECT name FROM sqlite_master WHERE type='table' "
    "AND name='"AUTOSCRUM_DB_TABLE"';";
  int exists = 0;
  char * error = NULL;
  if (sqlite3_exec(cfg->pDatabase, query, tableExists, (void *)&exists, &error)
      != SQLITE_OK) {
#if (SERIALIZERCONFIG_DEBUG)
    if (error != NULL) {
      fprintf(stderr, "%s:%d:%s\n", __func__, __LINE__, error);
      sqlite3_free(error);
    } else {
      fprintf(stderr, "Could not validate file as an Autoscrum Database\n");
    }
#endif
    goto exception;
  }

  /* By this point, we know whether or not the table exists. */
  if (!exists) {
#if (SERIALIZERCONFIG_DEBUG)
    fprintf(stderr, "The database is not a valid Autoscrum database.\n");
#endif
    goto exception;
  }

  return SCRUM_OK;

 exception:
  SerializerConfig_free(cfg);
  return SCRUM_ERROR;
}

/******************************************************************************
 * FUNCTION:	    SerializerConfig_initNewDb
 *
 * DESCRIPTION:	    Initializes `cfg' with the remaining data passed to it.
 *		    This function creates a new Autoscrum database at `path.'
 *
 * ARGUMENTS:	    cfg: (struct SerializerConfig *) The config object.
 *		    pathLength: (size_t) The length of the string at `path'.
 *		    path: (char *) Location to create the new DB file.
 *
 * RETURN:	    SCRUM_OK | SCRUM_ERROR
 ***/
int SerializerConfig_initNewDb(struct SerializerConfig * cfg,
			       size_t pathLength, char * path)
{
  /* If the file doesn't exist, create it. If it does exist, clear it. */
  int newFd = -1;
  if ((newFd = open(path, O_CREAT | O_TRUNC,
		    S_IRWXU | S_IRUSR | S_IXUSR)) < 0
      || close(newFd)) {
#if (SERIALIZERCONFIG_DEBUG)
    fprintf(stderr, "%s:%d:(%d) %s\n", __func__, __LINE__, errno,
	    strerror(errno));
#endif
    return SCRUM_ERROR;    
  }

  if (openDatabase(cfg, pathLength, path) != SCRUM_OK)
    return SCRUM_ERROR;

  /* TODO: Ensure we create the file so that only we can read it. */

  const char * query = "CREATE TABLE "AUTOSCRUM_DB_TABLE"("
    AUTOSCRUM_DB_FIELD")";
  char * error = NULL;
  if (sqlite3_exec(cfg->pDatabase, query, NULL, NULL, &error)
      != SQLITE_OK) {
#if (SERIALIZERCONFIG_DEBUG)
    if (error != NULL) {
      fprintf(stderr, "%s:%d:%s\n", __func__, __LINE__, error);
      sqlite3_free(error);
    } else {
      fprintf(stderr, "Could not create the Autoscrum table.\n");
    }
#endif
    /* Close the database and return an error */
    SerializerConfig_free(cfg);
    return SCRUM_ERROR;
  }

  return SCRUM_OK;
}

/******************************************************************************
 * FUNCTION:	    SerializerConfig_free
 *
 * DESCRIPTION:	    Closes all resources contained by the Serializer. Any
 *		    subsequent calls to the Serializer functions will result
 *		    in error return codes and no action taken. It's important
 *		    to note that this function does not handle memory
 *		    management of the caller's data. This function (in its
 *		    current implementation) simply closes the database ptr.
 *
 * ARGUMENTS:	    cfg: (struct SerializerConfig *) The object to remove.
 *
 * RETURN:	    SCRUM_OK, or SCRUM_ERROR if a failure occurred.
 ***/
int SerializerConfig_free(struct SerializerConfig * cfg)
{
  if (cfg == NULL)
    return SCRUM_ERROR;

  /* Close the database */
  int ret = sqlite3_close(cfg->pDatabase);
  if (ret != SQLITE_OK) {
#if (SERIALIZERCONFIG_DEBUG)
    fprintf(stderr, "%s:%d:%s\n", __func__, __LINE__, sqlite3_errstr(ret));
#endif
    return SCRUM_ERROR;
  }

  return SCRUM_OK;
}

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    tableExists
 *
 * DESCRIPTION:	    This function determines whether the Autoscrum table exists
 *		    in the database file passed to _initExistingDb.
 *
 * ARGUMENTS:	    exists: (void *) This is really an int*. On the first
 *			invocation of this method, *exists will be set to 1.
 *			This is how we verify that the table exists.
 *		    numCols: (int) The number of columns in the result.
 *		    colText: (char **) The column values for this row.
 *		    colName: (char **) The column field names.
 *
 * RETURN:	    int -- Always returns 0, except for the case where `exists'
 *		    is NULL. However, this would indicate improper use of the
 *		    function.
 ***/
static int tableExists(void * exists, int numCols, char ** colText,
		       char ** colName)
{
  if (exists == NULL)
    return 1;

  for (int i = 0; i < numCols; i++)
    if (!strncmp(colName[i], "name", 5)
	&& !strcmp(colText[i], AUTOSCRUM_DB_TABLE))
      *(int *)exists = 1;
  return 0;
}

/******************************************************************************
 * FUNCTION:	    openDatabase
 *
 * DESCRIPTION:	    This function opens the database file specified by `path',
 *		    returning the corresponding error code.
 *
 * ARGUMENTS:	    cfg: (struct SerializerConfig *) The config object.
 *		    pathLength: (size_t) The length of the string at `path'.
 *		    path: (char *) Location to create the new DB file.
 *
 * RETURN:	    SCRUM_OK | SCRUM_ERROR
 ***/
static int openDatabase(struct SerializerConfig * cfg,
			size_t pathLength, char * path)
{
  if (cfg == NULL || path == NULL)
    return SCRUM_ERROR;

  /* TODO: Determine if the file is on the local disk. */
  /* SQLite3's locking mechanism may malfunction if the fle is on an NFS share,
   * since the fcntl() call is broken on most NFS shares. We should perform a
   * check to ensure that it's on the local disk. For reference, check this:
   * https://superuser.com/questions/338033/
   * This check should be wrapped in define guards to allow future removal.
   */

  /* TODO: Start SQLite3 in Serialize mode here */
  /* See this page: https://sqlite.org/threadsafe.html 
   * This allows the SQLite3 core to manage multiple access by threads/
   * processes without fear.
   */

  /* TODO: any SQLite3 write access must be wrapped */
  /* Since SQLite3 will be in Serialized mode, any write access must be wrapped
   * in a loop that retries if SQLITE_BUSY is returned. Otherwise, change the
   * behavior using sqlite3_busy_handler().
   */

  /* Open the database */
  int ret = sqlite3_open(path, &(cfg->pDatabase));
  if (ret != SQLITE_OK) {
#if (SERIALIZERCONFIG_DEBUG)
    fprintf(stderr, "%s:%d:%s\n", __func__, __LINE__, sqlite3_errstr(ret));
#endif
    return SCRUM_ERROR;
  }

  cfg->path = path;
  cfg->pathLength = pathLength;
  return SCRUM_OK;  
}

/*****************************************************************************/
