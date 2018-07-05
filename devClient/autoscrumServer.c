/******************************************************************************
 * NAME:	    autoscrumServer.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Implements the autoscrumServer module. This module is
 *		    responsible for communicating with the autoscrum server.
 *
 * CREATED:	    07/01/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "throw.h"
#include "autoscrumServer.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#ifdef CONFIG_DEBUG
#   define CONFIG_DEBUG_AUTOSCRUMSERVER
#endif

#define MODULE "autoscrumServer: "

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static char * makeCommand(int argc, char * argv[argc], size_t * total);
static char * myStrcat(char * dest, char * src);

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    autoscrumConnect
 *
 * DESCRIPTION:	    create a static connection to the autoscrum server.
 *
 * ARGUMENTS:	    serverIp: (uint8_t[4]) The server's IPv4 address.
 *		    port: (uint16_t) The port to connect on.
 *
 * RETURN:	    autoscrumServer * -- module object, contains information
 *		    necessary to command the server, as well as buffers for
 *		    holding server responses.
 *
 * NOTES:	    none
 ***/
autoscrumServer * autoscrumConnect(char * hostname, uint16_t port)
{
  struct sockaddr_in addr;
  struct hostent * host = NULL;

  /* Get host information */
  if ((host = gethostbyname(hostname)) == NULL)
    throw(MODULE"Could not get information from host name", NULL);

  /* Attempt to create a socket */
  int socketfd = socket(PF_INET, SOCK_STREAM, 0);
  if (socketfd == -1)
    throw(MODULE"Could not create socket", NULL);

  /* Setup our sockaddr_in struct */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family   = AF_INET;
  addr.sin_port	    = htons(port);
  addr.sin_addr.s_addr = *(long *)(host->h_addr);

  /* Connect to the server */
  if (connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
    close(socketfd);
    throw(MODULE"Could not connect to host", NULL);
  }
#ifdef CONFIG_DEBUG_AUTOSCRUMSERVER
  printf(MODULE"Successfully connected to server.");
#endif

  /* Allocate and initialize the return object */
  autoscrumServer * server = NULL;
  if ((server = malloc(sizeof(autoscrumServer))) == NULL)
    throw(MODULE"malloc returned NULL", NULL);
  server->socketfd = socketfd;
  server->returnBuffer = NULL;

  return server;
}

/******************************************************************************
 * FUNCTION:	    autoscrumCommand
 *
 * DESCRIPTION:	    Issue a command to the autoscrum server. This function
 *		    unloads the burden of having to regulate communications
 *		    with the autoscrum server. The arguments are sent to the
 *		    server, and the server's response is recorded in
 *		    server->returnBuffer. The size of `returnBuffer' is
 *		    returned.
 *
 * ARGUMENTS:	    server: (autoscrumServer *) The internal server object.
 *		    argc: (int) The number of arguments in argv.
 *		    argv: (char * []) Array of '\0' terminated strings. These
 *			are the arguments to the server.
 *
 * RETURN:	    int -- The size of `server->returnBuffer'. If an error
 *			occured, -1 will be returned.
 *
 * NOTES:	    none.
 ***/
int autoscrumCommand(autoscrumServer * server, int argc, char * argv[argc])
{
  if (server == NULL)
    return -1;

  size_t total = 0;
  /* TODO: change makeCommand to use pascal-style strings */
  char * command = makeCommand(argc, argv, &total);
#ifdef CONFIG_DEBUG_AUTOSCRUMSERVER
  printf(MODULE"Command is: %s\n", command);
#endif

  /* Write the command to the socket */
  if ((unsigned)write(server->socketfd, command, total) != total)
    throw(MODULE"Error sending to server.", -1);
#ifdef CONFIG_DEBUG_AUTOSCRUMSERVER
  printf(MODULE"Successfully wrote to server.\n");
#endif
  free(command);

  /* Read sizeof(size_t) bytes from the socket into &size */
  char buffer[2];
  if (read(server->socketfd, buffer, 2) != 2)
    throw(MODULE"No response from server.", -1);
  uint16_t size = (buffer[1] << 8) + buffer[0];
#ifdef CONFIG_DEBUG_AUTOSCRUMSERVER
  printf(MODULE"Reading %d bytes from server...\n", size);
#endif

  /* Read `size' bytes into &buff */
  if ((server->returnBuffer = malloc(size + 1)) == NULL)
    throw(MODULE"NULL response from malloc call.", -1);
  if (read(server->socketfd, server->returnBuffer, size) != size)
    throw(MODULE"Problem reading server response.", -1);
  *(server->returnBuffer + size) = '\0';
#ifdef CONFIG_DEBUG_AUTOSCRUMSERVER
  printf(MODULE"Successfully read %d bytes from server.\n", size);
#endif

  return size;
}

/******************************************************************************
 * FUNCTION:	    autoscrumDisconnect
 *
 * DESCRIPTION:	    Close and free any resources associated with the
 *		    autoscrumServer object.
 *
 * ARGUMENTS:	    server: (autoscrumServer) the resource to free.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none
 ***/
void autoscrumDisconnect(autoscrumServer ** server)
{
  if (*server == NULL)
    return;

  close((*server)->socketfd);
  free(*server);
  *server = NULL;
}

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    makeCommand
 *
 * DESCRIPTION:	    This function allocates memory to join all the strings in
 *		    `argv' with a space.
 *
 * ARGUMENTS:	    argc: (int) The number of strings
 *		    argv: (char * [argc]) The strings
 *		    total: (size_t *) Place to store the length of the new str.
 *
 * RETURN:	    char * -- Pointer to allocated memory containing all the
 *		    strings in `argv' joined by a space.
 *
 * NOTES:	    none
 ***/
static char * makeCommand(int argc, char * argv[argc],
			  size_t * total)
{
  for (int i = 0; i < argc; i++)
    *total += strlen(argv[i]);
  *total += argc + 2;

  char * command = NULL;
  if ((command = malloc(*total)) == NULL)
    throw(MODULE"malloc returned NULL in makeCommand", NULL);

  /* This session layer protocol uses Pascal-based strings over the pipe. Here,
   * we are writing the size of the string, not including the two bytes eaten
   * by the size parameter, to the first two bytes of the string.
   */
  command = (char[]){(char)((*total - 2) >> 8),
	      (char)(*total - 2)};
  char * temp = command + 2;
  for (int i = 0; i < argc; i++)
    temp = myStrcat(temp, argv[i]);
  *(temp - 1) = '\0'; /* Make sure to null terminate! */

  return command;
}

/******************************************************************************
 * FUNCTION:	    myStrcat
 *
 * DESCRIPTION:	    Concatenate a string and return a pointer to the last char
 *		    before the '\0'. This is for a string concatenating
 *		    algorithm that works in O(2n). We do no error checking in
 *		    here.
 *
 * ARGUMENTS:	    dest: (char *) The destination string.
 *		    src: (char *) The source string.
 *
 * RETURN:	    char * -- A pointer to the last char before '\0' in the new
 *		    string.
 *
 * NOTES:	    O(m + n); m = strlen(dest), n = strlen(src)
 ***/
static char * myStrcat(char * dest, char * src)
{
  while ((*dest++ = *src++));
  *(dest - 1) = ' ';
  return dest;
}

/*****************************************************************************/
