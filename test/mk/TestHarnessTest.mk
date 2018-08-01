###############################################################################
# NAME:		    TestHarnessTest.mk
#
# AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
#
# DESCRIPTION:	    This module is for testing the Test Harness.
#
# CREATED:	    07/31/2018
#
# LAST EDITED:	    07/31/2018
###

MODULE:=TestHarness
CFLAGS += -I test/

obj-$(MODULE):=test/$(MODULE)Test/$(MODULE)Test.o \
test/TestHarness.o

# all:
# 	$(CC) $(CFLAGS) -E test/$(MODULE)Test/$(MODULE)Test.c -o \
# 		test/$(MODULE)Test/$(MODULE)Test.i

#: Run the test, then clean.
all: $(MODULE)Test $(MODULE)clean

#: Run the test.
$(MODULE)Test: test/$(MODULE)Test/$(MODULE)Test
	-./test/$(MODULE)Test/$(MODULE)Test

#: Generate the test executable.
test/$(MODULE)Test/$(MODULE)Test: $(obj-$(MODULE))

#: Generate dependencies
$(obj-$(MODULE)): force

force:

#: Remove any files generated by this Makefile
$(MODULE)clean:
	rm -f test/$(MODULE)Test/$(MODULE)Test
	rm -f $(obj-$(MODULE))

##############################################################################
