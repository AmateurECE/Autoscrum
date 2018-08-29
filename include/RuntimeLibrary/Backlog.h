/******************************************************************************
 * NAME:	    Backlog.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    API for manipulating Autoscrum Backlog objects.
 *
 * CREATED:	    07/21/2018
 *
 * LAST EDITED:	    07/21/2018
 ***/

#ifndef __ET_BACKLOG__
#define __ET_BACKLOG__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* Currently, this struct only has one member. This may be expanded in the
   * future, which is why this was valued over a simple `typedef`.
   */

  /* This member contains the order of the stories in this backlog. */
  pqueue * stories;

} Backlog;

#endif /* __ET_BACKLOG__ */

/*****************************************************************************/
