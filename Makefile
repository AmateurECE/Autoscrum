###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    The Makefile for the Autoscrum Server. This makefile will
#		    be replaced by an AUTOMAKE script in production.
#
# CREATED:	    07/01/2018
#
# LAST EDITED:	    07/02/2018
###
# TODO: Replace this Make system with Automake.

CONFIG_DEV=1

CFLAGS=-g -Wall -O0 -Wextra -I./devClient/include
CC=gcc

# This Makefile sets the obj-c list
include devClient/Makefile

# This Makefile sets the obj-s list
include source/Makefile

c-tgts=$(addprefix devClient/,$(obj-c))
s-tgts=$(addprefix source/,$(obj-s))

dev: devClient/devClient source/autoscrum
	@mv devClient/devClient ./client
	@mv source/autoscrum ./autoscrum

devClient/devClient: $(c-tgts)

source/autoscrum: $(s-tgts)

$(c-tgts): force

$(s-tgts): force

force:

clean:
	rm -f source/*.o
	rm -f devClient/*.o
	rm -rf devClient/*.dSYM
	rm -f autoscrum
	rm -f client

###############################################################################
