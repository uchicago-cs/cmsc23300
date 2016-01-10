#!/bin/bash

# Script to grade a single repository.
#
# Usage:
# 
#     grade-chirc.sh <team> [<commit>]
# 
# First parameter is your team identifier
#
# Optional second parameter is the commit you want to build.
# (if none is specified, the head of the master branch will be built)

set -o pipefail

if [ "X$1" == "X" ];
then
	echo "ERROR: Please specify a team."
	exit 1
fi

TEAM=$1

if ! chisubmit student team show $TEAM 2>&1 > /dev/null;
then
    echo "No such team: $TEAM"
    exit 1
fi

echo -n "Cloning your repository... "
 
REPO_DIR=$(chisubmit student team repo-pristine-clone $TEAM 2>&1 | grep -o "/tmp/.*")

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone the repository for $TEAM"
    exit 1
fi
echo "done."

if [ $# -eq 2 ];
then
	CHECKOUT=$2
else
	CHECKOUT=master
fi

cd $REPO_DIR/chirc

if [ $CHECKOUT != "master" ];
then
	git rev-list --all | grep $CHECKOUT > /dev/null

	if [ "$?" -ne "0" ]; 
	then
		echo "ERROR: Repository $TEAM does not have a $CHECKOUT commit."
		exit 1
	else
		git checkout $CHECKOUT > /dev/null 2>&1
	fi
else
	git checkout master > /dev/null 2>&1
fi

echo -n "Checking for chirc files... "
for CHIRC_FILE in $REPO_DIR/chirc/ $REPO_DIR/chirc/Makefile $REPO_DIR/chirc/src/;
do
    if [ ! -e $CHIRC_FILE ];
    then
        echo "ERROR: Your repository doesn't seem to contain a valid chirc directory"
        exit 1
    fi
done
echo "done."

echo -n "Building $TEAM chirc..."

BUILD_LOG="/tmp/chirc-build-$USER-$$.log"
touch $BUILD_LOG
chmod 600 $BUILD_LOG

make clean > $BUILD_LOG 2>&1
make chirc >> $BUILD_LOG 2>&1
if [ "$?" -ne "0" ]; 
then
	echo "ERROR: Your project did not build."
    echo "       Build log is in $BUILD_LOG"
    exit 1
else
    rm $BUILD_LOG
fi	

echo "done."


echo "Running tests..."

CHIRC_DIR=$(mktemp -d)

git clone https://github.com/uchicago-cs/chirc.git $CHIRC_DIR > /dev/null 2>&1

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone chirc upstream repository"
    exit 1
fi

python3 -m pytest $CHIRC_DIR/tests/ --chirc-exe=$REPO_DIR/chirc/chirc --chirc-loglevel=-1 --randomize-ports --json=$REPO_DIR/chirc/results.json
python3 $CHIRC_DIR/tests/grade.py --report-file=$REPO_DIR/chirc/results.json

rm -rf $CHIRC_DIR
rm -rf $REPO_DIR

echo "DONE"


