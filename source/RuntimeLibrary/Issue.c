/******************************************************************************
 * NAME:	    Issue.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file implements the interface presented in Issue.h
 *
 * CREATED:	    07/11/2018
 *
 * LAST EDITED:	    07/12/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include "Issue.h"

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    Issue_create
 *
 * DESCRIPTION:	    Allocates memory for a new Issue object. As of right now,
 *		    this function does no initialization, so it's not
 *		    particularly useful.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    (Issue *) A new issue object, or NULL if an error occurred.
 *
 * NOTES:	    none.
 ***/
Issue * Issue_create(void)
{
  return malloc(sizeof(Issue));
}

/******************************************************************************
 * FUNCTION:	    Issue_destroy
 *
 * DESCRIPTION:	    Frees memory associated with an Issue object. In the
 *		    future, this function will also free memory that is
 *		    initialized in Issue_create().
 *
 * ARGUMENTS:	    issue: (Issue *) The issue to destroy.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none.
 ***/
void Issue_destroy(Issue ** issue)
{
  if (issue == NULL || *issue == NULL)
    return;
  free(*issue);
  *issue = NULL;
}

/*****************************************************************************/
