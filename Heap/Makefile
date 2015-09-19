CFLAGS = -std=c99 -g -O0 -Wall -Werror 
main: main.o heap.o
	$(CC) $(CFLAGS) -o $@ main.o heap.o
clean:
	rm -rf main.o main heap.o heap
