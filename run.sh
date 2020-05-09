#!/bin/bash

timeout_interval=20

if [ "$1" != "" ]; then
	ipaddress="$1"
	tcpclient -vRHl0 "$ipaddress" 119 ./checknntp "$timeout_interval"
	retval="$?"
	exit "$retval"
fi

exit 0
