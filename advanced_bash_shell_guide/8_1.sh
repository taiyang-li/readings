#!/bin/bash

### gcd algorithm
ARGS=2
E_BADARGS=85
if [ $# -ne "$ARGS" ]; then 
	echo "usage: `basename $0` first-number second-number"
	exit $E_BADARGS
fi

gcd ()
{
	dividend=$1
	divisor=$2

	remainder=1
	until [ "$remainder" -eq 0 ]
	do
		echo "dividend = $dividend"
		echo "divisor = $divisor"
		let "remainder = $dividend % $divisor"
		dividend=$divisor
		divisor=$remainder
	done
}

gcd $1 $2
echo "GCD of $1 and $2 = $dividend"
echo 

exit 0
