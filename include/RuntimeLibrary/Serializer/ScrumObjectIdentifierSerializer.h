/******************************************************************************
 * NAME:	    ScrumObjectIdentifierSerializer.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    This header is an interface to segregate the implementation
 *                  of the serialization of objects from their function. This
 *                  allows the implementation of the serializer to have zero
 *                  dependencies--it could be a simple binary file writer, a
 *                  database, whatever.
 *
 * CREATED:	    07/29/2018
 *
 * LAST EDITED:	    08/16/2018
 ***/

/******************************************************************************
 * NOTE:
 *
 * In the current implementation of the serializer, this module is not used.
 * Do not call these functions, they are stubbed out and will always return
 * error codes. This interface is here in case another implementation requires
 * it.
 ***/

#ifndef __ET_SCRUMOBJECTIDENTIFIERSERIALIZER__
#define __ET_SCRUMOBJECTIDENTIFIERSERIALIZER__

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* This function assumes nothing of the state of the memory of `id'. */
int ScrumObjectIdentifier_writeId(ScrumObjectIdentifier * id);

/* Before calling this function, id->id should be set. If it is not, this fn
 * will immediately return non-zero (error).
 */
int ScrumObjectIdentifier_readId(ScrumObjectIdentifier * id);

int ScrumObjectIdentifier_writePath(ScrumObjectIdentifier * path);

int ScrumObjectIdentifier_readPath(ScrumObjectIdentifier * path);

#endif /* __ET_SCRUMOBJECTIDENTIFIERSERIALIZER__ */

/*****************************************************************************/
