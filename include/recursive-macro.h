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
 *			STRINGIFY(x)	    - Convert `x' to a string.
 *
 *		    Use of the recursively expanding macro:
 *
 *			#define GREET(x) Hello, x!
 *			EVAL(MAP(GREET, Mum, Dad, Adam, Joe))
 *
 *		    Expands to:
 *
 *			Hello, Mum! Hello, Dad! Hello, Adam! Hello, Joe!
 *
 * CREATED:	    07/05/2018
 *
 * LAST EDITED:	    07/31/2018
 ***/

#ifndef __ET_RECURSIVE_MACRO__
#define __ET_RECURSIVE_MACRO__

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define STRINGIFY(x) xstr(x)
#define xstr(x) #x

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

#define EMPTY()

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()

#define EVAL(...) EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define MAP(m, first, ...)           \
  m(first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    DEFER2(_MAP)()(m, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP

#endif /* __ET_RECURSIVE_MACRO__ */

/*****************************************************************************/
