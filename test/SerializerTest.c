/******************************************************************************
 * NAME:	    SerializerTest.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Implements the Test harness defined in the header file.
 *		    All tests:
 *			- Create a new db and clean it up when the test has
 *			  finished.
 *			- Are independent, i.e have NO preconditions.
 *			- Segregate implementation details of the serializer.
 *
 * CREATED:	    08/17/2018
 *
 * LAST EDITED:	    08/19/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include "recursive-macro.h"
#include "TestHarness.h"
#include "SerializerTest.h"
#include "RuntimeLibrary/ScrumContext.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define SerializerTest_oneTest(testName)				\
  if (initTest(&testContext) != SUCCESS					\
      || testName(&testObject) != SUCCESS)				\
    result = FAIL, failures++;						\
  else									\
    result = PASS;							\
  cleanupTest(&testContext);						\
  tests++;								\
  printf("%s %*s\n", STRINGIFY(testName), MAX_FN_NAME_LENGTH, result);	\

#define SerializerTest_runTheseTests(...)		\
  int runTests() {					\
    int failures = 0, tests = 0;			\
    char result[32] = '\0';				\
    ScrumContext testContext;				\
    TEST_MODULE testObject;				\
    EVAL(MAP(SerializerTest_oneTest, __VA_ARGS__))	\
    printf("\n"						\
	   "Run/Errors/Pass Rate\n"			\
	   "%3d/%6d/%9\n"				\
	   tests, failures, failures / tests * 1.0);	\
    return failures;					\
  }

#define TEST_FILE_PATH 'TestFile.db'

/******************************************************************************
 * STATIC FUNTION PROTOTYPES
 ***/

/* Test Helpers */
static int initTest(ScrumContext * context);
static int cleanupTest(ScrumContext * context);

/* Tests */
static int testWriteNewEntryPath(ScrumContext * testContext,
				 TEST_MODULE * testObject);
static int testWriteNewEntryId(ScrumContext * testContext,
			       TEST_MODULE * testObject);
static int testUpdateEntryPath(ScrumContext * testContext,
			       TEST_MODULE * testObject);
static int testUpdateEntryId(ScrumContext * testContext,
			     TEST_MODULE * testObject);
static int testReadValidPath(ScrumContext * testContext,
			     TEST_MODULE * testObject);
static int testReadValidId(ScrumContext * testContext,
			   TEST_MODULE * testObject);
static int testReadInvalidPath(ScrumContext * testContext,
			       TEST_MODULE * testObject);
static int testReadInvalidId(ScrumContext * testContext,
			     TEST_MODULE * testObject);

static int testReadIdNull(ScrumContext * testContext,
			  TEST_MODULE * testObject);
static int testWriteIdNull(ScrumContext * testContext,
			   TEST_MODULE * testObject);
static int testReadPathNull(ScrumContext * testContext,
			    TEST_MODULE * testObject);
static int testWritePathNull(ScrumContext * testContext,
			     TEST_MODULE * testObject);
static int testReadNumberOfNull(ScrumContext * testContext,
				TEST_MODULE * testObject);
static int testReadAllNull(ScrumContext * testContext,
			   TEST_MODULE * testObject);

static int testReadNumberOf(ScrumContext * testContext,
			    TEST_MODULE * testObject);
static int testReadAllIds(ScrumContext * testContext,
			  TEST_MODULE * testObject);
static int testInvalidScrumContext(ScrumContext * testContext,
				   TEST_MODULE * testObject);

int runTests() { return 1; }

