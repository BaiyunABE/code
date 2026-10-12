#!/bin/bash

get_tcp_stats() {
	local info=`netstat --statistics | grep -E "[0-9]+ segments .*"`
	local recv=`expr "$info" : '.* \([0-9]\+\) segments received.*'`
	local send=`expr "$info" : '.* \([0-9]\+\) segments sent out.*'`
	
	echo "$recv $send"
}

init=`get_tcp_stats`
recv=`expr "$init" : '\(.*\) .*'`
send=`expr "$init" : '.* \(.*\)'`
unset init
total=0

while true; do
	sleep 60

	now=`date +"%Y-%m-%d %H:%M"`
	
	curr=`get_tcp_stats`
	curr_recv=`expr "$curr" : '\(.*\) .*'`
	curr_send=`expr "$curr" : '.* \(.*\)'`
	
	delta_recv=`expr $curr_recv - $recv`
	delta_send=`expr $curr_send - $send`
	delta_total=`expr $delta_recv + $delta_send`
	
	symbol=" "
	diff=`expr $delta_total - $total`
	if [ $diff -gt 10 ]; then
		symbol="+"
	elif [ $diff -lt -10 ]; then
		symbol="-"
	fi
	
	printf "%s%6s%6s%6s%6s\n" "$now" "$delta_send" "$delta_recv" "$delta_total" "$symbol"
	
	recv=$curr_recv
	send=$curr_send
	total=$delta_total
done

