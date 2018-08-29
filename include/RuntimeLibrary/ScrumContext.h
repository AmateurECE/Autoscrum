/******************************************************************************
 * NAME:	    ScrumContext.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file contains information based on the context of the
 *		    calling process. This file presents a struct and an API,
 *		    the purpose of which is to allow the library to be
 *		    completely reentrant.
 *
 * CREATED:	    08/12/2018
 *
 * LAST EDITED:	    08/21/2018
 ***/

#ifndef __ET_SCRUMCONTEXT__
#define __ET_SCRUMCONTEXT__

/******************************************************************************
 * INCLUDES
 ***/

#include "RuntimeLibrary/Serializer/SerializerConfigStructdef.h"

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* Contains information about the last reported error in the library.
   * See ScrumExcept.h.
   */
  int err;

  /* Contains a pointer to a human-readable error string. DO NOT USE THIS
   * PARAMETER, it may be NULL at any point.
   */
  char * errstr;

  /* Contains information about the context of the Serializer. See
   * SerializerConfig.h.
   */
  struct SerializerConfig cfg;

} ScrumContext;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

int ScrumContext_init(ScrumContext * context);
int ScrumContext_open(ScrumContext * context, char * path);

#endif /* __ET_SCRUMCONTEXT__ */

/*****************************************************************************/
