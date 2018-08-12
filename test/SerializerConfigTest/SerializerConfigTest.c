/******************************************************************************
 * NAME:	    SerializerConfigTest.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Test module for the implementation of the SerializerConfig
 *		    module.
 *
 * CREATED:	    08/04/2018
 *
 * LAST EDITED:	    08/12/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stddef.h>
#include <time.h>
#include <sys/stat.h>
#include <sqlite3.h>
#include <unistd.h>

#include "TestHarness.h"
#include "CompileConfig.h"
#include "RuntimeLibrary/Serializer/SerializerConfig.h"

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int testInitExistingDbNull();
static int testInitExistingDbBunk();
static int testInitExistingDbReal();
static int testInitNewDbNull();
static int testInitNewDbNew();
static int testInitNewDbExisting();
static int testFreeNull();
static int testFreeReal();

/* This macro satisfies the test harness */
TestHarness_tests(
		  testInitExistingDbNull,
		  testInitExistingDbBunk,
		  testInitExistingDbReal,
		  testInitNewDbNull,
		  testInitNewDbNew,
		  testInitNewDbExisting,
		  testFreeNull,
		  testFreeReal
		  );

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    testInitExistingDbNull
 *
 * DESCRIPTION:	    This function tests the SerializerConfig_initExistingDb
 *		    function with NULL passed as a path.
 *
 * ARGUMENTS:	    none
 *
 * RETURN:	    int -- SUCCESS on success, failure otherwise.
 ***/
static int testInitExistingDbNull()
{
  /* Initialize the serializer with bunk parameters */
  struct SerializerConfig cfg;
  if (SerializerConfig_initExistingDb(&cfg, 0, NULL) == SCRUM_OK)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testInitExistingDbBunk
 *
 * DESCRIPTION:	    This function tests the SerializerConfig_initExistingDb
 *		    function with a valid path which doesn't contain a db.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- SUCCESS if the test passes, FAILURE otherwise.
 ***/
static int testInitExistingDbBunk() {
  struct SerializerConfig cfg;

  /* Note that this path works only if the test is run from the repo's root
   * directory.
   */
  char path[] = "test/SerializerConfigTest/TestFile.txt";
  size_t pathLength = sizeof(path);

  if (SerializerConfig_initExistingDb(&cfg, pathLength, path) == SCRUM_OK)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testInitExistingDbReal
 *
 * DESCRIPTION:	    Tests the SerializerConfig_initExistingDb function with a
 *		    correct set of parameters.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- SUCCESS if the test passes, FAILURE otherwise.
 ***/
static int testInitExistingDbReal() {
  struct SerializerConfig cfg;

  /* Note that this path only works if the test is being run from the repo's
   * root directory.
   */
  char path[] = "test/SerializerConfigTest/TestFile.db";
  size_t pathLength = sizeof(path);

  /* First, create the db. */
  if (SerializerConfig_initNewDb(&cfg, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&cfg);

  /* Then attempt to open it as an existing Db. */
  if (SerializerConfig_initExistingDb(&cfg, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&cfg);
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testInitNewDbNull
 *
 * DESCRIPTION:	    Tests the SerializerConfig_initNewDb function will NULL
 *		    parameters.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    SUCCESS | FAILURE.
 ***/
static int testInitNewDbNull()
{
  if (SerializerConfig_initNewDb(NULL, 0, NULL) == SCRUM_OK)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testInitNewDbNew
 *
 * DESCRIPTION:	    Tests SerializerConfig_initNewDb with parameters that
 *		    create a completely new Database file.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    SUCCESS | FAILURE.
 ***/
static int testInitNewDbNew()
{
  struct SerializerConfig cfg;

  char path[] = "test/SerializerConfigTest/testInitNewDbNewTestFile.db";
  size_t pathLength = sizeof(path);
  if (SerializerConfig_initNewDb(&cfg, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&cfg);

  /* This should be a new file every time we run this test */
  if (unlink(path) < 0)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testInitNewDbExisting
 *
 * DESCRIPTION:	    Tests SerializerConfig_initNewDb with the name of an
 *		    existing database, to be sure that it was overwritten
 *		    during the call.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    SUCCESS | FAILURE.
 ***/
static int testInitNewDbExisting()
{
  struct SerializerConfig cfg;
  char path[] = "test/SerializerConfigTest/testInitNewDbNewTestFile.db";
  size_t pathLength = sizeof(path);

  /* First, create the db. */
  if (SerializerConfig_initNewDb(&cfg, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&cfg);
  /* Get the time of creation */
  struct stat fileStats;
  if (stat(path, &fileStats))
    return FAILURE;
  time_t orig = fileStats.st_mtimespec.tv_sec;

  /* Call again */
  if (SerializerConfig_initNewDb(&cfg, pathLength, path) != SCRUM_OK)
    return FAILURE;
  if (stat(path, &fileStats))
    return FAILURE;
  SerializerConfig_free(&cfg);

  /* Make sure the times are different */
  if (fileStats.st_mtimespec.tv_sec ^ orig)
    return FAILURE;

  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testFreeNull
 *
 * DESCRIPTION:	    This function tests the SerializerConfig_free function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- SUCCESS on success, FAILURE otherwise.
 ***/
static int testFreeNull()
{
  if (SerializerConfig_free(NULL) == SCRUM_OK)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testFreeReal
 *
 * DESCRIPTION:	    Tests the SerializerConfig_free function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    SUCCESS | FAILURE.
 ***/
static int testFreeReal()
{
  struct SerializerConfig cfg;
  char path[] = "test/SerializerConfigTest/testInitNewDbNewTestFile.db";
  size_t pathLength = sizeof(path);
  if (SerializerConfig_initNewDb(&cfg, pathLength, path) != SCRUM_OK)
    return FAILURE;

  if (SerializerConfig_free(&cfg) != SCRUM_OK)
    return FAILURE;

  return SUCCESS;
}

/*****************************************************************************/
