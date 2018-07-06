/******************************************************************************
 * NAME:	    throw.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    A simple error reporting API for the development Client.
 *
 * CREATED:	    07/01/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

#ifndef __ET_THROW_H__
#define __ET_THROW_H__

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define throw(str, ret) {			\
    fprintf(stderr, str"\n");			\
    return ret;					\
  }

#endif /* __ET_THROW_H__ */

/*****************************************************************************/
