#!/bin/sh

echo "hello world", $1

case "$1" in

    start)
    if [ -x /home/pc/workspace/daemon/Server/kmd ] ; then
    echo "start..."
    /home/pc/workspace/daemon/Server/kmd &
    fi
    ;;

    stop)
    kill -9 `cat kmd.pid`
    ;;

	restart)
	echo "kill"
	echo "restart"
	;;
	
    *)
    echo "usage: $0 { start | stop | restart}" >&2
    exit 1
    ;;

esac
