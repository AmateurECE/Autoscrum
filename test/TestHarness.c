/******************************************************************************
 * NAME:	    TestHarness.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This code contains a general test harness and a hook for
 *		    verifying the behavior of a module.
 *
 * CREATED:	    07/29/2018
 *
 * LAST EDITED:	    07/31/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include "TestHarness.h"

/******************************************************************************
 * EXTERN DECLARATIONS
 ***/

extern int runTests();

/******************************************************************************
 * MAIN
 ***/

int main() {
  return runTests();
}

/*****************************************************************************/
