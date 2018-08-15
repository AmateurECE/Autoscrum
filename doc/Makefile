###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the documentation.
#
# CREATED:	    06/07/2018
#
# LAST EDITED:	    07/10/2018
###

TGTS = \
workflow \
server-arch \
issues

.PHONY: all clean force

# To avoid accidentally building the whole document package, we force the user
# to explicitly specify `all' or a specific document, by name.
default: force
	@>&2 echo "Error: Must specify a target. If building the whole doc" \
	"package, invoke with target \`all'"

all: $(TGTS)

$(TGTS): force
	pdflatex $@.tex
	pdflatex $@.tex

clean:
	rm -f *.out
	rm -f *.aux
	rm -f *.log
	rm -f *.toc

force:

###############################################################################
