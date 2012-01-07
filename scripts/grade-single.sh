#!/bin/bash


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

REPO=$1

git clone git@github.com:uchicago-cmsc23300/chirc.git

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone chirc repository"
    exit 1
fi

git clone git@github.com:uchicago-cmsc23300-students/$REPO.git

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone your repository ($REPO)"
    exit 1
fi

cd $REPO
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
echo "Running tests..."
python -c "import tests.runners; tests.runners.grade_runner(csv=False, exe='../$REPO/chirc')"

cd ../ > /dev/null


