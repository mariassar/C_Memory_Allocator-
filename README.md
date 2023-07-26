# C Memory Allocator
My goal was to make a basic but functional implementation of a memory allocator in the C programming Language. The standard C programming environment includes an elaborate memory allocator accessed via malloc() and free().

To accomplish the goal, the allocator needed two main functions: malloc() and free(). The data structure supporting the allocator is a linked list of memory block headers. This  data structure would allow me to optimally organize memory space into several parts that can be used and reused. The makeFile compiles the c program into the file called 'mem' containing the output of the memory allocation simulating program.

my_mem.c =
The strategy for allocation within the file called 'my_mem.c' was "first fit," meaning the first block of sufficient size that is available is taken in a sequential manner. If the size is not less than the required size, then it is allocated. The program is brought to life using the following functions, ##mem_init(), $my_malloc()$, $my_free()$, $mem_get_stats()$, $print_stats()$, and $main$.

#mem_init()# Initializes the memory pool with the provided memory block and saves the pointer to the memory block and its size in global variables. This function also sets the initial block header to represent the entire memory pool as a single free block. The program breaks the bulk space malloc() into blocks with headers.

$my_malloc() Functions equivalent to malloc, but allocates memory from the initialized memory pool. This function searches for a free memory block of the required size in the memory pool (using a "first fit" strategy). If found, it allocates the block and returns a pointer to the memory region after the block header. If the block is larger than the requested size, it splits the block into two parts, one for the allocation and the other for the remaining free space.

$my_free() Functions equivalent to free, but returns memory to the memory pool passed to mem_init. This function takes a pointer to a memory region and extracts the block header pointer. It then marks the corresponding block as free and if adjacent blocks are also free, it merges them to create larger free blocks.

  To free memory, the function identifies the first memory block in the list and marks it as free. Then the code finds the next block in the linked list, and if it's free, the program merges both blocks by extending the size of the current freed block. Going from the start of the chain, the code locates the previous block, and if it is free, the program extends it as well. $free()$

$mem_get_stats()$ Collects statistics about the current memory allocation in the memory pool. This function traverses all memory blocks and calculates the number of free and used blocks. It also determines the sizes of the smallest and largest free/used blocks. Additionally, it updates the provided mem_stats_ptr structure with the collected statistics.

$print_stats()$ Prints the statistics collected by mem_get_stats. This function calls mem_get_stats to obtain the memory statistics and then prints the statistics with a provided prefix for identification.

$main$ The main function that demonstrates the memory management system. This function first initializes a global memory pool with a size of 1 MB. It then calls mem_init to initialize the memory pool with the global memory. Next, it allocates memory using my_malloc in a loop and stores the pointers in the ptr_array array and prints memory statistics after each allocation using print_stats. Lastly, it frees memory in a random order using my_free and prints statistics after each deallocation.

mem = 
To run the file, download the repo, and in the command prompt, run: $ make && ./mem
The make file prints the output of the allocated memory simulator to mem.

The Best Case performance for malloc and free is O(1) if the block is at the beginning of the list.
Either Malloc quickly finds the free block of the correct size or free deallocates the block at the beginning of the chain of blocks.
In the Worst Case, the functions have to go through the entire linked list of blocks, and the performance is O(n), where n is the number of free or used blocks in the chain.
The Average Case performance would depend on the requests for malloc and free from the main function, but in general, the average should be O(n/2).
