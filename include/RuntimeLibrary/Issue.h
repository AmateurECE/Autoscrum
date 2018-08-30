/******************************************************************************
 * NAME:	    Issue.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file contains the public symbols for manipulating
 *		    Autoscrum Issue objects.
 *
 * CREATED:	    07/11/2018
 *
 * LAST EDITED:	    08/19/2018
 ***/

#ifndef __ET_ISSUE__
#define __ET_ISSUE__

/******************************************************************************
 * INCLUDES
 ***/

/* #include "ScrumId.h" */
/* #include "CommentLog.h" */
/* #include "Status.h" */

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* /\* Standard Scrum Object data *\/ */
  /* ScrumId id; */

  /* /\* User who reported the issue *\/ */
  /* User reporter; */

  /* /\* User who oversees resolution of the issue *\/ */
  /* User maintainer; */

  /* /\* User who is responsible for completion of the issue. *\/ */
  /* User assignee; */

  /* /\* The number of hours spent working on the issue *\/ */
  /* float time; */

  /* /\* The status of completion of the issue *\/ */
  /* enum Status status; */

  /* /\* The number of votes cast in favor of the issue. Users may vote for */
  /*  * an issue to help increase its priority in the backlog. Votes are */
  /*  * meant to be anonymous, however this is up to the implementer of */
  /*  * the client. All votes are created equal. */
  /*  *\/ */
  /* short numVotes; */

  /* /\* This string is a short (hopefully) description of the issue *\/ */
  /* char * description; */

  /* /\* Length of the string that resides in `description'. *\/ */
  /* size_t descriptionLength; */

  /* /\* This list contains users who are 'watchers.' Watchers are people */
  /*  * who wish to be notified whenever an updated is made to an Issue */
  /*  * object. */
  /*  *\/ */
  /* list * watchers; */

  /* /\* A comprehensive history of all events and changes made to the */
  /*  * Issue. */
  /*  *\/ */
  /* list * history; */

  /* /\* Arena for facilitating logged communication between users. *\/ */
  /* CommentLog * commentLog; */

} Issue;

/******************************************************************************
 * API FUNCTIONS
 ***/

extern Issue * Issue_create(void);
extern void Issue_destroy(Issue * issue);

#endif /* __ET_ISSUE__ */

/*****************************************************************************/
