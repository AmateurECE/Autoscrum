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
# LAST EDITED:	    08/23/2018
###
# TODO: Replace this Make system with Automake.

CONFIG_DEV=1

export CFLAGS:=-g -Wall -O0 -Wextra -I./include
# devClient/client: CFLAGS += -I./devClient/include -D CONFIG_DEFAULT_PORT=8082
source/RuntimeLibrary/libscrum.a: CFLAGS += -fPIC
export LDFLAGS:=`pkg-config --libs sqlite3` -shared
export CC:=gcc
# export BINARIES=devClient/client source/serve/autoscrum

# # This Makefile sets the obj-c list
# include devClient/Makefile

# # This Makefile sets the obj-s list
# include source/serve/Makefile

# This Makefile sets the obj-lib list
include source/RuntimeLibrary/Makefile

test-mkdir:=test/mk
test-files:=$(shell ls $(test-mkdir))
test-tgts:=$(patsubst %.mk,%,$(test-files))

# c-tgts=$(addprefix devClient/,$(obj-c))
# s-tgts=$(addprefix source/serve/,$(obj-s))
lib-tgts=$(addprefix source/RuntimeLibrary/,$(obj-lib))

test: libscrum $(test-tgts)

$(test-tgts):
	@$(MAKE) -f $(test-mkdir)/$@.mk

libscrum: source/RuntimeLibrary/libscrum.a
	@mkdir -p ./lib/
	@mv -f source/RuntimeLibrary/libscrum.a ./lib

source/RuntimeLibrary/libscrum.a: $(lib-tgts)
	ar rcs $@ $(lib-tgts)

$(lib-tgts): force

# dev: devClient/client source/serve/autoscrum
# 	@mv $^ ./

# devClient/client: $(c-tgts)

# source/serve/autoscrum: $(s-tgts)

# $(c-tgts): force

# $(s-tgts): force

force:

clean:
	ctags -e -R . # Generate ctags
	rm -f `find $(PWD) -name *.o`
	rm -rf `find $(PWD) -name *.dSYM`
	$(MAKE) -f source/Stack/Makefile clean
	rm -f autoscrum
	rm -f client

###############################################################################
