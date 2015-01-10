#!/bin/bash

# Script to grade a single repository.
#
# Usage:
# 
#     grade-chirc.sh <team> [<tag>]
# 
# First parameter is your team identifier
#
# Optional second parameter is the tag you want to build.
# (if none is specified, the master branch will be built)


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
	TAG=$2
else
	TAG=master
fi

cd $REPO_DIR/chirc

if [ $TAG != "master" ];
then
	git tag | grep $TAG > /dev/null

	if [ "$?" -ne "0" ]; 
	then
		echo "ERROR: Repository $TEAM does not have a $TAG tag."
		exit 1
	else
		git checkout $TAG > /dev/null 2>&1
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
    fi
done
echo "done."

echo -n "Building $TEAM chirc..."

make chirc > chirc-build.log 2>&1
if [ "$?" -ne "0" ]; 
then
	echo "ERROR: Your project did not build."
    echo "       Build log is in chirc-build.log"
    exit 1
fi	

echo "done."


echo "Running tests..."

CHIRC_DIR=$(mktemp -d)

git clone git@github.com:uchicago-cs/chirc.git $CHIRC_DIR > /dev/null 2>&1

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone chirc upstream repository"
    exit 1
fi

python -c "import sys; sys.path.insert(0, '$CHIRCPYPATH'); import tests.runners; tests.runners.grade_runner(csv=False, randomize_ports=1, exe='$REPO_DIR/chirc/chirc')"

rm -rf $CHIRC_DIR
rm -rf $REPO_DIR

echo "DONE"


