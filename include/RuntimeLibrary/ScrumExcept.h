/******************************************************************************
 * NAME:	    ScrumExcept.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains a few macros that are helpful for
 *		    handling exceptions.
 *		    TODO: Fill out list of exported (useful) symbols.
 *
 * CREATED:	    09/26/2017
 *
 * LAST EDITED:	    08/12/2018
 ***/

#ifndef __ET_SCRUMEXCEPT__
#define __ET_SCRUMEXCEPT__

/******************************************************************************
 * INCLUDES
 ***/

#include "ScrumContext.h"

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

#define SCRUM_OK	0
#define SCRUM_ERROR	1
#define SCRUM_EUNKNOWN	2

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Similar to the StdC function, this function returns a pointer to a STATIC
 * string which describes the error which occurred.
 */
char * ScrumExcept_strerror(ScrumContext * context);

#endif /* __SCRUMEXCEPT_H__ */

/*****************************************************************************/
