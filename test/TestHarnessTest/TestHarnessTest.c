/******************************************************************************
 * NAME:	    TestHarnessTest.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file is a test for the Test Harness.
 *
 * CREATED:	    07/31/2018
 *
 * LAST EDITED:	    07/31/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include "TestHarness.h"

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int testFail();
static int testPass();

/* This macro invocation is required to make the test harness happy */
TestHarness_tests(
		  testPass,
		  testFail
		  );

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    testFail
 *
 * DESCRIPTION:	    This test is meant to fail, always.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- FAILURE
 ***/
static int testFail()
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    testPass
 *
 * DESCRIPTION:	    This test is meant to pass, always.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- SUCCESS.
 ***/
static int testPass()
{
  return SUCCESS;
}

/*****************************************************************************/
