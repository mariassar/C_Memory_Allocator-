CC = gcc
CFLAGS = -Wall -Wextra
.PHONY: clean

# builds the 'main' executable, outputs it to mem.txt file, and displays the output
all: main
     ./main > mem.txt
     ./main 

# compiles the 'main' executable by linking the object files
main: main.o my_mem.o test_cases.o
	$(CC) $(CFLAGS) -o $@ $^

# builds 'main.o' object file, by compiling 'main.c', 'my_mem.h', and 'test_cases.h'
main.o: main.c my_mem.h test_cases.h
	$(CC) $(CFLAGS) -c $<

# builds 'my_mem.o' object file, by compiling 'my_mem.c' and 'my_mem.h'
my_mem.o: my_mem.c my_mem.h
	$(CC) $(CFLAGS) -c $<

# builds 'test_cases.o' object file, by compiling 'test_cases.c', 'my_mem.h', and 'test_cases.h'
test_cases.o: test_cases.c my_mem.h test_cases.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main mem.txt

