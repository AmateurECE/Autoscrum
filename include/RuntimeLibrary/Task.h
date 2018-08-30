/******************************************************************************
 * NAME:	    Task.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the public API for manipulating Task objects.
 *
 * CREATED:	    07/16/2018
 *
 * LAST EDITED:	    08/19/2018
 ***/

#ifndef __ET_TASK__
#define __ET_TASK__

/******************************************************************************
 * INCLUDES
 ***/

/* #include "ScrumId.h" */
/* #include "User.h" */
/* #include "Status.h" */

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* TODO: Uncomment fields in Task */

  /* /\* Standard Scrum Object data *\/ */
  /* ScrumId id; */

  /* /\* User who oversees resolution of the task *\/ */
  /* User maintainer; */

  /* /\* User who is responsible for completion of the task. *\/ */
  /* User assignee; */

  /* /\* The number of hours spent working on the task *\/ */
  /* float time; */

  /* /\* The status of completion of the task *\/ */
  /* enum Status status; */

  /* /\* The number of votes cast in favor of the task. Users may vote for */
  /*  * a task to help increase its priority in the backlog. Votes are meant */
  /*  * to be anonymous, however this is up to the implementer of the */
  /*  * client. All votes are created equal. */
  /*  *\/ */
  /* short numVotes; */

  /* /\* This string is a short (hopefully) description of the task *\/ */
  /* char * description; */

  /* /\* Length of the string that resides in `description'. *\/ */
  /* size_t descriptionLength; */

  /* /\* This list contains users who are 'watchers.' Watchers are people */
  /*  * who wish to be notified whenever an updated is made to an Task */
  /*  * object. */
  /*  *\/ */
  /* list * watchers; */

  /* /\* A comprehensive history of all events and changes made to the */
  /*  * Task. */
  /*  *\/ */
  /* list * history; */

  /* /\* Arena for facilitating logged communication between users. *\/ */
  /* CommentLog * commentLog; */

} Task;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* TODO: Task_create() */
/* TODO: Task_destroy() */

#endif /* __ET_TASK__ */

/*****************************************************************************/
