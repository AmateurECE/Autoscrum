/******************************************************************************
 * NAME:	    Status.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file contains the definition of the Status type.
 *		    Status is an enumerated type to track (on a high level)
 *		    progress towards completion of a task. This file has no
 *		    corresponding C source file.
 *
 * CREATED:	    07/11/2018
 *
 * LAST EDITED:	    07/12/2018
 ***/

#ifndef __ET_STATUS__
#define __ET_STATUS__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

enum Status {
  QUEUED,	/* Tasks which are queued to begin soon */
  INCOMPLETE,	/* Tasks that were unable to be completed */
  IN_PROGRESS,	/* Tasks which are currently being worked on */
  COMPLETE	/* Tasks which have been completed */
};

#endif /* __ET_STATUS__ */

/*****************************************************************************/
