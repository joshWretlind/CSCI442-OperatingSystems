#!/bin/bash

# alamode-publish.sh
# sample getopts and 
# input validation code

while getopts ":d:s:h" OPTIONS
  do
    case "$OPTIONS" in
       s) if [ -z $INPUT_DIRECTORY ]
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
       d) if [ -z $OUTPUT_DIRECTORY ]
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
  done

