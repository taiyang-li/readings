#!/bin/bash

key="no value yet"
while true; do
	clear
	echo "bash extra keys demo. keys to try:"
	echo 
	echo "* insert, delete, home, end, page_up, page_down"
	echo "* the four arrow keys"
	echo "* tab, enter, escape, and space key"
	echo "* the letter and number keys, etc."
	echo 
	echo "	d = show date/time"
	echo "	q = quit"
	echo "==============================="
	echo 

	
	# home key
	if [ "$key" = $'\x1b\x4f\x48' ]; then 
		key=$'\x1b\x5b\x31\x7e'
	fi

	# end key
	if [ "$key" = $'\x1b\x4f\x46' ]; then 
		key=$'\x1b\x5b\x34\x7e'
	fi

	case "$key" in 
		$'\x1b\x5b\x32\x7e') echo insert key;;
		$'\x1b\x5b\x33\x7e') echo delete key;;
		$'\x1b\x5b\x31\x7e') echo home key;;
		$'\x1b\x5b\x34\x7e') echo end key;;
		$'\x1b\x5b\x35\x7e') echo page up;;
		$'\x1b\x5b\x36\x7e') echo page down;;
		$'\x1b\x5b\x41') echo up arraw;;
		$'\x1b\x5b\x42') echo down arraw;;
		$'\x1b\x5b\x43') echo right arraw;;
		$'\x1b\x5b\x44') echo left arraw;;
		$'\x09') echo tab key;;
		$'\x0a') echo enter key;;
		$'\x1b') echo escape key;;
		$'\x20') echo space key;;
		d) date;;
		q) i
			echo time to quit... 
			echo 
			exit 0
			;;
		*) echo you pressed: \'"$key"\';;
	esac

	echo 
	echo "==================================="
	unset K1 K2 K3
	read -s -n 1 -p "press a key: "
	K1="$REPLY"
	read -s -n 2 -t 0.001
	K2="$REPLAY"
	read -s -n 1 -t 0.001
	K3="$REPLAY"
	key="$K1$K2$K3"
		
done

exit $?
