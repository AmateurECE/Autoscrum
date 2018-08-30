/******************************************************************************
 * NAME:	    ProjectSerializer.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This header is an interface to segregate the implementation
 *                  of the serialization of objects from their function. This
 *                  allows the implementation of the serializer to have zero
 *                  dependencies--it could be a simple binary file writer, a
 *                  database, whatever.
 *
 * CREATED:	    07/29/2018
 *
 * LAST EDITED:	    08/18/2018
 ***/

#ifndef __ET_PROJECTSERIALIZER__
#define __ET_PROJECTSERIALIZER__

/******************************************************************************
 * INCLUDES
 ***/

#include <stddef.h>

#include "RuntimeLibrary/Project.h"
#include "RuntimeLibrary/ScrumContext.h"

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Read/Write a project, searching for it based on its id. The `id' field in
 * `p' must be set previous to this call.
 */
extern int Project_readId(ScrumContext * ctx, Project * p);
extern int Project_writeId(ScrumContext * ctx, Project * p);

/* Read/Write a project, searching for it based on its path. The `path' field
 * in `p' must be set previous to this call.
 */
extern int Project_readPath(ScrumContext * ctx, Project * p);
extern int Project_writePath(ScrumContext * ctx, Project * p);

/* Get the number of projects in the Autoscrum database, and return it in `n'
 */
extern int Project_readNumberOfProjects(ScrumContext * ctx, size_t * n);

/* Read the ScrumIds of all projects in the database into the
 * array pointed to by `projects'.
 */
extern int Project_readAllProjectIds(ScrumContext * ctx, size_t n,
				     ScrumId projects[n]);

#endif /* __ET_PROJECTSERIALIZER__ */

/*****************************************************************************/
