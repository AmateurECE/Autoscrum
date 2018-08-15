/******************************************************************************
 * NAME:	    ScrumExcept.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the implementation of the ScrumExcept module.
 *
 * CREATED:	    08/12/2018
 *
 * LAST EDITED:	    08/13/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stddef.h>

#include "RuntimeLibrary/ScrumExcept.h"

/******************************************************************************
 * STATIC DATA
 ***/

struct ErrorString { int errno; char * string; };

static struct ErrorString errorStrings[] = {
  {SCRUM_OK, ""},
  {SCRUM_ERROR, "error occurred in libscrum"},
  {SCRUM_EUNKNOWN, "no error message available"},
  {SCRUM_ENULLPTR, "this function cannot take NULL"},
  {SCRUM_ESERIALIZER, ""}
};

static int errnoMax = sizeof(errorStrings);

#define getErrorStringAddr(n)	errorStrings[(n)].string
#define getErrorNumber(n)	errorStrings[(n)].errno

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    ScrumExcept_strerror
 *
 * DESCRIPTION:	    Returns a STATIC string describing the error that occurred.
 *
 * ARGUMENTS:	    context: The Autoscrum context.
 *
 * RETURN:	    Pointer to a string describing the error.
 ***/
char * ScrumExcept_strerror(ScrumContext * context)
{
  if (context == NULL)
    return NULL;

  if (context->errno > errnoMax
      || context->errno != getErrorNumber(context->errno))
    return getErrorStringAddr(SCRUM_EUNKNOWN);
  else if (context->errno == SCRUM_ESERIALIZER)
    return context->errstr;
  else
    return getErrorStringAddr(context->errno);
}

/*****************************************************************************/