/* SerializerTest_runTheseTests( */
			     /* testWriteNewEntryPath, */
			     /* testWriteNewEntryId, */
			     /* testUpdateEntryPath, */
			     /* testUpdateEntryId, */
			     /* testReadValidPath, */
			     /* testReadValidId, */
			     /* testReadInvalidPath, */
			     /* testReadInvalidId, */

			     /* testReadIdNull, */
			     /* testWriteIdNull, */
			     /* testReadPathNull, */
			     /* testWritePathNull, */
			     /* testReadNumberOfNull, */
			     /* testReadAllNull, */

			     /* testReadNumberOf, */
			     /* testReadAllIds, */
			     /* testReadIdISC, */
			     /* testWriteIdISC, */
			     /* testReadPathISC, */
			     /* testWritePathISC, */
			     /* testReadNumberOfProjectsISC, */
			     /* testReadAllProjectIdsISC */
			     /* ); */

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    initTest
 *
 * DESCRIPTION:	    Initialize a new Db (and corresponding ScrumContext).
 *
 * ARGUMENTS:	    context: Pointer to receptacle for ScrumContext.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int initTest(ScrumContext * context)
{
  char path[] = TEST_FILE_PATH;
  size_t pathLength = sizeof(path);
  char * allocatedPath = malloc()
  if (SerializerConfig_initNewDb(context, pathLength, path) != SCRUM_OK)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    cleanupTest
 *
 * DESCRIPTION:	    Clean up all resources generated during the test.
 *
 * ARGUMENTS:	    context: The ScrumContext instance affected by the test.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int cleanupTest(ScrumContext * context)
{
  SerializerConfig_free(context);

  if (unlink(TEST_FILE_PATH) < 0)
    return FAILURE;
  return SUCCESS;
}

/******************************************************************************
 * FUNCTION:	    testWriteNewEntryPath
 *
 * DESCRIPTION:	    Tests that _writePath() can add new entries, which persist
 *		    beyond the ScrumContext instance.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testWriteNewEntryPath(ScrumContext * testContext,
				 TEST_MODULE * testObject)
{
/* Verify entry is not present.
 * 1. Create object using object_constructor_1
 * 2. Attempt to read it from ScrumContext
 */
  
/* Insert new entry
 * Close db
 * Set ScrumContext to NULL.
 * Reopen Db
 * Verify entry is present.
 */
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testWriteNewEntryId
 *
 * DESCRIPTION:	    Tests that _writeId() can add new entries, which persist
 *		    beyond the ScrumContext instance.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testWriteNewEntryId(ScrumContext * testContext,
			       TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testUpdateEntryPath
 *
 * DESCRIPTION:	    Tests that _writePath() can update previously created
 *		    entries.
 *
 * ARGUMENTS:	    
 *
 * RETURN:	    
 ***/
static int testUpdateEntryPath(ScrumContext * testContext,
			       TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testUpdateEntryId
 *
 * DESCRIPTION:	    Tests that _writeId() can update previously created
 *		    entries.
 *
 * ARGUMENTS:	    
 *
 * RETURN:	    
 ***/
static int testUpdateEntryId(ScrumContext * testContext,
			     TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testReadValidPath
 *
 * DESCRIPTION:	    Tests that _readPath() will read previously created entries
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testReadValidPath(ScrumContext * testContext,
			     TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testReadValidId
 *
 * DESCRIPTION:	    Tests that _readId() will read previously created entries
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testReadValidId(ScrumContext * testContext,
			   TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testReadInvalidPath
 *
 * DESCRIPTION:	    Tests that _readPath will correctly report errors if
 *		    if attempting to read nonexistent data.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testReadInvalidPath(ScrumContext * testContext,
			       TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testReadInvalidId
 *
 * DESCRIPTION:	    Tests that _readId will correctly report errors if
 *		    if attempting to read nonexistent data.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testReadInvalidId(ScrumContext * testContext,
			     TEST_MODULE * testObject)
{
  return FAILURE;
}

/* NULL pointers for the full interface */
static int testReadIdNull(ScrumContext * testContext,
			  TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testWriteIdNull(ScrumContext * testContext,
			   TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testReadPathNull(ScrumContext * testContext,
			    TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testWritePathNull(ScrumContext * testContext,
			     TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testReadNumberOfNull(ScrumContext * testContext,
				TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testReadAllNull(ScrumContext * testContext,
			   TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testReadNumberOf
 *
 * DESCRIPTION:	    Tests that readNumberOfEntries always returns the correct
 *		    number of entries.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testReadNumberOf(ScrumContext * testContext,
			    TEST_MODULE * testObject)
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testReadAllIds
 *
 * DESCRIPTION:	    readProjectIds always reads ALL project ids.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testReadAllIds(ScrumContext * testContext,
			  TEST_MODULE * testObject)
{
  return FAILURE;
}

/* These tests evaluate that the interface reports the correct errors when the
 * ScrumContext object is invalid (in some fashion or another).
 */
static int testReadIdISC(ScrumContext * testContext,
			 TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testWriteIdISC(ScrumContext * testContext,
			  TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testReadPathISC(ScrumContext * testContext,
			   TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testWritePathISC(ScrumContext * testContext,
			    TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testReadNumberOfProjectsISC(ScrumContext * testContext,
				       TEST_MODULE * testObject)
{
  return FAILURE;
}

static int testReadAllProjectIdsISC(ScrumContext * testContext,
				    TEST_MODULE * testObject)
{
  return FAILURE;
}

/*****************************************************************************/
