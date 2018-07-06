/******************************************************************************
 * NAME:	    except.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains a few macros that are helpful for
 *		    handling exceptions.
 *		    TODO: Fill out list of exported (useful) symbols.
 *
 * CREATED:	    09/26/2017
 *
 * LAST EDITED:	    07/06/2018
 ***/

#ifndef __EXCEPT_H__
#define __EXCEPT_H__

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define ERROR	1
#define WARN	0

/* TODO: These terminal ctl chars are not portable. Fix with ncurses. */
#define ERROR_CODE  "\033[1;31m"
#define BOLD_CODE   "\033[1m"
#define NC_CODE	    "\033[0m"
#define WARN_CODE   "\033[1;35m"

#define ERROR_PRINT ""BOLD_CODE"%s:%d:"ERROR_CODE" "MODULE": "NC_CODE
#define WARN_PRINT  ""BOLD_CODE"%s:%d:"WARN_CODE" "MODULE": "NC_CODE

#define throw(action, ...)			\
    IF_ELSE(action)(				\
	PARSE_ERROR(__VA_ARGS__)		\
    )(						\
	PARSE_WARN(__VA_ARGS__)			\
    )

#define warn(...)

#define PARSE_WARN(format, ...)	    {				\
    PARSE_DO_FPRINTF(stderr, WARN_PRINT""format"\n\t%s\n\t^\n",	\
		     yyin_filename, yylineno,			\
		     IF_ELSE(HAS_ARGS(__VA_ARGS__))		\
		     (__VA_ARGS__,)() yytext);			\
}

#define PARSE_ERROR(format, ...)    {					\
    PARSE_DO_FPRINTF(stderr, ERROR_PRINT""format"\n\t%s\n\t^\n",	\
		     yyin_filename, yylineno,				\
		     IF_ELSE(HAS_ARGS(__VA_ARGS__))			\
		     (__VA_ARGS__,)() yytext);				\
    parsing_error = true;						\
}

#define PARSE_DO_FPRINTF(...)	fprintf(__VA_ARGS__)

#endif /* __EXCEPT_H__ */

/*****************************************************************************/
