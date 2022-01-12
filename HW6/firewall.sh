#!/bin/bash


ex=./firewall.exe

#putt the input  in var
input="$(cat)"
s=0

#read the rules line by line
while read line; do
	#we need to delete all the comment(begin with #), the space and tab
	line="$(echo "$line" | cut -f1 -d"#" | tr -d ' ' | tr -d '\t')"
	#we need to sperate the packets in the same line to diffrent rules
	if [[ "$line" ]]; then
		rule="$(echo $line | cut -f1 -d",")"
		n=1
		a=0
		packet="$input"

		while [[ "$rule" && "$packet" && "$packet" != "" ]]; do
			a=1
			(( n++ ))
			x="$(echo "$packet" | "$ex" "$rule")"
			rule="$(echo "$line" | cut -f$n -d",")"

			if [[ "$x" ]]; then
				packet="$x"
			else
				packet=""
			fi
		done

		if [[ s -eq 0 ]]; then
			out="$packet"
		else
			out="$out n $packet"
		fi
		s=1
	fi
done < $1

out="$(sed 's/n/\n/g' <(echo "$out"))"
#we need to print all the valid packets in the right order
grep -v '^$' <(echo "$out" | sort | tr -d ' \t')		
				
