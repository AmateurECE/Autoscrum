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
 * LAST EDITED:	    08/14/2018
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
#include "RuntimeLibrary/ScrumContext.h"
#include "RuntimeLibrary/ScrumExcept.h"
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
static int testCtxErrStr();

/* This macro satisfies the test harness */
TestHarness_tests(
		  testInitExistingDbNull,
		  testInitExistingDbBunk,
		  testInitExistingDbReal,
		  testInitNewDbNull,
		  testInitNewDbNew,
		  testInitNewDbExisting,
		  testFreeNull,
		  testFreeReal,
		  testCtxErrStr
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
  ScrumContext ctx;
  if (SerializerConfig_initExistingDb(&ctx, 0, NULL) == SCRUM_OK)
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
  ScrumContext ctx;

  /* Note that this path works only if the test is run from the repo's root
   * directory.
   */
  char path[] = "test/SerializerConfigTest/TestFile.txt";
  size_t pathLength = sizeof(path);

  if (SerializerConfig_initExistingDb(&ctx, pathLength, path) == SCRUM_OK)
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
static int testInitExistingDbReal()
{
  ScrumContext ctx;

  /* Note that this path only works if the test is being run from the repo's
   * root directory.
   */
  char path[] = "test/SerializerConfigTest/TestFile.db";
  size_t pathLength = sizeof(path);

  /* First, create the db. */
  if (SerializerConfig_initNewDb(&ctx, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&ctx);

  /* Then attempt to open it as an existing Db. */
  if (SerializerConfig_initExistingDb(&ctx, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&ctx);
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
  ScrumContext ctx;

  char path[] = "test/SerializerConfigTest/testInitNewDbNewTestFile.db";
  size_t pathLength = sizeof(path);
  if (SerializerConfig_initNewDb(&ctx, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&ctx);

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
  ScrumContext ctx;
  char path[] = "test/SerializerConfigTest/testInitNewDbNewTestFile.db";
  size_t pathLength = sizeof(path);

  /* First, create the db. */
  if (SerializerConfig_initNewDb(&ctx, pathLength, path) != SCRUM_OK)
    return FAILURE;
  SerializerConfig_free(&ctx);
  /* Get the time of creation */
  struct stat fileStats;
  if (stat(path, &fileStats))
    return FAILURE;
  time_t orig = fileStats.st_mtimespec.tv_sec;

  /* Call again */
  if (SerializerConfig_initNewDb(&ctx, pathLength, path) != SCRUM_OK)
    return FAILURE;
  if (stat(path, &fileStats))
    return FAILURE;
  SerializerConfig_free(&ctx);

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
  ScrumContext ctx;
  char path[] = "test/SerializerConfigTest/testInitNewDbNewTestFile.db";
  size_t pathLength = sizeof(path);
  if (SerializerConfig_initNewDb(&ctx, pathLength, path) != SCRUM_OK)
    return FAILURE;

  if (SerializerConfig_free(&ctx) != SCRUM_OK)
    return FAILURE;

  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testCtxErrStr
 *
 * DESCRIPTION:	    The Serializer module is required to implement some kind of
 *		    system to provide error messages when something bad
 *		    happens. Generally, this means setting errno to
 *		    SCRUM_ESERIALIZER and populating ScrumContext.errstr with a
 *		    pointer to a static string. This test does not test for
 *		    value, only non-NULL-ness. To do this, we perform the same
 *		    procedure as in initExistingDbBunk
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int.
 ***/
static int testCtxErrStr()
{
  ScrumContext ctx;

  /* Note that this path works only if the test is run from the repo's root
   * directory.
   */
  char path[] = "test/SerializerConfigTest/TestFile.txt";
  size_t pathLength = sizeof(path);

  SerializerConfig_initExistingDb(&ctx, pathLength, path);

  if (ctx.err != SCRUM_ESERIALIZER)
    return FAILURE;
  if (ctx.errstr == NULL)
    return FAILURE;
  return SUCCESS;  
}

/*****************************************************************************/
