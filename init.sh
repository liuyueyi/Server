#!/bin/sh

case "$1" in

    start)
    if [ -x /home/pc/workspace/daemon/Server/kmd ] ; then
    echo "start..."
    /home/pc/workspace/daemon/Server/kmd &
    fi
    ;;

    stop)
    echo "kill... " `cat kmd.pid`
    kill -9 `cat kmd.pid`
    ;;

	restart)
	kill -9 `cat kmd.pid`
	if [ -x /home/pc/workspace/daemon/Server/kmd ] ; then
    echo "start..."
    /home/pc/workspace/daemon/Server/kmd &
    fi
	;;
	
    *)
    echo "usage: $0 { start | stop | restart}" >&2
    exit 1
    ;;

esac
