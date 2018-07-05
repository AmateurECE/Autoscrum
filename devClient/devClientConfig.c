/******************************************************************************
 * NAME:	    devClientConfig.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Implements the devClientConfig module.
 *
 * CREATED:	    07/01/2018
 *
 * LAST EDITED:	    07/01/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdlib.h>

#include "devClientConfig.h"
#include "throw.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define MODULE "devClientConfig: "
/* 127.0.0.1 - The loopback address */
#define CONFIG_DEFAULT_HOSTNAME "localhost"
#define CONFIG_DEFAULT_PORT 8081

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    createConfig
 *
 * DESCRIPTION:	    Initializes the devClientConfig module, preparing the
 *		    devClient configuration information from required sources,
 *		    and returning a pointer to a struct which contains all
 *		    relevant client configuration information.
 *
 * ARGUMENTS:	    void
 *
 * RETURN:	    devClientConfig * -- Struct containing configuration data.
 *
 * NOTES:	    none
 ***/
devClientConfig * createConfig(void)
{
  devClientConfig * cfg = NULL;
  if ((cfg = malloc(sizeof(devClientConfig))) == NULL)
    throw(MODULE"malloc returned null in createConfig", NULL);

  /* Initialize with the (currently) static data */
  cfg->hostname	= CONFIG_DEFAULT_HOSTNAME;
  cfg->port	= CONFIG_DEFAULT_PORT;

  return cfg;
}

/******************************************************************************
 * FUNCTION:	    deleteConfig
 *
 * DESCRIPTION:	    Free any memory associated with the devClientConfig object.
 *
 * ARGUMENTS:	    cfg: (devClientConfig) devClient configuration data object.
 *
 * RETURN:	    void
 *
 * NOTES:	    none
 ***/
void deleteConfig(devClientConfig ** cfg)
{
  if (*cfg == NULL)
    return;

  free(*cfg);
  *cfg = NULL;
}

/*****************************************************************************/
