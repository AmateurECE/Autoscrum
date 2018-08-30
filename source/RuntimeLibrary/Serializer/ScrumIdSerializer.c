/******************************************************************************
 * NAME:	    ScrumIdSerializer.c
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Serializes ScrumId objects.
 *
 * CREATED:	    08/16/2018
 *
 * LAST EDITED:	    08/16/2018
 ***/

/******************************************************************************
 * NOTES
 ***/

/* TODO: Use v2 calls in SQLite3. */
/* TODO: Determine if initNewDb is necessary */
/* TODO: VARCHAR(max), not TEXT */

/* The SQLite3 Execution flow:
 * -	sqlite3_prepare_v2() -> sqlite3_stmt
 * -	sqlite3_step()
 * -	sqlite3_column()
 * -	sqlite3_finalize()

/*****************************************************************************/
