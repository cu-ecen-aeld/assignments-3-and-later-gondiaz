#!/bin/bash

if [ $# != 2 ]
  then
    echo "2 arguments required: filesdir searchstr"
    exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d $filesdir ]
  then
    echo "Directory $filesdir does not exit"
    exit 1
fi


X=$(find $filesdir -type f | wc -l)
Y=$(find $filesdir -type f | xargs grep -r $searchstr | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"
exit 0
