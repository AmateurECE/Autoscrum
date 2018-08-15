/******************************************************************************
 * NAME:	    ScrumExcept.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains a few macros that are helpful for
 *		    handling exceptions.
 *
 *		    NOTE TO DEVELOPERS: The Autoscrum convention is to set
 *		    errno at the bottom of the call stack. A good rule of thumb
 *		    is to not set errno if the function calls any other
 *		    autoscrum function.
 *
 * CREATED:	    09/26/2017
 *
 * LAST EDITED:	    08/13/2018
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

#define SCRUM_OK	    0
#define SCRUM_ERROR	    1
#define SCRUM_EUNKNOWN	    2
#define SCRUM_ENULLPTR	    3
#define SCRUM_ESERIALIZER   4

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Similar to the StdC function, this function returns a pointer to a STATIC
 * string which describes the error which occurred.
 */
char * ScrumExcept_strerror(ScrumContext * context);

#endif /* __SCRUMEXCEPT_H__ */

/*****************************************************************************/
