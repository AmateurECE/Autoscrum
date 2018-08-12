/******************************************************************************
 * NAME:	    CompileConfig.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This file contains a number of switches which control
 *		    whether certain features are compiled into the Autoscrum
 *		    binaries.
 *
 * CREATED:	    07/12/2018
 *
 * LAST EDITED:	    08/04/2018
 ***/

#ifndef __ET_COMPILECONFIG__
#define __ET_COMPILECONFIG__

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#if !defined(SCRUM_OK)
#   define SCRUM_OK 0
#endif

#if !defined (SCRUM_ERROR)
#   define SCRUM_ERROR 1
#endif

#endif /* __ET_COMPILECONFIG__ */

/*****************************************************************************/
