#!/bin/sh

case "$1" in

    start)
    if [ -x /home/pc/workspace/daemon/Server/kmd ] ; then
    echo "start..."
    /home/pc/workspace/daemon/Server/kmd $0 $2 $3 $4 $5 $6 $7 $8 $9 $10 $11&
    fi
    ;;

    stop)
    echo "kill... " 
    kill -9 `cat kmd.pid`
    rm kmd.pid
    ;;

	restart)
	echo "restart...."
	kill -9 `cat kmd.pid`
	if [ -x /home/pc/workspace/daemon/Server/kmd ] ; then
    /home/pc/workspace/daemon/Server/kmd $0 $2 $3 $4 $5 $6 $7 $8 $9 $10 $11&
    fi
	;;
	
    *)
    echo "usage: $0 { start | stop | restart}" >&2
    exit 1
    ;;

esac
