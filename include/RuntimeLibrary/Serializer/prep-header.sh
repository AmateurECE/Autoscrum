objName=`echo $1 | sed -e 's/\.h//'`
oldDesc=" \* DESCRIPTION:"
newDesc=" * DESCRIPTION:	    This header is an interface to segregate \
the implementation"'\n'"\
 *		    of the serialization of $objName objects from\\n\
 *		    their function. This allows the implementation of the\\n\
 *		    serializer to have zero dependencies--it could be a \
simple\\n\
 *		    binary file writer, a database, whatever.\\n\
"

sed -i '' -e 's/'"$oldDesc"'/'"$newDesc"'/' $1
