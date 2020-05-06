#!/bin/bash 

TIMER_INTERRUPT=14
TIMELIMIT=3

PrintAnswer()
{
	if [ "$answer" = TIMEOUT ]; then 
		echo $answer
	else
		echo "your favorate viggie is $answer "
		kill $!
	fi
}

TimerOn()
{
	sleep $TIMELIMIT && kill -s 14 $$ &
}

Int14Vector()
{
	answer="TIMEOUT"
	PrintAnswer
	exit $TIMER_INTERRUPT
}


trap Int14Vector $TIMER_INTERRUPT

echo "what is your favorite vegetable"
TimerOn
read answer 
PrintAnswer
exit 0
