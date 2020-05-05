#!/bin/bsh
function lockit()
{
	exec 7<>  /data/liyang/lockfile
	flock -n 7 || {
		echo "waiting for lock to release..."
		flock 7
		echo $? 
	}
}

lockit
while true; do
	echo "liyang"
	sleep 1
done
