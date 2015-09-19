all : main
CFLAGS = -std=c99 -g -O0 -Wall -Werror 
CC = cc
main: main.o list.o
	$(CC) $(CFLAGS) $< list.o -o $@
clean:
	rm -rf test test.o 
