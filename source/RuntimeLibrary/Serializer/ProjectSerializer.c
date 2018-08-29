/******************************************************************************
 * NAME:	    ProjectSerializer.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Implementation of the Project Serializer.
 *
 * CREATED:	    08/17/2018
 *
 * LAST EDITED:	    08/21/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stddef.h>

#include "RuntimeLibrary/ScrumObjectIdentifier.h"
#include "RuntimeLibrary/Project.h"
#include "RuntimeLibrary/Serializer/ProjectSerializer.h"
#include "RuntimeLibrary/ScrumContext.h"
#include "RuntimeLibrary/ScrumExcept.h"

/******************************************************************************
 * STATIC CONST DATA
 ***/

static const char readId[] = "";
static const char readPath[] = "";
static const char updateId[] = "";
static const char updatePath[] = "";
static const char insertId[] = "";
static const char insertPath[] = "";
static const char verifyId[] = "";
static const char verifyPath[] = "";

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    Project_readId
 *
 * DESCRIPTION:	    Read a project, searching the database for the value of the
 *		    `id' field in `p'.
 *
 * ARGUMENTS:	    p: The Project, containing the id to search for.
 *
 * RETURN:	    int -- SCRUM_OK if no errors occurred.
 ***/
int Project_readId(ScrumContext * ctx, Project * p)
{
  return SCRUM_ERROR;
}

/******************************************************************************
 * FUNCTION:	    Project_writeId
 *
 * DESCRIPTION:	    Write the Project `p' to the Autoscrum database, using the
 *		    `id' field to search for existing entries.
 *
 * ARGUMENTS:	    p: The Project, containing the id of the project to update.
 *
 * RETURN:	    int -- SCRUM_OK if no errors occurred.
 ***/
int Project_writeId(ScrumContext * ctx, Project * p)
{
  return SCRUM_ERROR;
}

/******************************************************************************
 * FUNCTION:	    Project_readPath
 *
 * DESCRIPTION:	    Read a project, searching the database for the value of the
 *		    `path' field in `p'.
 *
 * ARGUMENTS:	    p: The Project, containing the path to search for.
 *
 * RETURN:	    int -- SCRUM_OK if no errors occurred.
 ***/
int Project_readPath(ScrumContext * ctx, Project * p)
{
  return SCRUM_ERROR;
}

/******************************************************************************
 * FUNCTION:	    Project_writePath
 *
 * DESCRIPTION:	    Write the Project `p' to the Autoscrum database, using the
 *		    `path' field to search for existing entries.
 *
 * ARGUMENTS:	    p: The Project, containing the path of the project to
 *			update.
 *
 * RETURN:	    int -- SCRUM_OK if no errors occurred.
 ***/
int Project_writePath(ScrumContext * ctx, Project * p)
{
  return SCRUM_ERROR;
}

/******************************************************************************
 * FUNCTION:	    Project_readNumberOfProjects
 *
 * DESCRIPTION:	    Get the number of projects in the Autoscrum database, and
 *		    return it in `n'.
 *
 * ARGUMENTS:	    n: The number of projects is returned in *n.
 *
 * RETURN:	    int -- SCRUM_OK if no errors occurred.
 ***/
int Project_readNumberOfProjects(ScrumContext * ctx, size_t * n)
{
  return SCRUM_ERROR;
}

/******************************************************************************
 * FUNCTION:	    Project_readAllProjectIds
 *
 * DESCRIPTION:	    Read the ScrumObjectIdentifiers of all projects in the
 *		    database into the array pointed to by `projects'.
 *
 * ARGUMENTS:	    n: The size of the array `projects'.
 *		    projects: Array of size `n', for returning the id fields of
 *			all the projects in the database.
 *
 * RETURN:	    int -- SCRUM_OK if no errors occurred.
 ***/
int Project_readAllProjectIds(ScrumContext * ctx, size_t n,
			      ScrumObjectIdentifier projects[n]);

/*****************************************************************************/
