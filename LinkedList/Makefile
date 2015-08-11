all : test testclist dlisttest
CFLAGS = -std=c99 -g -O0 -Wall -Werror 
CC = cc
dlisttest : dlisttest.o dlist.o
	$(CC) $(CFLAGS) $< dlist.o -o $@
testclist : testclist.o clist.o
	$(CC) $(CFLAGS) $< clist.o -o $@
test: test.o list.o
	$(CC) $(CFLAGS) $< list.o -o $@
clean:
	rm -rf test test.o 
