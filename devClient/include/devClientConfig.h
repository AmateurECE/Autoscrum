/******************************************************************************
 * NAME:	    devClientConfig.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Configuration module for the development client.
 *
 * CREATED:	    07/01/2018
 *
 * LAST EDITED:	    07/05/2018
 ***/

#ifndef __ET_DEVCLIENTCONFIG_H__
#define __ET_DEVCLIENTCONFIG_H__

/******************************************************************************
 * INCLUDES
 ***/

#include <stdint.h>

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  char * hostname;
  uint16_t  port;

} devClientConfig;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern devClientConfig * createConfig(void);
extern void deleteConfig(devClientConfig ** cfg);

#endif /* __ET_DEVCLIENTCONFIG_H__ */

/*****************************************************************************/
