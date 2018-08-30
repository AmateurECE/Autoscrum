/******************************************************************************
 * NAME:	    TestHarnessTest.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file is a test for the Test Harness.
 *
 * CREATED:	    07/31/2018
 *
 * LAST EDITED:	    08/30/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include "TestHarness.h"

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int thisTestWillFail();
static int thisTestWillPass();

/* This macro invocation is required to make the test harness happy */
TestHarness_tests(
		  thisTestWillPass,
		  thisTestWillFail
		  );

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    thisTestWillFail
 *
 * DESCRIPTION:	    This test is meant to fail, always.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- FAILURE
 ***/
static int thisTestWillFail()
{
  return FAILURE;
}

/******************************************************************************
 * FUNCTION:	    thisTestWillPass
 *
 * DESCRIPTION:	    This test is meant to pass, always.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- SUCCESS.
 ***/
static int thisTestWillPass()
{
  return SUCCESS;
}

/*****************************************************************************/
