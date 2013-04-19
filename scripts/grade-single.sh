#!/bin/bash

# Script to grade a single repository.
#
# Usage:
# 
#     grade-single.sh <repository> [<tag>]
# 
# First parameter is the name of your repository.
# Optional second parameter is the tag you want to build.
# (if none is specified, the master branch will be built)if [ $# -eq 2 ];

if [ `ls -1 | wc --lines` -ne "0" ];
then
	echo "ERROR: I need to run in an empty directory"
	exit 1
fi

if [ "X$1" == "X" ];
then
	echo "ERROR: Please specify a repository name."
	exit 1
fi

if [ $# -eq 2 ];
then
	TAG=$2
else
	TAG=master
fi

REPO=$1

git clone git@github.com:uchicago-cs/chirc.git

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone chirc repository"
    exit 1
fi

git clone git@github.com:uchicago-cs/$REPO.git

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone your repository ($REPO)"
    exit 1
fi

cd $REPO

if [ $TAG != "master" ];
then
	git tag | grep $TAG > /dev/null

	if [ "$?" -ne "0" ]; 
	then
		echo "ERROR: Repository $REPO does not have a $TAG tag."
		exit 1
	else
		git checkout $TAG
	fi
else
	git checkout master
fi

make chirc 2>&1 > build.log
if [ "$?" -ne "0" ]; 
then
	echo "ERROR: Your project did not build."
        echo "       Build log is in ./$REPO/build.log"
else
	echo "$REPO built succesfully"
fi	

cd ../ > /dev/null

cd chirc
CHIRCPYPATH="$(pwd)"
echo "Running tests..."
python -c "import sys; sys.path.insert(0, '$CHIRCPYPATH'); import tests.runners; tests.runners.grade_runner(csv=False, randomize_ports=1, exe='../$REPO/chirc')"

cd ../ > /dev/null


