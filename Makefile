OBJS = main.o 
CC = gcc
CFLAGS = -Wall -O -g

kingshell : $(OBJS)
	$(CC) $^ -o $@
clean:
	rm -rf *.o
