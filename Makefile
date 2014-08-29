OBJS = kmd.o server.o
CC = gcc
CFLAGS = -Wall -O -g
kmd : $(OBJS)
	$(CC) $^ -o $@

.PHONY: clean	
clean:
	-rm kmd $(OBJS) *~
