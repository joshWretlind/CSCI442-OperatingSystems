#!/bin/bash

# alamode-generate.sh
# what this script does is gather various peices of data from the machine
# it is running on. For example, numebr of processes in a certain state,
# total number of users logged in, processor usage, disk usuage, etc

echo "Current number of users logged in: $(who | wc -l)"   >  "/tmp/`hostname`"
echo "You currently are taking up: $(du -ch | grep total | sed -e "s/\s*Total\s*//") amount of space in your home directory" >> "/tmp/`hostname`"
echo "Total amount of ram: $(cat /proc/meminfo | grep MemTotal | sed -e " s/MemTotal:\s*//g")" >> "/tmp/`hostname`"
 
