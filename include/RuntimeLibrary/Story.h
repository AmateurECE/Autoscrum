/******************************************************************************
 * NAME:	    Story.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the public interface for manipulating Story
 *		    objects.
 *
 * CREATED:	    07/20/2018
 *
 * LAST EDITED:	    08/19/2018
 ***/

#ifndef __ET_STORY__
#define __ET_STORY__

/******************************************************************************
 * INCLUDES
 ***/

/* #include "Task.h" */
/* #include "Issue.h" */
/* #include "User.h" */
/* #include "TagTree.h" */
/* #include "Backlog.h" */

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* /\* Standard Scrum Object data *\/ */
  /* ScrumObjectIdentifier id; */

  /* /\* The Backlog which this story is queued to *\/ */
  /* Backlog * backlog; */

  /* /\* Tag Tree of the Tags which the user has attributed to the */
  /*  * Story. */
  /*  *\/ */
  /* TagTree * tags; */

  /* /\* The List of watchers. For a description of "watchers" please see */
  /*  * the Scrum Object module */
  /*  *\/ */
  /* list * watchers; */

  /* /\* The number of votes this issue has. For a description of "votes" */
  /*  * please see the Scrum Object module. */
  /*  *\/ */
  /* short numVotes; */

  /* /\* This is a short description of the plot of the story, attributed by */
  /*  * the user. */
  /*  *\/ */
  /* char * description; */

  /* /\* The length of the description field. *\/ */
  /* size_t descriptionLength; */

  /* /\* The User who has been tasked with overseeing completion of the */
  /*  * Story. */
  /*  *\/ */
  /* User * maintainer; */

  /* /\* Tasks and Issues that are components of this story. *\/ */
  /* Task * tasks; */
  /* Issue * issues; */

  /* /\* TODO: Add story points *\/ */

} Story;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern Story * Story_create(void);
extern void Story_destroy(void);

#endif /* __ET_STORY__ */

/*****************************************************************************/
