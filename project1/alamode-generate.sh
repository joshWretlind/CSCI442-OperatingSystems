#!/bin/bash

# alamode-generate.sh
# what this script does is gather various peices of data from the machine
# it is running on. For example, numebr of processes in a certain state,
# total number of users logged in, processor usage, disk usuage, etc

set outfile = $(echo "/tmp/" $(hostname))

set totalUsers = $( who | wc -l )

echo $outfile
