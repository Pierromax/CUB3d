#!/bin/bash

RED="\033[1;31m"
LRED="\033[0;31m"
GREEN="\033[1;32m"
LGREEN="\033[0;32m"
YELLOW="\033[1;33m"
LYELLOW="\033[0;33m"
BLUE="\033[1;34m"
LBLUE="\033[0;34m"
GREY="\033[1;37m"
NC="\033[0m"

test_maps()
{
	for file in maps/tests/ok*; do
		echo -e $LGREEN"Testing "$GREEN$file$NC
		$COMMAND $file
		echo ""
		echo -en $LBLUE"Press any key to continue, or q to quit: "$NC
		read -a input
		if [ "$input" == "q" ] || [ "$input" == "Q" ]; then
			echo -e $RED"Quitting..."$NC
	    	exit 0
		fi
		echo ""
	done

	echo -e $LYELLOW"Testing "$YELLOW"[empty]"$NC
	echo ""
	$COMMAND
	echo ""

	echo -e $LYELLOW"Testing "$YELLOW"maps/tests/.cub"$NC
	echo ""
	$COMMAND map/tests/.cub
	echo ""

	for file in maps/tests/invalid*; do
		echo -e $LYELLOW"Testing "$YELLOW$file$NC
		$COMMAND $file
		echo ""
		echo -en $LBLUE"Press any key to continue, or q to quit: "$NC
		read -a input
		if [ "$input" == "q" ] || [ "$input" == "Q" ]; then
			echo -e $RED"Quitting..."$NC
	    	exit 0
		fi
		echo ""
	done
}


echo -e $RED"Welcome to the cub3d map tester!"$LRED
echo -e 1- "Test with valgrind"
echo -e 2- "Test without valgrind"
read -p "Please enter the option you would like to test (default: 1): " option
echo -e $NC
make re
if [ "$option" == "2" ]; then
	COMMAND="./cub3d"
else
	COMMAND="valgrind ./cub3d"
fi
test_maps
