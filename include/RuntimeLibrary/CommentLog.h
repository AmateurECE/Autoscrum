/******************************************************************************
 * NAME:	    Comment.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the information necessary to manipulate commentLog
 *		    data.
 *
 * CREATED:	    07/14/2018
 *
 * LAST EDITED:	    07/21/2018
 ***/

#ifndef __ET_COMMENT__
#define __ET_COMMENT__

/******************************************************************************
 * INCLUDES
 ***/

#include "list.h"
#include "User.h"

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef list CommentLog;

typedef struct {

  /* TODO: Add time member */
  User author;
  size_t length;
  char * text;

} Comment;

#endif /* __ET_COMMENT__ */

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern CommentLog * CommentLog_create();
extern void CommentLog_destroy(CommentLog * log);
extern void /* TODO: libXML? */ CommentLog_print(CommentLog * log);
extern void CommentLog_add_new(CommentLog * log, Comment * comment);
extern void CommentLog_add_reply(CommentLog * log, Comment * comment,
				 Comment * reply);
extern Comment * CommentLog_remove(/* TODO: CommentLog_remove Parameters */);
extern void CommentLog_traverse(CommentLog * log, void (*callback)(Comment *));

extern Comment * Comment_create();
extern void Comment_destroy(Comment * comment);

/*****************************************************************************/
