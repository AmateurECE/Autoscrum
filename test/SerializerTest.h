/******************************************************************************
 * NAME:	    SerializerTest.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This header contains some definitions which implement a
 *		    test framework for the Serializer modules.
 *
 * CREATED:	    08/17/2018
 *
 * LAST EDITED:	    08/18/2018
 ***/

#ifndef __ET_SERIALIZERTEST__
#define __ET_SERIALIZERTEST__

/******************************************************************************
 * INCLUDES
 ***/

#include "TestHarness.h"

/* Unfortunately, I'll have to add #include's here as necessary */
#include "RuntimeLibrary/Project.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

/* Use of this macro:
 * #define TEST_MODULE <Module name>
 *
 * This macro is used in a few places internally, in place of certain variable
 * definitions and declarations. If the user does not define TEST_MODULE, a
 * compile time error will be thrown. Due to the placement of this #ifndef,
 * the user may want to define TEST_MODULE on the command line, using
 * -DTEST_MODULE=<MySerializer> (for GCC).
 */
#ifndef TEST_MODULE
#   error "TEST_MODULE must be defined according to SerializerTest.h"
#endif

/* Use of these macros:
 * OBJECT_CONSTRUCTOR_X
 * {
 *   <Function definition here>
 * }
 *
 * These macros expand to a function signature that each take a pointer to 
 * TEST_MODULE, whatever that may be. These functions should each initialize a
 * UNIQUE instance of type TEST_MODULE. These functions should return FAILURE
 * if something bad happens. The test will then fail.
 */
#define OBJECT_CONSTRUCTOR_1 int initTestObject1(TEST_MODULE * object)
#define OBJECT_CONSTRUCTOR_2 int initTestObject2(TEST_MODULE * object)
#define OBJECT_CONSTRUCTOR_3 int initTestObject3(TEST_MODULE * object)

#endif /* __ET_SERIALIZERTEST__ */

/*****************************************************************************/
