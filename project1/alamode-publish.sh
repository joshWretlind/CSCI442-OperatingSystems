#!/bin/bash

# alamode-publish.sh
# sample getopts and 
# input validation code
while getopts ":d:s:h" OPTIONS
  do
    case "$OPTIONS" in
       s) if [ ! -z $INPUT_DIRECTORY ]
          then
            echo "Cannot input duplicate -s options"
            exit 1
          else
            if [ ! -z $OPTARG ]
            then
              INPUT_DIRECTORY=$OPTARG
            else
              echo "You must set a directpry after the -s argument"
              exit 1
            fi
          fi;;
       d) if [ ! -z $OUTPUT_DIRECTORY ]
          then
            echo "Cannot input duplicate -d options"
            exit 1
          else
            if [ ! -z $OPTARG ]
            then
              OUTPUT_DIRECTORY=$OPTARG
            else
              echo "You must set a directpry after the -d argument"
              exit 1
            fi
          fi;;
      h) echo "usage: $0 [-s source directory] [-d destination directory]"
          exit 1;;
    esac
    shift 2
done
if [ ! -z $INPUT_DIRECTORY ]
then
    if [ ! -z $1 ]
    then
        echo "you cannot put two seperate input directories in"
        exit 1
    fi
fi

if [ -z $INPUT_DIRECTORY ]
then
    if [ -z $1 ]
    then
        echo "you must put in some sort of input directory"
        exit 1
    fi
fi

set directory=$1

if [ -z $directory ]
then
    directory=$INPUT_DIRECTORY
fi

final_host_data=""
ls $directory
for file in $(ls $directory) then
do
    echo $file
    inner=$(cat templateInsideMachine.bstl)
    inner=$(echo "$inner" | sed -e "s/@HOSTNAME/$file/g")
    inner=$(echo "$inner" | sed -e "s/@USERSLOGGEDIN/$(cat $file | grep users | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@HOMESPACE/$(cat $file | grep home | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@TOTALTASKCOUNT/$(cat $file | grep Tasks | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@RUNNINGTASKCOUNT/$(cat $file | grep Running | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@SLEEPINGTASKCOUNT/$(cat $file | grep sleeping | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@STOPPEDTASKCOUNT/$(cat $file | grep stopped | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@ZOMBIETASKCOUNT/$(cat $file | grep zombie | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@TOTALRAMAVAILIBLE/$(cat $file | grep ram | sed -e 's/[^0-9]//g')/g" )
    inner=$(echo "$inner" | sed -e "s/@1MINUTELOADAVERAGE  /$(cat $file | grep minute | sed -e 's/.*://g' | sed -e 's/[0-9]\.[0-9][0-9]//2' | sed -e 's/[0-9]\.[0-9][0-9]//3' )/g" )
    inner=$(echo "$inner" | sed -e "s/@5MINUTELOADAVERAGE  /$(cat $file | grep minute | sed -e 's/.*://g' | sed -e 's/[0-9]\.[0-9][0-9]//1' | sed -e 's/[0-9]\.[0-9][0-9]//3' )/g" )
    inner=$(echo "$inner" | sed -e "s/@15MINUTELOADAVERAGE  /$(cat $file | grep minute | sed -e 's/.*://g' | sed -e 's/[0-9]\.[0-9][0-9]//1' | sed -e 's/[0-9]\.[0-9][0-9]//2' )/g" )
    echo $inner
done
