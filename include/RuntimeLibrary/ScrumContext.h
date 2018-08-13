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
 * LAST EDITED:	    08/12/2018
 ***/

#ifndef __ET_SCRUMCONTEXT__
#define __ET_SCRUMCONTEXT__

/******************************************************************************
 * INCLUDES
 ***/

#include "RuntimeLibrary/Serializer/SerializerConfig.h"

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  /* Contains information about the last reported error in the library.
   * See ScrumExcept.h.
   */
  int errno;

  /* Contains information about the context of the Serializer. See
   * SerializerConfig.h.
   */
  struct SerializerConfig * serConfig;

} ScrumContext;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

int ScrumContext_init(ScrumContext * context);
int ScrumContext_open(ScrumContext * context, char * path);

#endif /* __ET_SCRUMCONTEXT__ */

/*****************************************************************************/
