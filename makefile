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
