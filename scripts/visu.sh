#!/bin/bash


cycle=0
pos=3
size=16

function helppage
{
	clear
	printf -- "- Cycles:
 h/H/b/B to change by -1/-10/-100/-1000
 l/L/f/F to change by +1/+10/+100/+1000
 0 change to cycle 0

- Position & Size:
 j/k move down/up
 g/G Go to top/bottom
 p/n show less/more lines

Press any key to continue.. "
	read -n 1
}

while [[ $key != 'q' ]]
do
	clear

	bot=$(($pos + $size - 1))
	out=$(./corewar $@ -dump $cycle)"\n"

	printf "$out" | tail +$pos | head -$size
	printf "\n  %-6d (%03d:%03d)\n" "$cycle" "$pos" "$bot"
	printf "Press / for help\n"

	read -n 1 key
	case $key in
		/) helppage;;
		q) clear;;

		0) cycle=0;;
		B) ((cycle -= 1000));;
		b) ((cycle -= 100));;
		H) ((cycle -= 10));;
		h) ((cycle--));;
		l) ((cycle++));;
		L) ((cycle += 10));;
		f) ((cycle += 100));;
		F) ((cycle += 1000));;

		g) pos=3;;
		j) ((pos++));;
		k) ((pos--));;
		G) pos=128;;
		p) ((size--));;
		n) ((size++));;
	esac

	if [[ $cycle -lt 0 ]]; then
		cycle=0
	fi
	if [[ $pos -lt 0 ]]; then
		pos=0
	fi
	if [[ $size -lt 1 ]]; then
		size=1
	fi
	if (( $pos > (130 - $size) )); then
		(( pos = 130 - $size ))
	fi
	if [[ $size -gt 130 ]]; then
		size=130
	fi
done
