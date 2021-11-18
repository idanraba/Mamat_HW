#!/bin/bash  

#lines 1-5: check the number of arguments
#lines 6-10: check the exsistence of the course
#lines 11-15: check if the folder exist and if it does will delete and remake
#line 16: create new file with the grades only
#line 17: create the stats file of the course
#lines 18-19: compile linkging and calling the program in C
#line 20: print the course statistics that came from the program in C





if [[ $# != 1 ]]; then
	echo "Wrong number of arguments" >&2
	exit 1
fi

if [[ ! -e  "$1.txt" ]]; then
	echo "Course not found" >&2
	exit 2
fi

if [[ -e  "$1_stats" ]]; then
	rm -r "$1_stats"
fi
mkdir "$1_stats"

cut -d "	" -f 2  "$1.txt" | tail -n+2 > "$1_stats/grades.txt" 
#touch "$1_stat/course_statistics.txt"
gcc -g -Wall calc_statistics.c -o prog.exe
./prog.exe "$1_stats/grades.txt" "$1_stats/course_statistics.txt"
cat "$1_stats/course_statistics.txt" 