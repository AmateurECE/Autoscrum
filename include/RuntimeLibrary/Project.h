/******************************************************************************
 * NAME:	    Project.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    An API for manipulating Project objects.
 *
 * CREATED:	    07/20/2018
 *
 * LAST EDITED:	    08/21/2018
 ***/

#ifndef __ET_PROJECT__
#define __ET_PROJECT__

/******************************************************************************
 * INCLUDES
 ***/

#include <stddef.h>

#include "ScrumObjectIdentifier.h"
#include "TagHeap.h"
#include "EventLog.h"
#include "ScrumUser.h"
#include "ScrumGroup.h"

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* Standard Scrum Object data */
  ScrumObjectIdentifier id;

  /* An array of ScrumUser objects.
   * TODO: What's the purpose of the users?
   */
  ScrumUser * users;
  size_t numUsers;

  /* An array of ScrumGroup objects.
   * TODO: What's the purpose of the groups?
   */
  ScrumGroup * groups;
  size_t numGroups;

  /* This is the tag tree. Tags are used to automatically schedule priority of
   * stories in the backlog.
   */
  TagHeap tags;

  /* This is the event log. Whenever a change is made to the object in the
   * database, an event is created. This is implemented for traceability and
   * accountability.
   */
  ScrumEventLog eventLog;

  /* The ScrumObjectIdentifiers of each of this project's epics. */
  ScrumObjectIdentifier * epics;
  size_t numEpics;

  /* The currently active sprint. */
  ScrumObjectIdentifier activeSprint;

  /* The project backlog. */
  ScrumObjectIdentifier projectBacklog;

} Project;

#endif /* __ET_PROJECT__ */

/*****************************************************************************/
