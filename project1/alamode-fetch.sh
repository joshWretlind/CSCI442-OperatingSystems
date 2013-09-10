#!/bin/bash

# alamode-fetch.sh
# this is the main logic for the program
# Most of what this script does is validate things. The actual data we
# get is in the alamode-generate.sh script

# getInfo basically is the wrapper for the SSH command itself. This
# contains a little bit of validation, but most of that is done 
# before this is ever called.

getInfo () {
    if [ -z $1 ]
    then
        echo "Must call getInfo with a machine to get the info from"
        exit 1
    fi
    if [ ! $# -eq 2 ]
    then
        echo "Too many arguments to getInfo"
        exit 1
    fi
    
    ssh $1 sh ./alamode-generate.sh; rm ./alamode-generate;
}

# Ehat pushCommand does is that it copies over the commands that need to
# ran to the host machine we're running things on, reporting it to their 
# respective locaiton. This is it's own file.
pushCommand () {
    if [ -z $1 ]
    then
        echo "Must call pushCommand with a machine to get the info from"
        exit 1
    fi
    if [ ! $# -eq 2 ]
    then
        echo "Too many arguments to pusgCommand"
        exit 1
    fi
    
    scp ./alamode-generate.sh $1:./alamode-generate.sh
}

while getopts "n:f:" OPTIONS
  do
    case "$OPTIONS" in
	  n)  set isN = "foo"
          if [ ! -z $isF ]
          then
            echo "Cannot set both n and f options -n"
            exit 1            
          else
            if [ ! -z $OPTARG ]
            then
              set REMOTE_MACHINE = $OPTARG
            else
              echo "-n options must be given a host"
              exit 1
            fi
          fi;;
      f)  set isF = "foo"
          if [ ! -z $isN ]
          then
            echo "Cannot set both n and f options -f"
            exit 1  
          fi
          if [ ! -z $READ_FILE ] # Check if we've parsed this flag already
          then
            echo "$0: does not support nultiple -f's"
            exit 1
          else
            if [ ! -z $OPTARG ] # Check to make sure a token was given with this flag
            then
              READ_FILE=$OPTARG
            else
              echo "$0: Must specify a file with hostnames/IPs with -f"
              exit 1
            fi
          fi;;
      
      \?) echo "usage: $0 [-d directory (OPTIONAL)] [-n IP or Name of computer] or [-f File containing names or IPs]"
          exit 1;;
    esac
  done

echo $READ_FILE
echo $REMOTE_MACHINE
######## Begin input validation for -f flag ############

  if [ ! -f $READ_FILE ] #Check if file exists
  then
    echo "$0: The file \"$READ_FILE\" does not exist."
    exit 1
  fi
  
  if [ ! -r $READ_FILE ] #Check if we have read permissions
  then
    echo "$0: Cannot read \"$READ_FILE\"; check permissions."
    exit 1
  fi
########################################################

if [ ! -z $READ_FILE] #We have a file to do
then
    echo "unimplemented"
fi
if [ ! -z $REMOTE_MACHINE] # we only have a single machine to get info on
then
    echo "trying to push to $REMOTE_MACHINE"
    pushCommand $REMOTE_MACHINE
    getInfo $REMOTE_MACHINE
fi


