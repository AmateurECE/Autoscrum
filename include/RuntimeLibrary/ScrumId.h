/******************************************************************************
 * NAME:	    ScrumId.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This struct contains data that is common to all Autoscrum
 *		    Scrum data objects.
 *
 * CREATED:	    07/21/2018
 *
 * LAST EDITED:	    08/18/2018
 ***/

#ifndef __ET_SCRUMOBJECTIDENTIFIER__
#define __ET_SCRUMOBJECTIDENTIFIER__

/******************************************************************************
 * INCLUDES
 ***/

#include <stdint.h>

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  uint16_t id;
  uint8_t pathLength;
  uint8_t titleLength;
  char * path;
  char * title;

} ScrumId;

#endif /* __ET_SCRUMOBJECTIDENTIFIER__ */

/*****************************************************************************/
