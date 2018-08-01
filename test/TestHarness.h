/******************************************************************************
 * NAME:	    TestHarness.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains useful functions for reporting errors, etc.
 *
 * CREATED:	    07/31/2018
 *
 * LAST EDITED:	    07/31/2018
 ***/

#ifndef __ET_TESTHARNESS__
#define __ET_TESTHARNESS__

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>

#include "recursive-macro.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

/* These terminal sequences are different for every terminal, and it's not
 * worth integrating termcap or something comparable just to have them.
 */
#ifdef __APPLE__
#   define GREEN    "\033[1;32m"
#   define RED	    "\033[1;31m"
#   define NO_COLOR "\033[0m"

#   define PASS	    GREEN"PASS"NO_COLOR
#   define FAIL	    RED"FAIL"NO_COLOR
#else
#   define PASS	    "PASS"
#   define FAIL	    "FAIL"
#endif

#define SUCCESS 0
#define FAILURE -1

#define MAX_FN_NAME_LENGTH 32

#define TestHarness_oneTest(testName)					\
  if (testName() == SUCCESS) {						\
    printf("%s %*s\n", STRINGIFY(testName), MAX_FN_NAME_LENGTH,	PASS);	\
  } else {								\
    printf("%s %*s\n", STRINGIFY(testName), MAX_FN_NAME_LENGTH, FAIL);	\
    failures++;								\
  }
  

#define TestHarness_tests(...)			\
  int runTests() {				\
    int failures = 0;				\
    EVAL(MAP(TestHarness_oneTest, __VA_ARGS__))	\
    return failures;				\
  }

#endif /* __ET_TESTHARNESS__ */

/*****************************************************************************/
