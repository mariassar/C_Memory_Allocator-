# C Memory Allocator
My goal was to make a basic but functional implementation of a memory allocator in the C programming Language. The standard C programming environment includes an elaborate memory allocator accessed via malloc() and free().

To accomplish the goal, the allocator needed two main functions: malloc() and free(). The data structure supporting the allocator is a linked list of memory block headers. This  data structure would allow me to optimally organize memory space into several parts that can be used and reused. The makeFile compiles the c program into the file called 'mem' containing the output of the memory allocation simulating program.

my_mem.c =
The strategy for allocation within the file called 'my_mem.c' was "first fit," meaning the first block of sufficient size that is available is taken in a sequential manner. If the size is not less than the required size, then it is allocated. The program breaks the bulk space malloc() into blocks with headers.

To collect information about the memory, the code goes through the chain of the blocks and marks their sizes and statuses as free versus occupied. 

To allocate memory, the function finds the first free block of sufficient size and splits it into two blocks: occupied and the remaining free. If the size is not big enough for the block, with an additional header for the new second block, then the first memory block is marked as occupied without splitting. $malloc()$

To free memory, the function identifies the first memory block in the list and marks it as free. Then the code finds the next block in the linked list, and if it's free, the program merges both blocks by extending the size of the current freed block. Going from the start of the chain, the code locates the previous block, and if it is free, the program extends it as well. 

mem = 
To run the file, download the repo, and in the command prompt, run: $ make && ./mem
The make file prints the output of the allocated memory simulator to mem.

The Best Case performance for malloc and free is O(1) if the block is at the beginning of the list.
Either Malloc quickly finds the free block of the correct size or free deallocates the block at the beginning of the chain of blocks.
In the Worst Case, the functions have to go through the entire linked list of blocks, and the performance is O(n), where n is the number of free or used blocks in the chain.
The Average Case performance would depend on the requests for malloc and free from the main function, but in general, the average should be O(n/2).
