/******************************************************************************
 * NAME:	    recursive-macro.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file implements a set of macros which can be used
 *		    to implement recursively expanding macros. The macros
 *		    exported by this interface which may be useful to the user
 *		    are:
 *
 *			NOT(x)		    - Perform logical inverse of `x'.
 *			BOOL(x)		    - Cast `x' to a boolean.
 *			IF_ELSE(x)(a)(b)    - If `x', expands to `a.' Else `b'.
 *			HAS_ARGS(...)	    - TRUE if ... expands to something.
 *			CAT(x,y)	    - Concatenate x and y.
 *
 * CREATED:	    07/05/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define FIRST(a, ...) a
#define SECOND(a, b, ...) b

#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a,b) a ## b

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()

#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

/*****************************************************************************/
