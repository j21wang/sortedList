CC = gcc
CFLAGS = -c -Wall -g

all: sl
sl: main.o libsl.a
	 $(CC) main.o sorted-list.o -o sl

main.o: main.c sorted-list.h
		  $(CC) $(CFLAGS) main.c

libsl.a: sorted-list.o sorted-list.h
	      $(CC) $(CFLAGS) sorted-list.c
	   	ar rcs libsl.a sorted-list.o

clean: rm-rf *.o sl
		 rm-rf *.o libsl.a
