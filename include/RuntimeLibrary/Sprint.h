/******************************************************************************
 * NAME:	    Sprint.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the public API for manipulating Sprint objects.
 *
 * CREATED:	    07/21/2018
 *
 * LAST EDITED:	    07/21/2018
 ***/

#ifndef __ET_SPRINT__
#define __ET_SPRINT__

/******************************************************************************
 * INCLUDES
 ***/

#include <time.h>

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* The sprint backlog */
  Backlog * backlog;

  /* startDate */
  time_t startDate;

  /* dateEndDate */
  time_t endDate;

} Sprint;

#endif /* __ET_SPRINT__ */

/*****************************************************************************/
