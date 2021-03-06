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
    if [  ! $# -eq 1 ] &&  [ ! $# -eq 2 ]
    then
        echo "Too many arguments to getInfo"
        exit 1
    fi
    if [ $# -eq 1 ]
    then
        export outdir="$outdir_base/$1"
    else
        if [ ! -e $2 ]
        then
            mkdir $2
        fi
        if [ ! -d $2 ]
        then
            echo "A file already exsists where this directiory is meant to be"
        fi
        if [ ! -w $2 ]
        then
            echo "We do not have write permissions to this directory"
        fi
        export outdir=$2
    fi
    master_host=$(hostname)
    command="sh  /tmp/alamode-generate.sh;
             rm  /tmp/alamode-generate.sh;
             scp /tmp/$1 $master_host:$outdir;
             rm  /tmp/$1"
             
    ssh -q $1 $command
}


# What pushCommand does is that it copies over the commands that need to
# ran to the host machine we're running things on, reporting it to their 
# respective locaiton. This is it's own file.
pushCommand () {
    if [ -z $1 ]
    then
        echo "Must call pushCommand with a machine to get the info from"
        exit 1
    fi
    if [ ! $# -eq 1 ] 
    then
        echo "Too many arguments to pushCommand"
        exit 1
    fi
    
    scp -q ./alamode-generate.sh $1:/tmp/alamode-generate.sh
}

while getopts "d:n:f:" OPTIONS
  do
    case "$OPTIONS" in
      d)  if [ ! -z $DIRECTORY ]
          then
            echo "Cannot set two directory options"
            exit 1
          else
            if [ ! -z $OPTARG ]
            then
              DIRECTORY=$OPTARG
            else
              echo "You must set a directpry after the -d argument"
              exit 1
            fi
          fi;;
	  n)  isN="foo"
          if [ ! -z $isF ]
          then
            echo "Cannot set both n and f options -n"
            exit 1            
          else
            if [ ! -z $OPTARG ]
            then
              REMOTE_MACHINE=$OPTARG
            else
              echo "-n options must be given a host"
              exit 1
            fi
          fi;;
      f)  isF="foo"
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
export outdir_base="$(mktemp -d)"

if [ -z $DIRECTORY ]
then
    echo $outdir_base
else
    echo $DIRECTORY
fi

if [ ! -z $READ_FILE ] #We have a file to do
then
    #push the commands to all the hosts first
    for host in $(cat $READ_FILE)
    do
        pushCommand $host
    done
    #run the commands and clean up
    for host in $(cat $READ_FILE)
    do
        getInfo $host $DIRECTORY
    done
fi
if [ ! -z $REMOTE_MACHINE ] # we only have a single machine to get info on
then
    echo "trying to push to $REMOTE_MACHINE"
    pushCommand $REMOTE_MACHINE
    getInfo $REMOTE_MACHINE $DIRECTORY
fi


