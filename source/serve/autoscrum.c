/******************************************************************************
 * NAME:	    autoscrum.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the `main' function of the autoscrum
 *		    server.
 *
 * CREATED:	    07/05/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>

#include "throw.h"
#include "autoscrumClient.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define MODULE "Autoscrum"

/******************************************************************************
 * MAIN
 ***/

int main() {

  /* Initialize the server */
  autoscrumClient * server = autoscrumInit(CONFIG_DEFAULT_PORT);

  /* Wait for a connection */
  while (1) {
    autoscrumClient * client = autoscrumWait(server);
    if (autoscrumReceive(client) == 0)
      throw(MODULE"No message received from client.", 1);
    printf("Client says: %s\n", client->commandBuffer);
    autoscrumDisconnect(&client);
  }

  autoscrumDisconnect(&server);
}

/*****************************************************************************/
