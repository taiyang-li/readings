#!/usr/bin/expect

#(
#	echo Y
#	sleep 1
#	for i in `seq 1 6`; do
#		echo 
#		sleep 1
#	done
#) | rpm_create *.citb

spawn rpm_create *.citb
expect "(y/n)"
send "y\r"
expect "����:"
send "\r"
expect "�û���:"
send "\r"
expect "����:"
send "\r"
expect "�û���:"
send "\r"
expect "����:"
send "\r"
expect eof
exit
