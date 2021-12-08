# Defining constants

CC=gcc
CCLINK=$(CC)
CFLAGS=-Wall -g -std=c99
OBJS=grades.o
EXEC=libgrades.so
RM=-rf *.o libgrades.so


#create library
$(EXEC): $(OBJS)
	$(CCLINK) -shared $(OBJS) -o $(EXEC) -llinked-list -L.


#will compile the objects if the o file is older than the c and h files
grades.o: grades.c grades.h linked-list.h 
	$(CC) $(CFLAGS) -c -fpic grades.c
	

# clean o file and libgrades.so
clean:
	rm $(RM)