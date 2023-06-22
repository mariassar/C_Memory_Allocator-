mem: my_mem.c
	gcc my_mem.c -o mem
clean:
	rm mem

#

tests: tests.c
	gcc tests.c -o tests
	./tests
clean:
	rm mem tests

#make mem - Compiles the my_mem.c file into an executable called "mem"
#make tests  - Compiles the tests.c file into an executable called "tests" and runs the test cases
