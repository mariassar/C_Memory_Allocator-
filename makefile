# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Declare the 'clean' target as a PHONY target
.PHONY: clean

# Default target ('all') that builds the 'main' executable and runs it
all: main
	./main

# Target to build the 'main' executable, depends on the object files
main: main.o my_mem.o test_cases.o
	$(CC) $(CFLAGS) -o $@ $^

# Target to build 'main.o' object file, depends on 'main.c', 'my_mem.h', and 'test_cases.h'
main.o: main.c my_mem.h test_cases.h
	$(CC) $(CFLAGS) -c $<

# Target to build 'my_mem.o' object file, depends on 'my_mem.c' and 'my_mem.h'
my_mem.o: my_mem.c my_mem.h
	$(CC) $(CFLAGS) -c $<

# Target to build 'test_cases.o' object file, depends on 'test_cases.c', 'my_mem.h', and 'test_cases.h'
test_cases.o: test_cases.c my_mem.h test_cases.h
	$(CC) $(CFLAGS) -c $<

# Target to clean up object files and executables
clean:
	rm -f *.o main mem.txt

