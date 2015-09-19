TARGET = main
all : $(TARGET)
CFLAGS = -std=c99 -g -O0 -Wall -Werror 
CC = cc
OBJS = main.o queue.o
main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
clean:
	rm -rf $(OBJS) $(TARGET)
