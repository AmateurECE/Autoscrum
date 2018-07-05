/******************************************************************************
 * NAME:	    devClient.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This unit contains the main() function for the Autoscrum
 *		    development client. This source is not to be built or used
 *		    by the end user.
 *
 * CREATED:	    07/01/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include "throw.h"
#include "devClientConfig.h"
#include "autoscrumServer.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define MODULE "devClient: "
#define ERR_USAGE \
  "Usage: client {command} [options...]"
#define ERR_SERVER \
  "Error on the server side"

/******************************************************************************
 * MAIN
 ***/

int main(int argc, char * argv[]) {

  /* In the real client, we would begin by verifying command line arguments. */
  if (argc < 2)
    throw(MODULE""ERR_USAGE, 1);

  /* First, read in our configuration information */
  devClientConfig * cfg = createConfig();

  /* Connect to the autoscrum server */
  autoscrumServer * server = autoscrumConnect(cfg->hostname, cfg->port);

  /* Issue our command to the server */
  int bytes = 0;
  if ((bytes = autoscrumCommand(server, --argc, ++argv)) < 0)
    throw(MODULE""ERR_SERVER, 1);

  /* Disconnect from the server */
  autoscrumDisconnect(&server);

  /* Cleanly free the configuration data */
  deleteConfig(&cfg);
}

/*****************************************************************************/
