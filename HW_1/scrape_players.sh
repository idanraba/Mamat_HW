#!/bin/bash                                       
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




