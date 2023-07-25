mem: my_mem.c
	gcc my_mem.c -o mem
	./mem > mem.txt
clean:
	rm mem 

#make mem - Compiles the my_mem.c file into an executable called "mem"

