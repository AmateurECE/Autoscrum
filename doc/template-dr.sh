###############################################################################
# NAME:		    template-dr.sh
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    A Shell script which creates a blank template for a design
#		    requirements document.
#
# CREATED:	    06/10/2018
#
# LAST EDITED:	    06/13/2018
###

###############################################################################
# FUNCTIONS
###

error() {
    RED="\033[31;1m"
    NC="\033[0m"
    >&2 echo -e $RED"ERROR"$NC": $@"
    exit
}

# A little pseudo-lambda expression I use to make regular expressions later in
# the script.
captureGroup() {
    echo '\('$@':[[:blank:]]*\)'
}

###############################################################################
# MAIN
###

drDir="design-requirements"

# List all LaTeX documents in the $drDir directory.
if [[ ! -d $drDir ]]; then
    error "The $drDir directory is not present in the current" \
	  "directory"
fi
entries=`ls -1 $drDir | grep '\.tex' | grep '[[:digit:]]'`

# Parse filename into an array of integers.
ints=""
for i in $entries; do
    ints="$ints "`echo $i | sed -e 's/dr-\([[:digit:]]*\)\.tex/\1/'`
done

# Find the greatest integer in the array, then increment it by one.
max=0
for i in $ints; do
    if [[ "$i" > "$max" ]]; then
	max=$i
    fi
done
max=$(expr $max + 1)
if [[ "$max" -lt "10" ]]; then
    max="0"$max
fi

# Copy the template into the $drDir directory.
templateFilename="template-dr.tex"
if [[ ! -f $templateFilename ]]; then
    error "The template is not located in the current directory."
fi
cp $templateFilename $drDir
if [[ "$?" != "0" ]]; then
    error "Could not copy the template into $drDir."
fi

# Rename it to 'dr-XX' where XX is replaced with the max.
newPath="$drDir/dr-$max.tex"
mv $drDir/$templateFilename $newPath
if [[ "$?" != "0" ]]; then
    error "Could not rename template file."
fi

# Replace every instance of 'dr-XX' in the file with the file's name.
# sed -i '' 's/\(dr\|DR\)-XX/\1-'$max'/g' $newPath
sed -Ei '' 's/(dr|DR)-XX/\1-'$max'/g' $newPath

# Replace the CREATED field
date=`date +%m/%d/%Y`
created='CREATED'
lastEdited='LAST EDITED'
group=`captureGroup $created`
dateGroup='[0-9]*/[0-9]*/[0-9]*'
sed -i '' 's|'"${group}${dateGroup}"'|\1'$date'|' $newPath
# ...and LAST EDITED field
group=`captureGroup $lastEdited`
sed -i '' 's|'"${group}${dateGroup}"'|\1'$date'|' $newPath

# Update the Date field in the only entry in the Revision History table.
regex='Date No, Year'
date=`date '+%b %d, %Y'`
sed -i '' 's|& '"$regex"' &|\& '"$date"' \&|' $newPath

###############################################################################
