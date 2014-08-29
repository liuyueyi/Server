#!/bin/sh

echo "hello world", $1

case "$1" in

    start)
    if [ -x /home/pc/workspace/daemon/Server/kmsad ] ; then
    echo "start..."
    /home/pc/workspace/daemon/Server/kmsad &
    fi
    ;;

    stop)
    kill -9 `cat kmc_sa.pid`
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