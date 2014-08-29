OBJS = kmsad.o server.o
CC = gcc
CFLAGS = -Wall -O -g
kmsad : $(OBJS)
	$(CC) $^ -o $@

.PHONY: clean	
clean:
	-rm kmsad $(OBJS) *.*~

