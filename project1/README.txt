Name: Josh Wretlind
Files: alamode-fetch.sh
       alamode-fetch
       alamode-generate.sh
       alamode-publish.sh
       alamode-publish
       hosts.txt
       output.html
       README.txt
       templateInsideMachine.bstl
       templateOutside.bstl

File format: 
	Current number of users logged in: <# of users logged in, in users>
	You currently are taking up this amount of space in home: <amount of space being taken up by home, in MB>
	Total amount of ram: <amount of RAM availible, in kB>
	1 minute, 5 minute, 15 minute average load: <1 minute average> <5 minute average> <15 minute average> 
	total nunber of tasks: Tasks: <total number of tasks running> total
	   <# of running tasks> running
	   <# of sleeping tasks> sleeping
	   <# of stopped tasks> stopped
	   <# of zombie tasks> zombie


How the HTML is formed: the BSTL(BASH Standard Template Library, I made that acronym up considering that they operate very similar to how JSTL does) are template files which are used to form the html files

Interesting features: how much space home is taking up and the amount of total ram availible(this has been useful for parallel scientific computing/knowing when a program I'm running hits ram limitations).

Time spent: 9 Hours or so

Note: The coloring for the output html file is done as follows:
	if the 15 minute load is over 50%, then we color the hostname red
	if the 15 minute load is under 50% but over 10%, we color the hostname orange
	if the 15 minute load is under 10%, the hostname is colored black


