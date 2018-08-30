/******************************************************************************
 * NAME:	    ScrumExceptTest.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Test for the ScrumExcept module.
 *
 * CREATED:	    08/12/2018
 *
 * LAST EDITED:	    08/30/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <string.h>

#include "TestHarness.h"
#include "RuntimeLibrary/ScrumExcept.h"

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int testOk();
static int testError();
static int testEunknown();
static int testEnullptr();

/* Utilities */
static int testErrorString(int errno, const char * str);

TestHarness_tests(
		  testOk,
		  testError,
		  testEunknown,
		  testEnullptr
		  );

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

static int testOk()
{
  return testErrorString(SCRUM_OK, "");
}

static int testError()
{
  return testErrorString(SCRUM_ERROR, "error occurred in libscrum");
}

static int testEunknown()
{
  return testErrorString(SCRUM_EUNKNOWN, "no error message available");
}

static int testEnullptr()
{
  return testErrorString(SCRUM_ENULLPTR, "this function cannot take NULL");
}

/******************************************************************************
 * FUNCTION:	    testErrorString
 *
 * DESCRIPTION:	    Implements the logic used by each of these tests.
 *
 * ARGUMENTS:	    errno: The error number to test.
 *		    compStr: The error string to test against.
 *
 * RETURN:	    SUCCESS | FAILURE
 ***/
static int testErrorString(int err, const char * compStr)
{
  ScrumContext context;
  context.err = err;

  char * str = ScrumExcept_strerror(&context);
  if (str == NULL)
    return FAILURE;
  else if (strcmp(str, compStr))
    return FAILURE;
  
  return SUCCESS;  
}

/*****************************************************************************/
