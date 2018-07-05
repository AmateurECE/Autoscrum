/******************************************************************************
 * NAME:	    autoscrumServer.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Module for communicating with the autoscrum server.
 *
 * CREATED:	    07/01/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

#ifndef __ET_AUTOSCRUMSERVER__
#define __ET_AUTOSCRUMSERVER__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  int socketfd;
  char * returnBuffer;

} autoscrumServer;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern autoscrumServer * autoscrumConnect(char * hostname, uint16_t port);
extern int autoscrumCommand(autoscrumServer * server, int argc,
			    char * argv[argc]);
extern void autoscrumDisconnect(autoscrumServer ** server);

#endif /* __ET_AUTOSCRUMSERVER__ */

/*****************************************************************************/
