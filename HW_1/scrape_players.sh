#!/bin/bash                                       
#line 1: browses and export the information from the web to "players" file
#line 2-3: took the specifc request pattern to "urls.txt" file
#line 4-5: counts the number of players and poot them in "Results" file
#line 6: make the link legal
#line 7-14: every line, browers from the link in overview file, and
#           search for midfielder word, and count them, and save them in
#           Results.csv file
#line 15-16: delete the files
#line 17: print the Results.csv file

wget https://www.premierleague.com/players &> /dev/null  

grep -oP "/players/[0-9]+/[a-zA-Z-]+/overview" players > urls.txt
total=$(cat players_list.txt|wc -l)
echo "Total Players: $total" > Results.csv
sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' urls.txt
while read line ; do
	wget $line
	count=$(cat overview|grep -oP "[mM]idfielder"|wc -w)
	if [[ $count -gt 0 ]]; then
		echo "$line, midfielder, $count" >>Results.csv
	fi
	rm overview
done < urls.txt
rm players
rm urls.txt
cat Results.csv




