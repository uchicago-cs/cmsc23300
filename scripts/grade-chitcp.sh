#!/bin/bash

# Script to grade a single repository.
#
# Usage:
# 
#     grade-chitcp.sh <team> [<commit>]
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

if [ ! -e $REPO_DIR/chitcp ];
then
    echo "ERROR: Your repository doesn't seem to contain a valid chitcp directory"
    exit 1
fi

cd $REPO_DIR/chitcp

if [ $# -eq 2 ];
then
	CHECKOUT=$2
else
	CHECKOUT=master
fi

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

echo -n "Checking for chitcp files... "
for CHITCP_FILE in $REPO_DIR/chitcp/ $REPO_DIR/chitcp/src/ $REPO_DIR/chitcp/src/libchitcp/ $REPO_DIR/chitcp/src/chitcpd/;
do
    if [ ! -e $CHITCP_FILE ];
    then
        echo $CHITCP_FILE
        echo "ERROR: Your repository doesn't seem to contain a valid chitcp directory"
        exit 1
    fi
done
echo "done."

echo -n "Building $TEAM chitcp... "

BUILD_LOG="/tmp/chitcp-build-$USER-$$.log"
touch $BUILD_LOG
chmod 600 $BUILD_LOG

./autogen.sh > $BUILD_LOG 2>&1
./configure >> $BUILD_LOG 2>&1
make clean >> $BUILD_LOG 2>&1
make >> $BUILD_LOG 2>&1
if [ "$?" -ne "0" ]; 
then
	echo "ERROR: Your project did not build."
    echo "       Build log is in $BUILD_LOG"
    exit 1
else
    rm $BUILD_LOG
fi	

echo "done."


echo -n "Building tests... "

CHITCP_DIR=$(mktemp -d)

git clone https://github.com/uchicago-cs/chitcp.git $CHITCP_DIR > /dev/null 2>&1

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone chitcp upstream repository"
    exit 1
fi

cp $CHITCP_DIR/tests/* $REPO_DIR/chitcp/tests/

make tcp-tests > $BUILD_LOG 2>&1
if [ "$?" -ne "0" ]; 
then
	echo "ERROR: The tests did not build."
    echo "       Build log is in $BUILD_LOG"
    exit 1
else
    rm $BUILD_LOG
fi	

echo "done"

echo "Running tests..."

tests/test-tcp --verbose
make grade

rm -rf $CHITCP_DIR
rm -rf $REPO_DIR

echo "DONE"


