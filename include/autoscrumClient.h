/******************************************************************************
 * NAME:	    autoscrumClient.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the prototypes for interacting with the
 *		    autoscrumClient module.
 *
 * CREATED:	    07/05/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

#ifndef __ET_AUTOSCRUMCLIENT_H__
#define __ET_AUTOSCRUMCLIENT_H__

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdint.h>

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  int socketfd;
  char * commandBuffer;

} autoscrumClient;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Initialize the autoscrumClient interface */
extern autoscrumClient * autoscrumInit(uint16_t port);

/* Wait for connections on `port.' Returns when a connection has been received.
 */
extern autoscrumClient * autoscrumWait(autoscrumClient * client);

/* Receive commands from the client. Fills the .commandBuffer member of the
 * struct, and returns the number of bytes read, or -1 if an error occurred.
 */
extern size_t autoscrumReceive(autoscrumClient * client);

/* Close the connection to the client */
extern void autoscrumDisconnect(autoscrumClient ** client);

#endif /* __ET_AUTOSCRUMCLIENT_H__ */

/*****************************************************************************/
