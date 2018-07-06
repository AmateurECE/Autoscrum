/******************************************************************************
 * NAME:	    autoscrumClient.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains a module for communicating with
 *		    autoscrum clients.
 *
 * CREATED:	    07/05/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "autoscrumClient.h"
#include "throw.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#ifdef CONFIG_DEBUG
#   define CONFIG_DEBUG_AUTOSCRUMCLIENT
#endif

#define MODULE "autoscrumClient"

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    autoscrumInit
 *
 * DESCRIPTION:	    Initialize the autoscrum server.
 *
 * ARGUMENTS:	    port: (uint16_t) Initialize the server to listen here.
 *
 * RETURN:	    autoscrumClient * -- This struct is only meant to be passed
 *		    into autoscrumWait.
 *
 * NOTES:	    none.
 ***/
extern autoscrumClient * autoscrumInit(uint16_t port)
{
  /* Initialize socket and data */
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family   = AF_INET;
  addr.sin_port	    = htons(port);
  addr.sin_addr.s_addr	= INADDR_LOOPBACK;
  int socketfd = socket(PF_INET, SOCK_STREAM, 0);

  /* Bind and configure listener */
  if (bind(socketfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)))
    throw(MODULE"Could not bind to port.", NULL);
  if (listen(socketfd, 10))
    throw(MODULE"Could not configure listening port.", NULL);

  /* Create our return */
  autoscrumClient * client = NULL;
  if ((client = malloc(sizeof(autoscrumClient))) == NULL)
    throw(MODULE"Could not malloc return struct.", NULL);
  *client = (autoscrumClient){.socketfd = socketfd, .commandBuffer = NULL};

  return client;
}

/******************************************************************************
 * FUNCTION:	    autoscrumWait
 *
 * DESCRIPTION:	    Opens up to listen for connections on `port.' This function
 *		    blocks program flow until a connection has been received.
 *
 * ARGUMENTS:	    port: (uint16_t) The port to wait on.
 *
 * RETURN:	    autoscrumClient * -- Pointer to the client object we
 *		    have a connection with.
 *
 * NOTES:	    none.
 ***/
autoscrumClient * autoscrumWait(autoscrumClient * client)
{
  if (client == NULL)
    return NULL;

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr_in));
  socklen_t len = sizeof(struct sockaddr_in);
  int clientfd = accept(client->socketfd, (struct sockaddr *)&addr, &len);
#ifdef CONFIG_DEBUG_AUTOSCRUMCLIENT
  printf(MODULE"Connection: %s:%d\n", inet_ntoa(addr.sin_addr),
	 ntohs(addr.sin_port));
#endif

  /* Allocate and populate return */
  autoscrumClient * ret = NULL;
  if ((ret = malloc(sizeof(autoscrumClient))) == NULL)
    throw(MODULE"Could not malloc return struct.", NULL);
  *ret = (autoscrumClient){.socketfd = clientfd, .commandBuffer = NULL};

  return ret;
}

/* 
 */
/******************************************************************************
 * FUNCTION:	    autoscrumReceive
 *
 * DESCRIPTION:	    Receive commands from the client. Fills the .commandBuffer
 *		    member of the struct, and returns the number of bytes read,
 *		    or -1 if an error occurred.
 *
 * ARGUMENTS:	    client: (autoscrumClient *) Object representing a
 *			connection to a client.
 *
 * RETURN:	    size_t -- The number of bytes read from the socket.
 *
 * NOTES:	    
 ***/
extern size_t autoscrumReceive(autoscrumClient * client)
{
  if (client == NULL)
    return 0;

  /* Read the size of the command from the client */
  char buffer[2];
  if (read(client->socketfd, buffer, 2) != 2)
    throw(MODULE"Could not read from the client.", 0);
  size_t size = (buffer[0] << 8) + buffer[1];

  /* Read the command from the client */
  if ((client->commandBuffer = malloc(size)) == NULL)
    throw(MODULE"Could not malloc space for command.", 0);
  if ((unsigned)read(client->socketfd, client->commandBuffer, size) != size)
    throw(MODULE"Could not read command from client.", 0);
  (client->commandBuffer)[size] = '\0';

  return size;
}

/******************************************************************************
 * FUNCTION:	    autoscrumDisconnect
 *
 * DESCRIPTION:	    Disconnect from the client and free any allocated
 *		    resources.
 *
 * ARGUMENTS:	    client: (autoscrumClient **) Object representing a
 *			connection to a client.
 *
 * RETURN:	    void
 *
 * NOTES:	    none.
 ***/
void autoscrumDisconnect(autoscrumClient ** client)
{
  if (client == NULL || *client == NULL)
    return;

  close((*client)->socketfd);
  if ((*client)->commandBuffer != NULL)
    free((*client)->commandBuffer);
  free(*client);
  *client = NULL;
}

/*****************************************************************************/
