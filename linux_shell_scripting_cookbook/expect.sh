#!/usr/bin/expect

spawn ./interactive.sh
expect "enter number:"
send "1\n"
expect "enter name:" 
send "hello\n"
expect eof
