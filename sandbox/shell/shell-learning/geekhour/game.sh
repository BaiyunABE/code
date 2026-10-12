#!/bin/bash

number=$(shuf -i 1-10 -n 1)

while true; do
	echo "please input a number from 1 to 10"
	read guess

	if [[ $guess -eq $number ]]; then
		echo "hit! want more? (y/n):"
		read choice

		if [[ $choice = "y" ]] || [[ $choice = "Y" ]]; then
			number=$(($RANDOM % 10 + 1))
			continue
		else
			break
		fi
	elif [[ $guess -lt $number ]]; then
		echo "too small"
	else
		echo "too big"
	fi
done
