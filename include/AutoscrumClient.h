/******************************************************************************
 * NAME:	    AutoscrumClient.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the prototypes for interacting with the
 *		    autoscrumClient module.
 *
 * CREATED:	    07/05/2018
 *
 * LAST EDITED:	    07/15/2018
 ***/

#ifndef __ET_AUTOSCRUMCLIENT__
#define __ET_AUTOSCRUMCLIENT__

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

} AutoscrumClient;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Initialize the autoscrumClient interface */
extern AutoscrumClient * AutoscrumClient_init(uint16_t port);

/* Wait for connections on `port.' Returns when a connection has been received.
 */
extern AutoscrumClient * AutoscrumClient_wait(AutoscrumClient * client);

/* Receive commands from the client. Fills the .commandBuffer member of the
 * struct, and returns the number of bytes read, or -1 if an error occurred.
 */
extern size_t AutoscrumClient_receive(AutoscrumClient * client);

/* Close the connection to the client */
extern void AutoscrumClient_disconnect(AutoscrumClient ** client);

#endif /* __ET_AUTOSCRUMCLIENT_H__ */

/*****************************************************************************/
